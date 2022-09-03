// =============================================================================
//
// Based on code from:
//    * 8086tiny: a tiny, highly functional, highly portable PC emulator/VM
//      Copyright 2013-14, Adrian Cable (adrian.cable@gmail.com) - http://www.megalith.co.uk/8086tiny
//    * 8086tiny plus Revision 1.34 - Copyright 2014 Julian Olds - https://jaybertsoftware.weebly.com/8086-tiny-plus.html
//
// This work is licensed under the MIT License. See included LICENSE.TXT.
//
// Changes by Fabrizio Di Vittorio
//   - some heavy optimizations
//   - bug fixes on several instructions (HLT, divide by zero interrupt, ROL, ROR, RCL, RCR, SHL, SHR, DAA, DAS)
//   - expanded macros
//   - removed redundant code resulted from macro expansions
//   - moved Flags out of registers file
//   - moved some static variables into auto function vars
//   - moved decodes tables from BIOS to C code
//   - emulator commands executed as INT instead of custom CPU opcodes
//   - reset to 0xffff:0000 as real 8086
//   - LEA, removed mod=11 option
//   - registers moved to different area
//   - memory read/write no more direct but by callbacks



#include <stdio.h>
#include <string.h>

#include "i8086.h"


namespace fabgl {



#pragma GCC optimize ("O3")

#if FABGL_ESP_IDF_VERSION > FABGL_ESP_IDF_VERSION_VAL(3, 3, 5)
  #pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#endif


#define VIDEOMEM_START 0xA0000
#define VIDEOMEM_END   0xC0000


// 16-bit register decodes

#define REG_AX                                   0
#define REG_CX                                   1
#define REG_DX                                   2
#define REG_BX                                   3
#define REG_SP                                   4
#define REG_BP                                   5
#define REG_SI                                   6
#define REG_DI                                   7

#define REG_ES                                   8
#define REG_CS                                   9
#define REG_SS                                   10
#define REG_DS                                   11

#define REG_ZERO                                 12
#define REG_SCRATCH                              13

#define REG_TMP                                  15


// 8-bit register decodes
#define REG_AL                                   0
#define REG_AH                                   1
#define REG_CL                                   2
#define REG_CH                                   3
#define REG_DL                                   4
#define REG_DH                                   5
#define REG_BL                                   6
#define REG_BH                                   7


// FLAGS

#define CF_ADDR 0
#define PF_ADDR 1
#define AF_ADDR 2
#define ZF_ADDR 3
#define SF_ADDR 4
#define TF_ADDR 5
#define IF_ADDR 6
#define DF_ADDR 7
#define OF_ADDR 8
#define XX_ADDR 9

#define FLAG_CF                                  (flags[CF_ADDR])
#define FLAG_PF                                  (flags[PF_ADDR])
#define FLAG_AF                                  (flags[AF_ADDR])
#define FLAG_ZF                                  (flags[ZF_ADDR])
#define FLAG_SF                                  (flags[SF_ADDR])
#define FLAG_TF                                  (flags[TF_ADDR])
#define FLAG_IF                                  (flags[IF_ADDR])
#define FLAG_DF                                  (flags[DF_ADDR])
#define FLAG_OF                                  (flags[OF_ADDR])



// Global variable definitions
static uint8_t    regs[48];
static uint8_t    flags[10];
static int32_t    regs_offset;
static uint8_t    * regs8, i_mod_size, i_d, i_w, raw_opcode_id, xlat_opcode_id, extra, rep_mode, seg_override_en, rep_override_en;
static uint16_t   * regs16, reg_ip, seg_override;
static uint32_t   op_source, op_dest, set_flags_type;
static int32_t    op_to_addr, op_from_addr;


void *                    i8086::s_context;
i8086::ReadPort           i8086::s_readPort;
i8086::WritePort          i8086::s_writePort;
i8086::WriteVideoMemory8  i8086::s_writeVideoMemory8;
i8086::WriteVideoMemory16 i8086::s_writeVideoMemory16;
i8086::ReadVideoMemory8   i8086::s_readVideoMemory8;
i8086::ReadVideoMemory16  i8086::s_readVideoMemory16;
i8086::Interrupt          i8086::s_interrupt;

uint8_t *                 i8086::s_memory;
bool                      i8086::s_pendingIRQ;
uint8_t                   i8086::s_pendingIRQIndex;
bool                      i8086::s_halted;




// Table 0: R/M mode 1/2 "register 1" lookup
static uint8_t rm_mode12_reg1[]  = { 3, 3, 5, 5, 6, 7, 5, 3 };

// Table 1: R/M mode 1/2 "register 2" lookup
// Table 5: R/M mode 0 "register 2" lookup
static uint8_t rm_mode012_reg2[] = { 6, 7, 6, 7, 12, 12, 12, 12 };

// Table 2: R/M mode 1/2 "DISP multiplier" lookup
static uint8_t rm_mode12_disp[]  = { 1, 1, 1, 1, 1, 1, 1, 1 };

// Table 3: R/M mode 1/2 "default segment" lookup
static uint8_t rm_mode12_dfseg[] = { 11, 11, 10, 10, 11, 11, 10, 11 };

// Table 4: R/M mode 0 "register 1" lookup
static uint8_t rm_mode0_reg1[]   = { 3, 3, 5, 5, 6, 7, 12, 3 };

// Table 6: R/M mode 0 "DISP multiplier" lookup
static uint8_t rm_mode0_disp[]   = { 0, 0, 0, 0, 0, 0, 1, 0 };

// Table 7: R/M mode 0 "default segment" lookup
static uint8_t rm_mode0_dfseg[]  = { 11, 11, 10, 10, 11, 11, 11, 11 };

// Table 8: Translation of raw opcode index ("Raw ID") to function number ("Xlat'd ID")
static uint8_t xlat_ids[] = {   9,  9,  9,  9,  7,  7, 25, 26,  9,  9,  9,  9,  7,  7, 25, 50,
                                9,  9,  9,  9,  7,  7, 25, 26,  9,  9,  9,  9,  7,  7, 25, 26,
                                9,  9,  9,  9,  7,  7, 27, 28,  9,  9,  9,  9,  7,  7, 27, 28,
                                9,  9,  9,  9,  7,  7, 27, 29,  9,  9,  9,  9,  7,  7, 27, 29,
                                2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
                                3,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  4,  4,  4,
                                53, 54, 55, 70, 71, 71, 72, 72, 56, 58, 57, 58, 59, 59, 60, 60,
                                0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                                8,  8,  8,  8, 15, 15, 24, 24,  9,  9,  9,  9, 10, 10, 10, 10,
                                16, 16, 16, 16, 16, 16, 16, 16, 30, 31, 32, 69, 33, 34, 35, 36,
                                11, 11, 11, 11, 17, 17, 18, 18, 47, 47, 17, 17, 17, 17, 18, 18,
                                1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
                                12, 12, 19, 19, 37, 37, 20, 20, 51, 52, 19, 19, 38, 39, 40, 19,
                                12, 12, 12, 12, 41, 42, 43, 44, 69, 69, 69, 69, 69, 69, 69, 69,
                                13, 13, 13, 13, 21, 21, 22, 22, 14, 14, 14, 14, 21, 21, 22, 22,
                                48,  0, 23, 23, 49, 45,  6,  6, 46, 46, 46, 46, 46, 46,  5,  5 };

// Table 9: Translation of Raw ID to Extra Data
static uint8_t ex_data[] = {  0,  0,  0,  0,  0,  0,  8,  8,  1,  1,  1,  1,  1,  1,  9, 36,
                              2,  2,  2,  2,  2,  2, 10, 10,  3,  3,  3,  3,  3,  3, 11, 11,
                              4,  4,  4,  4,  4,  4,  8,  0,  5,  5,  5,  5,  5,  5,  9,  1,
                              6,  6,  6,  6,  6,  6, 10,  2,  7,  7,  7,  7,  7,  7, 11,  0,
                              0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,
                              0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                              0,  0, 21, 21, 21, 21, 21, 21,  0,  0,  0,  0, 21, 21, 21, 21,
                              21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21,
                              0,  0,  0,  0,  0,  0,  0,  0,  8,  8,  8,  8, 12, 12, 12, 12,
                              0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 255, 0,
                              0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  2,  2,  1,  1,
                              0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                              1,  1,  0,  0, 16, 22,  0,  0,  0,  0,  1,  1,  0, 255, 48, 2,
                              0,  0,  0,  0, 255, 255, 40, 11, 3, 3,  3,  3,  3,  3,  3,  3,
                              43, 43, 43, 43,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
                              1, 21,  0,  0,  2, 40, 21, 21, 80, 81, 92, 93, 94, 95,  0,  0 };

// Table 10: How each Raw ID sets the flags (bit 1 = sets SZP, bit 2 = sets AF/OF for arithmetic, bit 3 = sets OF/CF for logic)
static uint8_t std_flags[] = {  3, 3, 3, 3, 3, 3, 0, 0, 5, 5, 5, 5, 5, 5, 0, 0,
                                1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
                                5, 5, 5, 5, 5, 5, 0, 1, 3, 3, 3, 3, 3, 3, 0, 1,
                                5, 5, 5, 5, 5, 5, 0, 1, 3, 3, 3, 3, 3, 3, 0, 1,
                                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                1, 1, 1, 1, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// Table 11: Parity flag loop-up table (256 entries)
static uint8_t parity[] = {   1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
                              0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
                              0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
                              1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
                              0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
                              1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
                              1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
                              0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
                              0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
                              1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
                              1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
                              0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
                              1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
                              0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
                              0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
                              1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1 };

// Table 12: Translation of Raw ID to base instruction size (bytes)
static uint8_t base_size[] = {  2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 2,
                                2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1,
                                2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1,
                                2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1,
                                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 2, 1, 1, 1, 1, 1,
                                2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
                                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
                                3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                3, 3, 0, 0, 2, 2, 2, 2, 4, 1, 0, 0, 0, 0, 0, 0,
                                2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2,
                                2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
                                1, 2, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2 };

// Table 13: Translation of Raw ID to i_w size adder yes/no
static uint8_t i_w_adder[] = {  0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
                                0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
                                0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
                                0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
                                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// Table 14: Translation of Raw ID to i_mod size adder yes/no
static uint8_t i_mod_adder[] = {  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
                                  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
                                  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
                                  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                  1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                                  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                  0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1 };

// Table 15: Jxx decode table A
static uint8_t jxx_dec_a[]   = { OF_ADDR, CF_ADDR, ZF_ADDR, CF_ADDR, SF_ADDR, PF_ADDR, XX_ADDR, XX_ADDR };

// Table 16: Jxx decode table B
static uint8_t jxx_dec_b[]   = { XX_ADDR, XX_ADDR, XX_ADDR, ZF_ADDR, XX_ADDR, XX_ADDR, XX_ADDR, ZF_ADDR };

// Table 17: Jxx decode table C
static uint8_t jxx_dec_c[]   = { XX_ADDR, XX_ADDR, XX_ADDR,XX_ADDR, XX_ADDR, XX_ADDR, SF_ADDR, SF_ADDR };

// Table 18: Jxx decode table D
static uint8_t jxx_dec_d[]   = { XX_ADDR, XX_ADDR, XX_ADDR, XX_ADDR,XX_ADDR, XX_ADDR, OF_ADDR, OF_ADDR };


static uint8_t * instr_table_lookup[] = {    rm_mode12_reg1,    // 0
                                             rm_mode012_reg2,   // 1
                                             rm_mode12_disp,    // 2
                                             rm_mode12_dfseg,   // 3
                                             rm_mode0_reg1,     // 4
                                             rm_mode012_reg2,   // 5
                                             rm_mode0_disp,     // 6
                                             rm_mode0_dfseg,    // 7
                                             xlat_ids,          // 8 TABLE_XLAT_OPCODE
                                             ex_data,           // 9 TABLE_XLAT_SUBFUNCTION
                                             std_flags,         // 10 TABLE_STD_FLAGS
                                             parity,            // 11 TABLE_PARITY_FLAG
                                             base_size,         // 12 TABLE_BASE_INST_SIZE
                                             i_w_adder,         // 13 TABLE_I_W_SIZE
                                             i_mod_adder,       // 14 TABLE_I_MOD_SIZE
                                          };




void i8086::setAL(uint8_t value)
{
  regs8[REG_AL] = value;
}


void i8086::setAH(uint8_t value)
{
  regs8[REG_AH] = value;
}


uint8_t i8086::AL()
{
  return regs8[REG_AL];
}


uint8_t i8086::AH()
{
  return regs8[REG_AH];
}


void i8086::setBL(uint8_t value)
{
  regs8[REG_BL] = value;
}


void i8086::setBH(uint8_t value)
{
  regs8[REG_BH] = value;
}


uint8_t i8086::BL()
{
  return regs8[REG_BL];
}


uint8_t i8086::BH()
{
  return regs8[REG_BH];
}


void i8086::setCL(uint8_t value)
{
  regs8[REG_CL] = value;
}


void i8086::setCH(uint8_t value)
{
  regs8[REG_CH] = value;
}


uint8_t i8086::CL()
{
  return regs8[REG_CL];
}


uint8_t i8086::CH()
{
  return regs8[REG_CH];
}


void i8086::setDL(uint8_t value)
{
  regs8[REG_DL] = value;
}


void i8086::setDH(uint8_t value)
{
  regs8[REG_DH] = value;
}


uint8_t i8086::DL()
{
  return regs8[REG_DL];
}


uint8_t i8086::DH()
{
  return regs8[REG_DH];
}


void i8086::setAX(uint16_t value)
{
  regs16[REG_AX] = value;
}


void i8086::setBX(uint16_t value)
{
  regs16[REG_BX] = value;
}


void i8086::setCX(uint16_t value)
{
  regs16[REG_CX] = value;
}


void i8086::setDX(uint16_t value)
{
  regs16[REG_DX] = value;
}


void i8086::setDI(uint16_t value)
{
  regs16[REG_DI] = value;
}


void i8086::setCS(uint16_t value)
{
  regs16[REG_CS] = value;
}


void i8086::setDS(uint16_t value)
{
  regs16[REG_DS] = value;
}


void i8086::setSS(uint16_t value)
{
  regs16[REG_SS] = value;
}


void i8086::setES(uint16_t value)
{
  regs16[REG_ES] = value;
}


void i8086::setIP(uint16_t value)
{
  reg_ip = value;
}


uint16_t i8086::IP()
{
  return reg_ip;
}


void i8086::setSP(uint16_t value)
{
  regs16[REG_SP] = value;
}


uint16_t i8086::AX()
{
  return regs16[REG_AX];
}


uint16_t i8086::BX()
{
  return regs16[REG_BX];
}


uint16_t i8086::CX()
{
  return regs16[REG_CX];
}


uint16_t i8086::DX()
{
  return regs16[REG_DX];
}


uint16_t i8086::BP()
{
  return regs16[REG_BP];
}


uint16_t i8086::SI()
{
  return regs16[REG_SI];
}


uint16_t i8086::DI()
{
  return regs16[REG_DI];
}


uint16_t i8086::SP()
{
  return regs16[REG_SP];
}


uint16_t i8086::CS()
{
  return regs16[REG_CS];
}


uint16_t i8086::ES()
{
  return regs16[REG_ES];
}


uint16_t i8086::DS()
{
  return regs16[REG_DS];
}


uint16_t i8086::SS()
{
  return regs16[REG_SS];
}


bool i8086::flagIF()
{
  return FLAG_IF;
}


bool i8086::flagTF()
{
  return FLAG_TF;
}


bool i8086::flagCF()
{
  return FLAG_CF;
}


bool i8086::flagZF()
{
  return FLAG_ZF;
}

bool i8086::flagOF()
{
  return FLAG_OF;
}

bool i8086::flagDF()
{
  return FLAG_DF;
}

bool i8086::flagSF()
{
  return FLAG_SF;
}

bool i8086::flagAF()
{
  return FLAG_AF;
}

bool i8086::flagPF()
{
  return FLAG_PF;
}

void i8086::setFlagZF(bool value)
{
  FLAG_ZF = value;
}


void i8086::setFlagCF(bool value)
{
  FLAG_CF = value;
}




// ret false if not acked
bool i8086::IRQ(uint8_t interrupt_num)
{
  if (!s_pendingIRQ) {
    s_pendingIRQ = true;
    s_pendingIRQIndex = interrupt_num;
    return true;
  } else {
    return false;
  }
}



/////////////////////////////////////////////////////////////////////////////


// direct RAM access (not video RAM)
#define MEM8(addr)  s_memory[addr]
#define MEM16(addr) (*(uint16_t*)(s_memory + (addr)))


uint8_t i8086::RMEM8(int addr)
{
  if (addr >= VIDEOMEM_START && addr < VIDEOMEM_END) {
    return s_readVideoMemory8(s_context, addr);
  } else {
    return s_memory[addr];
  }
}


uint16_t i8086::RMEM16(int addr)
{
  if (addr >= VIDEOMEM_START && addr < VIDEOMEM_END) {
    return s_readVideoMemory16(s_context, addr);
  } else {
    return *(uint16_t*)(s_memory + addr);
  }
}


inline __attribute__((always_inline)) uint8_t i8086::WMEM8(int addr, uint8_t value)
{
  if (addr >= VIDEOMEM_START && addr < VIDEOMEM_END) {
    s_writeVideoMemory8(s_context, addr, value);
  } else {
    s_memory[addr] = value;
  }
  return value;
}


inline __attribute__((always_inline)) uint16_t i8086::WMEM16(int addr, uint16_t value)
{
  if (addr >= VIDEOMEM_START && addr < VIDEOMEM_END) {
    s_writeVideoMemory16(s_context, addr, value);
  } else {
    *(uint16_t*)(s_memory + addr) = value;
  }
  return value;
}

/////////////////////////////////////////////////////////////////////////////



// Set auxiliary and overflow flag after arithmetic operations
void set_AF_OF_arith(int32_t op_result)
{
  FLAG_AF = (bool)((op_source ^= op_dest ^ op_result) & 0x10);
  if (op_result == op_dest)
    FLAG_OF = 0;
  else
    FLAG_OF = 1 & (FLAG_CF ^ op_source >> (8 * (i_w + 1) - 1));
}


// Assemble and return emulated CPU FLAGS register
uint16_t i8086::make_flags()
{
  #if I80186MODE
  uint16_t r = 0x0002;    // to pass test186 tests, just unused bit nr. 1 is set to 1 (some programs checks this to know if this is a 80186 or 8086)
  #else
  uint16_t r = 0xf002;    // for real 8086
  #endif

  return r | FLAG_CF << 0 | FLAG_PF << 2 | FLAG_AF << 4 | FLAG_ZF << 6 | FLAG_SF << 7 | FLAG_TF << 8 | FLAG_IF << 9 | FLAG_DF << 10 | FLAG_OF << 11;
}


void i8086::set_flags(int new_flags)
{
  FLAG_CF = (bool)(new_flags & 0x001);
  FLAG_PF = (bool)(new_flags & 0x004);
  FLAG_AF = (bool)(new_flags & 0x010);
  FLAG_ZF = (bool)(new_flags & 0x040);
  FLAG_SF = (bool)(new_flags & 0x080);
  FLAG_TF = (bool)(new_flags & 0x100);
  FLAG_IF = (bool)(new_flags & 0x200);
  FLAG_DF = (bool)(new_flags & 0x400);
  FLAG_OF = (bool)(new_flags & 0x800);
}


// Convert raw opcode to translated opcode index. This condenses a large number of different encodings of similar
// instructions into a much smaller number of distinct functions, which we then execute
void set_opcode(uint8_t opcode)
{
  raw_opcode_id  = opcode;
  xlat_opcode_id = xlat_ids[opcode];
  extra          = ex_data[opcode];
  i_mod_size     = i_mod_adder[opcode];
  set_flags_type = std_flags[opcode];
}


// Execute INT #interrupt_num on the emulated machine
void i8086::pc_interrupt(uint8_t interrupt_num)
{
  // fab: interrupt can exit from halt state
  if (s_halted) {
    s_halted = false;
    ++reg_ip; // go to next instruction after HLT
  }

  if (!s_interrupt(s_context, interrupt_num)) {
    uint16_t newIP     = MEM16(4 * interrupt_num);
    uint16_t newCS     = MEM16(4 * interrupt_num + 2);

    regs16[REG_SP] -= 6;
    uint16_t * stack = &MEM16(16 * regs16[REG_SS] + regs16[REG_SP]);
    stack[2] = make_flags();
    stack[1] = regs16[REG_CS];
    stack[0] = reg_ip;

    reg_ip         = newIP;
    regs16[REG_CS] = newCS;

    FLAG_TF = FLAG_IF = 0;
  }
}


// fab: necessary to go back to the first instruction prefix
uint8_t i8086::raiseDivideByZeroInterrupt()
{
  if (seg_override_en || rep_override_en) {
    // go back looking for segment prefixes or REP prefixes
    while (true) {
      uint8_t opcode = MEM8(16 * regs16[REG_CS] + reg_ip - 1);
      // break if not REP and SEG
      if ((opcode & 0xfe) != 0xf2 && (opcode & 0xe7) != 0x26)
        break;
      --reg_ip;
    }
  }
  pc_interrupt(0);
  return 0;
}


// AAA and AAS instructions - which_operation is +1 for AAA, and -1 for AAS
static int32_t AAA_AAS()
{
  FLAG_AF = FLAG_CF = ((regs8[REG_AL] & 0x0F) > 9) || FLAG_AF;
  regs16[REG_AX] += 262 * (extra - 1) * FLAG_AF;
  return regs8[REG_AL] &= 0x0F;
}


static int32_t DAA_DAS()
{
  // fab: fixed to pass test186
  i_w = 0;
  FLAG_AF = (regs8[REG_AL] & 0x0f) > 9 || FLAG_AF;
  FLAG_CF = regs8[REG_AL] > 0x99 || FLAG_CF;
  if (extra) {
    // DAS
    if (FLAG_CF)
      regs8[REG_AL] -= 0x60;
    else if (FLAG_AF)
      FLAG_CF = (regs8[REG_AL] < 6);
    if (FLAG_AF)
      regs8[REG_AL] -= 6;
  } else {
    // DAA
    if (FLAG_CF)
      regs8[REG_AL] += 0x60;
    if (FLAG_AF)
      regs8[REG_AL] += 6;
  }
  return regs8[REG_AL];
}


void i8086::reset()
{
  regs_offset = (int32_t)(regs - s_memory);

  regs8  = (uint8_t *)(s_memory + regs_offset);
  regs16 = (uint16_t *)(s_memory + regs_offset);

  memset(regs8, 0, sizeof(regs));
  set_flags(0);

  // Initialise CPU state variables
  seg_override_en = 0;
  rep_override_en = 0;

  s_halted = false;

  regs16[REG_CS] = 0xffff;
  reg_ip = 0;
}


// tries to make more compact opcode "switch"
static uint8_t optcodes[] = {
// 0    1   2   3   4   5   6   7   8   9   a   b   c   d   e   f
   0,   0,  0,  0,  0,  0, 13, 12,  0,  0,  0,  0,  0,  0, 13,  0, // 00 - 0f
   0,   0,  0,  0,  0,  0, 13, 12,  0,  0,  0,  0,  0,  0, 13, 12, // 10 - 1f
   0,   0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0, // 20 - 2f
   0,   0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0, // 30 - 3f
   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 40 - 4f
   9,   9,  9,  9,  9,  9,  9,  9,  8,  8,  8,  8,  8,  8,  8,  8, // 50 - 5f
   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 60 - 6f
   2,   2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, // 70 - 7f
   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18,  0, // 80 - 8f
   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // 90 - 9f
   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // a0 - af
   10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, // b0 - bf
   0,   0,  0,  7,  0,  0,  0,  0,  0,  0,  0, 17,  0, 15,  0, 16, // c0 - cf
   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, // d0 - df
   0,   0,  0,  5,  0,  0,  0,  0,  6,  0,  0,  3,  0,  0,  0,  0, // e0 - ef
   0,   0, 14, 14,  0,  0,  0,  0,  4,  4,  4,  4,  4,  4,  0,  0, // f0 - ff
};


void i8086::step()
{

  // Interrupts handling
  // Following instructions inhibits interrupts for the next instruction:
  //    MOV SS, xxx     [opcode 0x8e]
  //    POP SS          [opcode 0x17]
  //    STI             [opcode 0xfb]
  // They are hard coded inside below loop, repeating it using "break" instead of "return"

  // Application has set trap flag, so fire INT 1
  if (FLAG_TF && !seg_override_en && !rep_override_en) {
    pc_interrupt(1);
  }
  // Check for interrupts triggered by system interfaces
  else if (FLAG_IF && s_pendingIRQ && !seg_override_en && !rep_override_en) {
    pc_interrupt(s_pendingIRQIndex);
    s_pendingIRQ = false;
  }

  // Instructions handling

  PSRAM_WORKAROUND2
  
  // external interrupts allowed only out of this loop
  while (true) {

    // seg_override_en and rep_override_en contain number of instructions to hold segment override and REP prefix respectively
    if (seg_override_en)
      --seg_override_en;
    if (rep_override_en)
      --rep_override_en;

    uint8_t const * opcode_stream = s_memory + 16 * regs16[REG_CS] + reg_ip;

    #if I8086_SHOW_OPCODE_STATS
    static uint32_t opcodeStats[256] = {0};
    static int      opcodeStatsCount = 0;
    static uint64_t opcodeStatsT0 = esp_timer_get_time();
    opcodeStats[*opcode_stream] += 1;
    ++opcodeStatsCount;
    if ((opcodeStatsCount % 500000000) == 0) {
      opcodeStatsCount = 0;
      if (Serial.available()) {
        Serial.read();
        printf("\ntime delta = %llu uS\n\n", esp_timer_get_time() - opcodeStatsT0);
        opcodeStatsT0 = esp_timer_get_time();
        for (int i = 0; i < 256; ++i) {
          if (opcodeStats[i] > 0)
            printf("%d, %02X\n", opcodeStats[i], i);
          opcodeStats[i] = 0;
        }
        printf("\n");
      }
    }
    #endif

    // quick and dirty processing of simple and common instructions
    switch (optcodes[*opcode_stream]) {

      // SEG ES
      // SEG CS
      // SEG SS
      // SEG DS
      // opcodes 0x26, 0x2e, 0x36, 0x3e
      case 1:
        seg_override_en = 2;
        seg_override    = ex_data[*opcode_stream];
        if (rep_override_en)
          ++rep_override_en;
        ++reg_ip;
        return;

      // JO
      // JNO
      // JB/JNAE/JC
      // JAE/JNB/JNC
      // JE/JZ
      // JNE/JNZ
      // JBE/JNA
      // JA/JNBE
      // JS
      // JNS
      // JP/JPE
      // JNP/JPO
      // JL/JNGE
      // JGE/JNL
      // JLE/JNG
      // JG/JNLE
      // opcodes 0x70 ... 0x7f
      case 2:
      {
        int32_t inv = *opcode_stream & 1; // inv is the invert flag, e.g. 1 means JNAE, whereas 0 means JAE
        int32_t idx = (*opcode_stream >> 1) & 7;
        reg_ip += 2 + (int8_t)opcode_stream[1] * (inv ^ (flags[jxx_dec_a[idx]] || flags[jxx_dec_b[idx]] || flags[jxx_dec_c[idx]] ^ flags[jxx_dec_d[idx]]));
        return;
      }

      // JMP disp8
      // opcode 0xeb
      case 3:
        reg_ip += 2 + (int8_t)opcode_stream[1];
        return;

      // CLC|STC|CLI|STI|CLD|STD
      // opcodes 0xf8 ... 0xfd
      case 4:
      {
        static int16_t FADDR[3] = { CF_ADDR, IF_ADDR, DF_ADDR };
        flags[FADDR[(*opcode_stream >> 1) & 3]] = *opcode_stream & 1;
        ++reg_ip;
        break;  // reloop, this is required to inhibit interrupt until next instruction (actually should be just for STI...)
      }

      // JCXZ
      // opcode 0xe3
      case 5:
        reg_ip += 2 + !regs16[REG_CX] * (int8_t)opcode_stream[1];
        return;

      // CALL disp16
      // opcode 0xe8
      case 6:
      {
        uint16_t pIP = reg_ip + 3;
        reg_ip = pIP + *(uint16_t*)(opcode_stream + 1);
        regs16[REG_SP] -= 2;
        MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = pIP;
        return;
      }

      // RET (intrasegment)
      // opcode 0xc3
      case 7:
        reg_ip = MEM16(16 * regs16[REG_SS] + regs16[REG_SP]);
        regs16[REG_SP] += 2;
        return;

      // POP reg
      // opcodes 0x58 ... 0x5f
      case 8:
        regs16[REG_SP] += 2;  // SP may be read from stack, so we have to increment here
        regs16[*opcode_stream & 7] = MEM16(16 * regs16[REG_SS] + (uint16_t)(regs16[REG_SP] - 2));
        ++reg_ip;
        return;

      // PUSH reg
      // opcodes 0x50 ... 0x57
      case 9:
        regs16[REG_SP] -= 2;
        MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = regs16[*opcode_stream & 7];
        ++reg_ip;
        return;

      // MOV reg8, data8
      // opcodes 0xb0 ... 0xb7
      case 10:
        regs8[((*opcode_stream >> 2) & 1) + (*opcode_stream & 3) * 2] = *(opcode_stream + 1);
        reg_ip += 2;
        return;

      // MOV reg16, data16
      // opcodes 0xb8 ... 0xbf
      case 11:
        regs16[*opcode_stream & 0x7] = *(uint16_t*)(opcode_stream + 1);
        reg_ip += 3;
        return;

      // POP ES
      // POP SS
      // POP DS
      // opcodes 0x07 0x17 0x1f
      case 12:
        regs16[REG_ES + (*opcode_stream >> 3)] = MEM16(16 * regs16[REG_SS] + regs16[REG_SP]);
        regs16[REG_SP] += 2;
        ++reg_ip;
        break; // reloop, this is required to inhibit interrupt until next instruction (actually just for POP SS)

      // PUSH ES
      // PUSH CS (80186)
      // PUSH SS
      // PUSH DS
      // opcodes 0x06 0x0e 0x16 0x1e
      case 13:
        regs16[REG_SP] -= 2;
        MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = regs16[REG_ES + (*opcode_stream >> 3)];
        ++reg_ip;
        return;

      // REP / REPE / REPNE / REPNZ / REPZ
      // opcodes 0xf2 0xf3
      case 14:
        rep_override_en = 2;
        rep_mode = *opcode_stream & 1;
        if (seg_override_en)
          ++seg_override_en;
        ++reg_ip;
        return;

      // INT imm8
      // opcode 0xcd
      case 15:
        reg_ip += 2;
        pc_interrupt(opcode_stream[1]);
        return;

      // IRET
      // opcode 0xcf
      case 16:
      {
        uint16_t * stack = &MEM16(16 * regs16[REG_SS] + regs16[REG_SP]);
        reg_ip         = stack[0];
        regs16[REG_CS] = stack[1];
        set_flags(stack[2]);
        regs16[REG_SP] += 6;
        return;
      }

      // RETF (intersegment RET)
      // opcode 0xcb
      case 17:
      {
        uint16_t * stack = &MEM16(16 * regs16[REG_SS] + regs16[REG_SP]);
        reg_ip         = stack[0];
        regs16[REG_CS] = stack[1];
        regs16[REG_SP] += 4;
        return;
      }

      // MOV SS, r/m
      case 18:
        stepEx(opcode_stream);
        break;  // reloop, this is required to inhibit interrupt until next instruction

      default:
        stepEx(opcode_stream);
        return;

    }
    
  };

}


void i8086::stepEx(uint8_t const * opcode_stream)
{
  set_opcode(*opcode_stream);

  // Extract fields from instruction
  uint8_t i_reg4bit = raw_opcode_id & 7;
  i_w = i_reg4bit & 1;
  i_d = i_reg4bit / 2 & 1;

  // Extract instruction data fields
  uint16_t i_data0 = opcode_stream[1] | (opcode_stream[2] << 8);
  uint16_t i_data1 = (i_data0 >> 8) | (opcode_stream[3] << 8);
  uint16_t i_data2 = (i_data1 >> 8) | (opcode_stream[4] << 8);

  uint8_t i_mod = 0, i_rm = 0, i_reg = 0;
  int32_t op_result = 0;
  int32_t rm_addr = 0;

  bool calcIP = true;

  // i_mod_size > 0 indicates that opcode uses i_mod/i_rm/i_reg, so decode them
  if (i_mod_size) {
    i_mod = (i_data0 & 0xFF) >> 6;
    i_rm  = i_data0 & 7;
    i_reg = i_data0 / 8 & 7;

    if ((!i_mod && i_rm == 6) || (i_mod == 2))
      i_data2 = (i_data2 >> 8) | (opcode_stream[5] << 8);
    else if (i_mod != 1)
      i_data2 = i_data1;
    else // If i_mod is 1, operand is (usually) 8 bits rather than 16 bits
      i_data1 = (int8_t) i_data1;

    int idx = 4 * !i_mod;
    op_to_addr = rm_addr = i_mod < 3 ? 16 * regs16[seg_override_en ? seg_override : instr_table_lookup[idx + 3][i_rm]] + (uint16_t)(regs16[instr_table_lookup[idx + 1][i_rm]] + instr_table_lookup[idx + 2][i_rm] * i_data1 + regs16[instr_table_lookup[idx][i_rm]]) : (regs_offset + (i_w ? 2 * i_rm : (2 * i_rm + i_rm / 4) & 7));
    op_from_addr = regs_offset + (i_w ? 2 * i_reg : (2 * i_reg + i_reg / 4) & 7);
    if (i_d) {
      auto t = op_from_addr;
      op_from_addr = rm_addr;
      op_to_addr = t;
    }
  }

  // Instruction execution unit
  switch (xlat_opcode_id) {
    case 2: // INC|DEC regs16
    {
      i_w = 1;
      i_d = 0;
      i_reg = i_reg4bit;
      int idx = 4 * !i_mod;
      op_to_addr = rm_addr = i_mod < 3 ? 16 * regs16[seg_override_en ? seg_override : instr_table_lookup[idx + 3][i_rm]] + (uint16_t)(regs16[instr_table_lookup[idx + 1][i_rm]] + instr_table_lookup[idx + 2][i_rm] * i_data1 + regs16[instr_table_lookup[idx][i_rm]]) : (regs_offset + 2 * i_rm);
      op_from_addr = regs_offset + 2 * i_reg;
      i_reg = extra;
    } // not break!
    case 5: // INC|DEC|JMP|CALL|PUSH
      if (i_reg < 2) {
        // INC|DEC
        if (i_w) {
          op_dest = RMEM16(op_from_addr);
          op_result = WMEM16(op_from_addr, (uint16_t)op_dest + 1 - 2 * i_reg);
        } else {
          op_dest = RMEM8(op_from_addr);
          op_result = WMEM8(op_from_addr, (uint16_t)op_dest + 1 - 2 * i_reg);
        }
        op_source = 1;
        set_AF_OF_arith(op_result);
        FLAG_OF = (bool)(op_dest + 1 - i_reg == 1 << (8 * (i_w + 1) - 1));
        if (xlat_opcode_id == 5) {
          // Decode like ADC (0x10)
          xlat_opcode_id = 0x10;
          set_flags_type = 1;
        }
      } else if (i_reg != 6) {
        // JMP|CALL
        uint16_t jumpTo = i_w ? MEM16(op_from_addr) : MEM8(op_from_addr);
        if (i_reg - 3 == 0) {
          // CALL (far)
          i_w = 1;
          regs16[REG_SP] -= 2;
          MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = regs16[REG_CS];
        }
        if (i_reg & 2) {
          // CALL (near or far)
          i_w = 1;
          regs16[REG_SP] -= 2;
          MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = (reg_ip + 2 + i_mod * (i_mod != 3) + 2 * (!i_mod && i_rm == 6));
        }
        if (i_reg & 1) {
          // JMP|CALL (far)
          PSRAM_WORKAROUND2
          regs16[REG_CS] = MEM16(op_from_addr + 2);
        }
        reg_ip = jumpTo;
        return; // no calc IP, no flags
      } else {
        // PUSH
        i_w = 1;
        regs16[REG_SP] -= 2;
        MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = RMEM16(rm_addr);
      }
      break;
    case 6: // TEST r/m, imm16 / NOT|NEG|MUL|IMUL|DIV|IDIV reg
      op_to_addr = op_from_addr;

      switch (i_reg) {
        case 0: // TEST
          // Decode like AND (0x20)
          raw_opcode_id = 0x20;
          set_flags_type = 5;

          reg_ip += i_w + 1;
          if (i_w) {
            op_dest = RMEM16(op_to_addr);
            op_source = (uint16_t)i_data2;
            op_result = (uint16_t)(op_dest & op_source);
          } else {
            op_dest = RMEM8(op_to_addr);
            op_source = (uint8_t)i_data2;
            op_result = (uint8_t)(op_dest & op_source);
          }
          break;
        case 2: // NOT
          if (i_w)
            WMEM16(op_to_addr, ~RMEM16(op_from_addr));
          else
            WMEM8(op_to_addr, ~RMEM8(op_from_addr));
          break;
        case 3: // NEG
          if (i_w)
            op_result = WMEM16(op_to_addr, -(op_source = RMEM16(op_from_addr)));
          else
            op_result = WMEM8(op_to_addr, -(op_source = RMEM8(op_from_addr)));
          op_dest = 0;

          // Decode like SUB (0x28)
          raw_opcode_id  = 0x28;
          set_flags_type = 3;

          FLAG_CF = op_result > op_dest;
          break;
        case 4: // MUL
          raw_opcode_id  = 0x10;
          set_flags_type = 1;
          if (i_w) {
            regs16[REG_DX] = (op_result = RMEM16(rm_addr) * regs16[REG_AX]) >> 16;
            regs16[REG_AX] = op_result;
            FLAG_OF = FLAG_CF = (bool)(op_result - (uint16_t)op_result);
          } else {
            regs16[REG_AX] = op_result = RMEM8(rm_addr) * regs8[REG_AL];
            FLAG_OF = FLAG_CF = (bool)(op_result - (uint8_t) op_result);
          }
          break;
        case 5: // IMUL
          raw_opcode_id  = 0x10;
          set_flags_type = 1;
          if (i_w) {
            regs16[REG_DX] = (op_result = (int16_t)RMEM16(rm_addr) * (int16_t)regs16[REG_AX]) >> 16;
            regs16[REG_AX] = op_result;
            FLAG_OF = FLAG_CF = (bool)(op_result - (int16_t)op_result);
          } else {
            regs16[REG_AX] = op_result = (int8_t)RMEM8(rm_addr) * (int8_t)regs8[REG_AL];
            FLAG_OF = FLAG_CF = (bool)(op_result - (int8_t) op_result);
          }
          break;
        case 6: // DIV
        {
          int32_t scratch_int;
          int32_t scratch_uint, scratch2_uint;
          if (i_w) {
            (scratch_int = RMEM16(rm_addr))
            &&
            !(scratch2_uint = (uint32_t)(scratch_uint = (regs16[REG_DX] << 16) + regs16[REG_AX]) / scratch_int, scratch2_uint - (uint16_t) scratch2_uint)
            ?
            regs16[REG_DX] = scratch_uint - scratch_int * (regs16[REG_AX] = scratch2_uint)
            :
            (raiseDivideByZeroInterrupt(), calcIP = false);
          } else {
            (scratch_int = RMEM8(rm_addr))
            &&
            !(scratch2_uint = (uint16_t)(scratch_uint = regs16[REG_AX]) / scratch_int, scratch2_uint - (uint8_t) scratch2_uint)
            ?
            regs8[REG_AH] = scratch_uint - scratch_int * (regs8[REG_AL] = scratch2_uint)
            :
            (raiseDivideByZeroInterrupt(), calcIP = false);
          }
          break;
        }
        case 7: // IDIV
        {
          int32_t scratch_int;
          int32_t scratch2_uint, scratch_uint;
          if (i_w) {
            (scratch_int = (int16_t)RMEM16(rm_addr))
            &&
            !(scratch2_uint = (int)(scratch_uint = (regs16[REG_DX] << 16) + regs16[REG_AX]) / scratch_int, scratch2_uint - (int16_t) scratch2_uint)
            ?
            regs16[REG_DX] = scratch_uint - scratch_int * (regs16[REG_AX] = scratch2_uint)
            :
            (raiseDivideByZeroInterrupt(), calcIP = false);
          } else {
            (scratch_int = (int8_t)RMEM8(rm_addr))
            &&
            !(scratch2_uint = (int16_t)(scratch_uint = regs16[REG_AX]) / scratch_int, scratch2_uint - (int8_t) scratch2_uint)
            ?
            regs8[REG_AH] = scratch_uint - scratch_int * (regs8[REG_AL] = scratch2_uint)
            :
            (raiseDivideByZeroInterrupt(), calcIP = false);
          }
          break;
        }
      };
      break;
    case 7: // ADD|OR|ADC|SBB|AND|SUB|XOR|CMP AL/AX, immed
      rm_addr = regs_offset;
      i_data2 = i_data0;
      i_mod = 3;
      i_reg = extra;
      reg_ip--;
      // not break!
    case 8: // ADD|OR|ADC|SBB|AND|SUB|XOR|CMP reg, immed
      op_to_addr = rm_addr;
      regs16[REG_SCRATCH] = (i_d |= !i_w) ? (int8_t) i_data2 : i_data2;
      op_from_addr = regs_offset + 2 * REG_SCRATCH;
      reg_ip += !i_d + 1;
      set_opcode(0x08 * (extra = i_reg));
      // not break!
    case 9: // ADD|OR|ADC|SBB|AND|SUB|XOR|CMP|MOV reg, r/m
      switch (extra) {
        case 0: // ADD
          if (i_w) {
            op_dest   = RMEM16(op_to_addr);
            op_source = RMEM16(op_from_addr);
            op_result = (uint16_t)(op_dest + op_source);
            WMEM16(op_to_addr, op_result);
          } else {
            op_dest   = RMEM8(op_to_addr);
            op_source = RMEM8(op_from_addr);
            op_result = (uint8_t)(op_dest + op_source);
            WMEM8(op_to_addr, op_result);
          }
          FLAG_CF = op_result < op_dest;
          break;
        case 1: // OR
          if (i_w) {
            op_dest   = RMEM16(op_to_addr);
            op_source = RMEM16(op_from_addr);
            op_result = op_dest | op_source;
            WMEM16(op_to_addr, op_result);
          } else {
            op_dest   = RMEM8(op_to_addr);
            op_source = RMEM8(op_from_addr);
            op_result = op_dest | op_source;
            WMEM8(op_to_addr, op_result);
          }
          break;
        case 2: // ADC
          if (i_w) {
            op_dest   = RMEM16(op_to_addr);
            op_source = RMEM16(op_from_addr);
            op_result = WMEM16(op_to_addr, op_dest + FLAG_CF + op_source);
          } else {
            op_dest   = RMEM8(op_to_addr);
            op_source = RMEM8(op_from_addr);
            op_result = WMEM8(op_to_addr, op_dest + FLAG_CF + op_source);
          }
          FLAG_CF = (FLAG_CF && (op_result == op_dest)) || (op_result < (int) op_dest);
          set_AF_OF_arith(op_result);
          break;
        case 3: // SBB
          if (i_w) {
            op_dest   = RMEM16(op_to_addr);
            op_source = RMEM16(op_from_addr);
            op_result = WMEM16(op_to_addr, op_dest - (FLAG_CF + op_source));
          } else {
            op_dest   = RMEM8(op_to_addr);
            op_source = RMEM8(op_from_addr);
            op_result = WMEM8(op_to_addr, op_dest - (FLAG_CF + op_source));
          }
          FLAG_CF = (FLAG_CF && (op_result == op_dest)) || (-op_result < -(int) op_dest);
          set_AF_OF_arith(op_result);
          break;
        case 4: // AND
          if (i_w) {
            op_dest   = RMEM16(op_to_addr);
            op_source = RMEM16(op_from_addr);
            op_result = op_dest & op_source;
            WMEM16(op_to_addr, op_result);
          } else {
            op_dest   = RMEM8(op_to_addr);
            op_source = RMEM8(op_from_addr);
            op_result = op_dest & op_source;
            WMEM8(op_to_addr, op_result);
          }
          break;
        case 5: // SUB
          if (i_w) {
            op_dest   = RMEM16(op_to_addr);
            op_source = RMEM16(op_from_addr);
            op_result = WMEM16(op_to_addr, op_dest - op_source);
          } else {
            op_dest   = RMEM8(op_to_addr);
            op_source = RMEM8(op_from_addr);
            op_result = WMEM8(op_to_addr, op_dest - op_source);
          }
          FLAG_CF = op_result > op_dest;
          break;
        case 6: // XOR
          if (i_w) {
            op_dest   = RMEM16(op_to_addr);
            op_source = RMEM16(op_from_addr);
            op_result = op_dest ^ op_source;
            WMEM16(op_to_addr, op_result);
          } else {
            op_dest   = RMEM8(op_to_addr);
            op_source = RMEM8(op_from_addr);
            op_result = op_dest ^ op_source;
            WMEM8(op_to_addr, op_result);
          }
          break;
        case 7: // CMP
          if (i_w) {
            op_dest   = RMEM16(op_to_addr);
            op_source = RMEM16(op_from_addr);
          } else {
            op_dest   = RMEM8(op_to_addr);
            op_source = RMEM8(op_from_addr);
          }
          op_result = op_dest - op_source;
          FLAG_CF = op_result > op_dest;
          break;
        case 8: // MOV
          if (i_w) {
            WMEM16(op_to_addr, RMEM16(op_from_addr));
          } else {
            WMEM8(op_to_addr, RMEM8(op_from_addr));
          }
          break;
      };
      break;
    case 10: // MOV sreg, r/m | POP r/m | LEA reg, r/m
      if (!i_w) { // i_w == 0
        // MOV
        i_w = 1;
        i_reg += 8;
        int32_t scratch2_uint = 4 * !i_mod;
        rm_addr = i_mod < 3 ?
                              16 * regs16[seg_override_en ?
                                                            seg_override
                                                          : instr_table_lookup[scratch2_uint + 3][i_rm]] + (uint16_t)(regs16[instr_table_lookup[scratch2_uint + 1][i_rm]] + instr_table_lookup[scratch2_uint + 2][i_rm] * i_data1 + regs16[instr_table_lookup[scratch2_uint][i_rm]])
                            : (regs_offset + (2 * i_rm));
        if (i_d) {
          regs16[i_reg] = RMEM16(rm_addr);
        } else {
          WMEM16(rm_addr, regs16[i_reg]);
        }
      } else if (!i_d) {  // i_w == 1 && i_d == 0
        // LEA
        int idx = 4 * !i_mod;
        regs16[i_reg] = regs16[instr_table_lookup[idx + 1][i_rm]] + instr_table_lookup[idx + 2][i_rm] * i_data1 + regs16[instr_table_lookup[idx][i_rm]];
      } else {  // i_w == 1 && i_d == 1
        // POP
        regs16[REG_SP] += 2;
        WMEM16(rm_addr, MEM16(16 * regs16[REG_SS] + (uint16_t)(-2 + regs16[REG_SP])));
      }
      break;
    case 11: // MOV AL/AX, [loc]
      rm_addr = 16 * regs16[seg_override_en ? seg_override : REG_DS] + i_data0;
      if (i_d) {
        if (i_w) {
          WMEM16(rm_addr, regs16[REG_AX]);
        } else {
          WMEM8(rm_addr, regs8[REG_AL]);
        }
      } else {
        if (i_w) {
          regs16[REG_AX] = RMEM16(rm_addr);
        } else {
          regs8[REG_AL] = RMEM8(rm_addr);
        }
      }
      reg_ip += 3;
      return; // no calc IP, no flags
    case 12: // ROL|ROR|RCL|RCR|SHL|SHR|???|SAR reg/MEM, 1/CL/imm (80186)
    {
      uint16_t scratch2_uint = (1 & (i_w ? (int16_t)RMEM16(rm_addr) : RMEM8(rm_addr)) >> (8 * (i_w + 1) - 1));
      uint16_t scratch_uint  = extra ? // xxx reg/MEM, imm
        (int8_t) i_data1 : // xxx reg/MEM, CL
        i_d ?
        31 & regs8[REG_CL] : // xxx reg/MEM, 1
        1;
      if (scratch_uint) {
        if (i_reg < 4) {
          // Rotate operations
          scratch_uint %= i_reg / 2 + 8 * (i_w + 1);
          scratch2_uint = i_w ? RMEM16(rm_addr) : RMEM8(rm_addr);
        }
        if (i_reg & 1) {
          // Rotate/shift right operations
          if (i_w) {
            op_dest   = RMEM16(rm_addr);
            op_result = WMEM16(rm_addr, (uint16_t)op_dest >> scratch_uint);
          } else {
            op_dest   = RMEM8(rm_addr);
            op_result = WMEM8(rm_addr, (uint8_t)op_dest >> (uint8_t)scratch_uint);
          }
        } else {
          // Rotate/shift left operations
          if (i_w) {
            op_dest   = RMEM16(rm_addr);
            op_result = WMEM16(rm_addr, (uint16_t)op_dest << scratch_uint);
          } else {
            op_dest   = RMEM8(rm_addr);
            op_result = WMEM8(rm_addr, (uint8_t)op_dest << (uint8_t)scratch_uint);
          }
        }
        if (i_reg > 3) // Shift operations
          set_flags_type = 1; // Shift instructions affect SZP
        if (i_reg > 4) // SHR or SAR
          FLAG_CF = op_dest >> (scratch_uint - 1) & 1;
      }

      switch (i_reg) {
        case 0: // ROL
          if (i_w) {
            op_dest   = RMEM16(rm_addr);
            op_result = WMEM16(rm_addr, (uint16_t)op_dest + (op_source = scratch2_uint >> (16 - scratch_uint)));
          } else {
            op_dest   = RMEM8(rm_addr);
            op_result = WMEM8(rm_addr, (uint8_t)op_dest + (op_source = (uint8_t)scratch2_uint >> (8 - scratch_uint)));
          }
          if (scratch_uint) // fab: zero shift/rotation doesn't change CF or OF ("rotate.asm" and "shift.asm" tests)
            FLAG_OF = (1 & op_result >> (8 * (i_w + 1) - 1)) ^ (FLAG_CF = op_result & 1);
          break;
        case 1: // ROR
          scratch2_uint &= (1 << scratch_uint) - 1;
          if (i_w) {
            op_dest   = RMEM16(rm_addr);
            op_result = WMEM16(rm_addr, (uint16_t)op_dest + (op_source = scratch2_uint << (16 - scratch_uint)));
          } else {
            op_dest   = RMEM8(rm_addr);
            op_result = WMEM8(rm_addr, (uint8_t)op_dest + (op_source = (uint8_t)scratch2_uint << (8 - scratch_uint)));
          }
          if (scratch_uint) // fab: zero shift/rotation doesn't change CF or OF ("rotate.asm" and "shift.asm" tests)
            FLAG_OF = (1 & (i_w ? (int16_t)op_result * 2 : op_result * 2) >> (8 * (i_w + 1) - 1)) ^ (FLAG_CF = 1 & (i_w ? (int16_t)op_result : op_result) >> (8 * (i_w + 1) - 1));
            ;
          break;
        case 2: // RCL
          if (i_w) {
            op_dest   = RMEM16(rm_addr);
            op_result = WMEM16(rm_addr, (uint16_t)op_dest + (FLAG_CF << (scratch_uint - 1)) + (op_source = scratch2_uint >> (17 - scratch_uint)));
          } else {
            op_dest   = RMEM8(rm_addr);
            op_result = WMEM8(rm_addr, (uint8_t)op_dest + (FLAG_CF << (scratch_uint - 1)) + (op_source = (uint8_t)scratch2_uint >> (9 - scratch_uint)));
          }
          if (scratch_uint) // fab: zero shift/rotation doesn't change CF or OF ("rotate.asm" and "shift.asm" tests)
            FLAG_OF = (1 & op_result >> (8 * (i_w + 1) - 1)) ^ (FLAG_CF = (bool)(scratch2_uint & 1 << (8 * (i_w + 1) - scratch_uint)));
          break;
        case 3: // RCR
          if (i_w) {
            op_dest   = RMEM16(rm_addr);
            op_result = WMEM16(rm_addr, (uint16_t)op_dest + (FLAG_CF << (16 - scratch_uint)) + (op_source = scratch2_uint << (17 - scratch_uint)));
          } else {
            op_dest   = RMEM8(rm_addr);
            op_result = WMEM8(rm_addr, (uint8_t)op_dest + (FLAG_CF << (8 - scratch_uint)) + (op_source = (uint8_t)scratch2_uint << (9 - scratch_uint)));
          }
          if (scratch_uint) { // fab: zero shift/rotation doesn't change CF or OF ("rotate.asm" and "shift.asm" tests)
            FLAG_CF = (bool)(scratch2_uint & 1 << (scratch_uint - 1));
            FLAG_OF = (1 & op_result >> (8 * (i_w + 1) - 1)) ^ (1 & (i_w ? (int16_t)op_result * 2 : op_result * 2) >> (8 * (i_w + 1) - 1));
          }
          break;
        case 4: // SHL
          if (scratch_uint) // fab: zero shift/rotation doesn't change CF or OF ("rotate.asm" and "shift.asm" tests)
            FLAG_OF = (1 & op_result >> (8 * (i_w + 1) - 1)) ^ (FLAG_CF = (1 & (op_dest << (scratch_uint - 1)) >> (8 * (i_w + 1) - 1)));
          break;
        case 5: // SHR
          if (scratch_uint) // fab: zero shift/rotation doesn't change CF or OF ("rotate.asm" and "shift.asm" tests)
            FLAG_OF = 1 & op_dest >> (8 * (i_w + 1) - 1);
          break;
        case 7: // SAR
          scratch_uint < 8 * (i_w + 1) || (FLAG_CF = (bool)scratch2_uint);
          FLAG_OF = 0;
          if (i_w) {
            op_dest      = RMEM16(rm_addr);
            uint16_t u16 = (uint16_t)scratch2_uint * ~(((1 << 16) - 1) >> scratch_uint);
            op_result    = WMEM16(rm_addr, op_dest + (op_source = u16));
          } else {
            op_dest    = RMEM8(rm_addr);
            uint8_t u8 = (uint8_t)scratch2_uint * ~(((1 << 8) - 1) >> scratch_uint);
            op_result  = WMEM8(rm_addr, op_dest + (op_source = u8));
          }
          break;
      };
      break;
    }
    case 13: // LOOPxx
      // i_reg4bit: 0=LOOPNZ, 1=LOOPZ, 2=LOOP
      if (--regs16[REG_CX])
        reg_ip += ((FLAG_ZF ^ !i_reg4bit) | (bool)(i_reg4bit & 2)) * (int8_t) i_data0;
      break;
    case 14: // JMP | CALL int16_t/near
      reg_ip += 3 - i_d;
      if (!i_w) {
        if (i_d) {
          // JMP far
          reg_ip = 0;
          regs16[REG_CS] = i_data2;
        } else {
          // CALL
          i_w = 1;
          regs16[REG_SP] -= 2;
          MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = reg_ip;
        }
      }
      reg_ip += i_d && i_w ? (int8_t) i_data0 : i_data0;
      return; // no calc IP, no flags
    case 15: // TEST reg, r/m
      if (i_w) {
        op_result = RMEM16(op_from_addr) & RMEM16(op_to_addr);
      } else {
        op_result = RMEM8(op_from_addr) & RMEM8(op_to_addr);
      }
      break;
    case 16: // XCHG AX, regs16
      if (i_reg4bit != REG_AX) {
        uint16_t t = regs16[REG_AX];
        regs16[REG_AX] = regs16[i_reg4bit];
        regs16[i_reg4bit] = t;
      }
      ++reg_ip;
      return; // no calc ip, no flags
    case 24: // NOP|XCHG reg, r/m
      if (op_to_addr != op_from_addr) {
        if (i_w) {
          uint16_t t = RMEM16(op_to_addr);
          WMEM16(op_to_addr, RMEM16(op_from_addr));
          WMEM16(op_from_addr, t);
        } else {
          uint16_t t = RMEM8(op_to_addr);
          WMEM8(op_to_addr, RMEM8(op_from_addr));
          WMEM8(op_from_addr, t);
        }
      }
      break;
    case 17: // MOVSx (extra=0)|STOSx (extra=1)|LODSx (extra=2)
    {
      int32_t seg = seg_override_en ? seg_override : REG_DS;
      if (i_w) {
        const int dec = (2 * FLAG_DF - 1) * 2;
        for (int32_t i = rep_override_en ? regs16[REG_CX] : 1; i; --i) {
          uint16_t src = extra & 1 ? regs16[REG_AX] : RMEM16(16 * regs16[seg] + regs16[REG_SI]);
          if (extra < 2) {
            WMEM16(16 * regs16[REG_ES] + regs16[REG_DI], src);
            PSRAM_WORKAROUND2;
          } else
            regs16[REG_AX] = src;
          extra & 1 || (regs16[REG_SI] -= dec);
          extra & 2 || (regs16[REG_DI] -= dec);

        }
      } else {
        const int dec = (2 * FLAG_DF - 1);
        for (int32_t i = rep_override_en ? regs16[REG_CX] : 1; i; --i) {
          uint8_t src = extra & 1 ? regs8[REG_AL] : RMEM8(16 * regs16[seg] + regs16[REG_SI]);
          if (extra < 2) {
            WMEM8(16 * regs16[REG_ES] + regs16[REG_DI], src);
            PSRAM_WORKAROUND2;
          } else
            regs8[REG_AL] = src;
          extra & 1 || (regs16[REG_SI] -= dec);
          extra & 2 || (regs16[REG_DI] -= dec);
        }
      }
      if (rep_override_en)
        regs16[REG_CX] = 0;
      ++reg_ip;
      return; // no calc ip, no flags
    }
    case 18: // CMPSx (extra=0)|SCASx (extra=1)
    {
      int count = rep_override_en ? regs16[REG_CX] : 1;
      if (count) {
        int incval = (2 * FLAG_DF - 1) * (i_w + 1);
        if (extra) {
          // SCASx
          op_dest = i_w ? regs16[REG_AX] : regs8[REG_AL];
          for (; count; rep_override_en || count--) {
            if (i_w) {
              op_result = op_dest - (op_source = RMEM16(16 * regs16[REG_ES] + regs16[REG_DI]));
            } else {
              op_result = op_dest - (op_source = RMEM8(16 * regs16[REG_ES] + regs16[REG_DI]));
            }
            regs16[REG_DI] -= incval;
            rep_override_en && !(--regs16[REG_CX] && ((!op_result) == rep_mode)) && (count = 0);
          }
        } else {
          // CMPSx
          int scratch2_uint = seg_override_en ? seg_override : REG_DS;
          for (; count; rep_override_en || count--) {
            if (i_w) {
              op_dest   = RMEM16(16 * regs16[scratch2_uint] + regs16[REG_SI]);
              op_result = op_dest - (op_source = RMEM16(16 * regs16[REG_ES] + regs16[REG_DI]));
            } else {
              op_dest   = RMEM8(16 * regs16[scratch2_uint] + regs16[REG_SI]);
              op_result = op_dest - (op_source = RMEM8(16 * regs16[REG_ES] + regs16[REG_DI]));
            }
            regs16[REG_SI] -= incval;
            regs16[REG_DI] -= incval;
            rep_override_en && !(--regs16[REG_CX] && ((!op_result) == rep_mode)) && (count = 0);
          }
        }
        set_flags_type = 3; // set SZP/AO flags
        FLAG_CF = op_result > op_dest;
      };
      ++reg_ip;
      calcIP = false;
      break;
    }
    case 19: // RET / RETF imm16
      reg_ip = MEM16(16 * regs16[REG_SS] + regs16[REG_SP]);
      regs16[REG_SP] += 2;
      if (extra) {
        // RETF
        regs16[REG_CS] = MEM16(16 * regs16[REG_SS] + regs16[REG_SP]);
        regs16[REG_SP] += 2;
      }
      regs16[REG_SP] += i_data0;
      return; // no calc ip, no flags
    case 20: // MOV r/m, immed
      if (i_w) {
        WMEM16(op_from_addr, i_data2);
      } else {
        WMEM8(op_from_addr, i_data2);
      }
      break;
    case 21: // IN AL/AX, DX/imm8
    {
      int32_t port = extra ? regs16[REG_DX] : (uint8_t) i_data0;
      regs8[REG_AL] = s_readPort(s_context, port);
      if (i_w)
        regs8[REG_AH] = s_readPort(s_context, port + 1);
      break;
    }
    case 22: // OUT DX/imm8, AL/AX
    {
      int32_t port = extra ? regs16[REG_DX] : (uint8_t) i_data0;
      s_writePort(s_context, port, regs8[REG_AL]);
      if (i_w)
        s_writePort(s_context, port + 1, regs8[REG_AH]);
      break;
    }
    case 28: // DAA/DAS
      op_result = DAA_DAS();
      break;
    case 29: // AAA/AAS
      op_result = AAA_AAS();
      break;
    case 30: // CBW
      regs8[REG_AH] = -(1 & (i_w ? * (int16_t *) & regs8[REG_AL] : regs8[REG_AL]) >> (8 * (i_w + 1) - 1));
      break;
    case 31: // CWD
      regs16[REG_DX] = -(1 & (i_w ? * (int16_t *) & regs16[REG_AX] : regs16[REG_AX]) >> (8 * (i_w + 1) - 1));
      break;
    case 32: // CALL FAR imm16:imm16
    {
      regs16[REG_SP] -= 4;
      uint16_t * stack = &MEM16(16 * regs16[REG_SS] + regs16[REG_SP]);
      stack[1] = regs16[REG_CS];
      stack[0] = reg_ip + 5;
      regs16[REG_CS]  = i_data2;
      reg_ip          = i_data0;
      return; // no calc ip, no flags
    }
    case 33: // PUSHF
      regs16[REG_SP] -= 2;
      MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = make_flags();
      ++reg_ip;
      return; // no calc ip, no flags
    case 34: // POPF
      regs16[REG_SP] += 2;
      set_flags(MEM16(16 * regs16[REG_SS] + (uint16_t)(-2 + regs16[REG_SP])));
      ++reg_ip;
      return; // no calc ip, no flags
    case 35: // SAHF
      set_flags((make_flags() & 0xFF00) + regs8[REG_AH]);
      break;
    case 36: // LAHF
      regs8[REG_AH] = make_flags();
      break;
    case 37: // LES|LDS reg, r/m
      i_w = i_d = 1;
      regs16[i_reg] = RMEM16(rm_addr);
      regs16[extra / 2] = RMEM16(rm_addr + 2);
      break;
    case 38: // INT 3
      ++reg_ip;
      pc_interrupt(3);
      return; // no calc ip, no flags
    case 40: // INTO
      ++reg_ip;
      if (FLAG_OF)
        pc_interrupt(4);
      return; // no calc ip, no flags
    case 41: // AAM;
      if (i_data0 &= 0xFF) {
        regs8[REG_AH] = regs8[REG_AL] / i_data0;
        op_result = regs8[REG_AL] %= i_data0;
      } else {
        // Divide by zero
        raiseDivideByZeroInterrupt();
        return; // no calc ip, no flags
      }
      break;
    case 42: // AAD
      i_w = 0;
      regs16[REG_AX] = op_result = 0xFF & (regs8[REG_AL] + i_data0 * regs8[REG_AH]);
      break;
    case 43: // SALC
      regs8[REG_AL] = -FLAG_CF;
      break;
    case 44: // XLAT
      regs8[REG_AL] = RMEM8(16 * regs16[seg_override_en ? seg_override : REG_DS] + (uint16_t)(regs8[REG_AL] + regs16[REG_BX]));
      ++reg_ip;
      return; // no calc ip, no flags
    case 45: // CMC
      FLAG_CF ^= 1;
      ++reg_ip;
      return; // no calc ip, no flags
    case 47: // TEST AL/AX, immed
      if (i_w) {
        op_result = regs16[REG_AX] & i_data0;
      } else {
        op_result = regs8[REG_AL] & (uint8_t)i_data0;
      }
      break;
    case 48: // LOCK:
      break;
    case 49: // HLT
      //printf("CPU HALT, IP = %04X:%04X, AX = %04X, BX = %04X, CX = %04X, DX = %04X\n", regs16[REG_CS], reg_ip, regs16[REG_AX], regs16[REG_BX], regs16[REG_CX], regs16[REG_DX]);
      s_halted = true;
      return; // no calc ip, no flags
    case 51: // 80186, NEC V20: ENTER
    {
      //printf("80186, NEC V20: ENTER\n");
      regs16[REG_SP] -= 2;
      MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = regs16[REG_BP];
      uint16_t framePtr = regs16[REG_SP];
      int16_t level = i_data2 & 31;
      if (level > 0) {
        while (--level) {
          regs16[REG_BP] -= 2;
          regs16[REG_SP] -= 2;
          MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = MEM16(16 * regs16[REG_SS] + regs16[REG_BP]);
        }
        regs16[REG_SP] -= 2;
        MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = framePtr;
      }
      regs16[REG_BP]  = framePtr;
      regs16[REG_SP] -= i_data0;
      break;
    }
    case 52: // 80186, NEC V20: LEAVE
      //printf("80186, NEC V20: LEAVE\n");
      regs16[REG_SP] = regs16[REG_BP];
      regs16[REG_BP] = MEM16(16 * regs16[REG_SS] + regs16[REG_SP]);
      regs16[REG_SP] += 2;
      break;
    case 53: // 80186, NEC V20: PUSHA
    {
      //printf("80186, NEC V20: PUSHA\n");
      uint16_t temp = regs16[REG_SP];
      regs16[REG_SP] -= 2;
      MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = regs16[REG_AX];
      regs16[REG_SP] -= 2;
      MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = regs16[REG_CX];
      regs16[REG_SP] -= 2;
      MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = regs16[REG_DX];
      regs16[REG_SP] -= 2;
      MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = regs16[REG_BX];
      regs16[REG_SP] -= 2;
      MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = temp;
      regs16[REG_SP] -= 2;
      MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = regs16[REG_BP];
      regs16[REG_SP] -= 2;
      MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = regs16[REG_SI];
      regs16[REG_SP] -= 2;
      MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = regs16[REG_DI];
      break;
    }
    case 54: // 80186, NEC V20: POPA
    {
      //printf("80186, NEC V20: POPA\n");
      regs16[REG_DI] = MEM16(16 * regs16[REG_SS] + regs16[REG_SP]);
      regs16[REG_SP] += 2;
      regs16[REG_SI] = MEM16(16 * regs16[REG_SS] + regs16[REG_SP]);
      regs16[REG_SP] += 2;
      regs16[REG_BP] = MEM16(16 * regs16[REG_SS] + regs16[REG_SP]);
      regs16[REG_SP] += 2;
      regs16[REG_SP] += 2;  // SP ignored
      regs16[REG_BX] = MEM16(16 * regs16[REG_SS] + regs16[REG_SP]);
      regs16[REG_SP] += 2;
      regs16[REG_DX] = MEM16(16 * regs16[REG_SS] + regs16[REG_SP]);
      regs16[REG_SP] += 2;
      regs16[REG_CX] = MEM16(16 * regs16[REG_SS] + regs16[REG_SP]);
      regs16[REG_SP] += 2;
      regs16[REG_AX] = MEM16(16 * regs16[REG_SS] + regs16[REG_SP]);
      regs16[REG_SP] += 2;
      break;
    }
    case 55: // 80186: BOUND
      printf("80186: BOUND - not implemented!\n");
      break;
    case 56: // 80186, NEC V20: PUSH imm16
      //printf("80186, NEC V20: PUSH imm16\n");
      regs16[REG_SP] -= 2;
      MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = i_data0;
      break;
    case 57: // 80186, NEC V20: PUSH imm8
      //printf("80186, NEC V20: PUSH imm8\n");
      regs16[REG_SP] -= 2;
      MEM16(16 * regs16[REG_SS] + regs16[REG_SP]) = (i_data0 & 0xff) | (i_data0 & 0x80 ? 0xff00 : 0); // 8->16 bit with sign extension
      break;
    case 58: // 80186 IMUL
      printf("80186 IMUL - not implemented!\n");
      break;
    case 59: // 80186: INSB INSW
      printf("80186: INSB INSW - not implemented!\n");
      break;
    case 60: // 80186: OUTSB OUTSW
      printf("80186: OUTSB OUTSW - not implemented!\n");
      break;
    case 69: // 8087 MATH Coprocessor
      printf("8087 MATH Coprocessor %02X %02X %02X %02X - not implemented!\n", opcode_stream[0], opcode_stream[1], opcode_stream[2], opcode_stream[3]);
      break;
    /*
    case 70: // 80286+
      printf("80286+\n");
      break;
    case 71: // 80386+
      printf("80386+\n");
      break;
    case 72: // BAD OP CODE
      printf("Bad 8086 opcode %02X %02X\n", opcode_stream[0], opcode_stream[1]);
      break;
      */
    default:
      printf("Unsupported 8086 opcode %02X %02X\n", opcode_stream[0], opcode_stream[1]);
      break;
  }

  // Increment instruction pointer by computed instruction length.
  if (calcIP)
    reg_ip += (i_mod * (i_mod != 3) + 2 * (!i_mod && i_rm == 6)) * i_mod_size + base_size[raw_opcode_id] + i_w_adder[raw_opcode_id] * (i_w + 1);

  // If instruction needs to update SF, ZF and PF, set them as appropriate
  if (set_flags_type & 1) {
    FLAG_SF = (1 & op_result >> (8 * (i_w + 1) - 1));
    FLAG_ZF = !op_result;
    FLAG_PF = parity[(uint8_t) op_result];

    // If instruction is an arithmetic or logic operation, also set AF/OF/CF as appropriate.
    if (set_flags_type & 2)
      set_AF_OF_arith(op_result);
    else if (set_flags_type & 4)
      FLAG_CF = FLAG_OF = 0;
  }

}


}   // namespace fabgl
