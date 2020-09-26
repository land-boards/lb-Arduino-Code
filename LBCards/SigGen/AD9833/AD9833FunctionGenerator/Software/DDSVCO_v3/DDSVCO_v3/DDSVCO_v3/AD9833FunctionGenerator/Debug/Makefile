################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../include


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../main.cpp


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
main.o

OBJS_AS_ARGS +=  \
main.o

C_DEPS +=  \
main.d

C_DEPS_AS_ARGS +=  \
main.d

OUTPUT_FILE_PATH +=AD9833FunctionGenerator.elf

OUTPUT_FILE_PATH_AS_ARGS +=AD9833FunctionGenerator.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+=  \
H:/Workspace/ElectronicsProjects/TestAndMeasurement/AD9833FunctionGenerator/AD9833FunctionGenerator/Software/DDSVCO_v3/DDSVCO_v3/DDSVCO_v3/ArduinoCore/Debug/libArduinoCore.a

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./main.o: .././main.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 5.4.0
	$(QUOTE)H:\Programs\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DDEBUG -DF_CPU=16000000L -DARDUINO=10805 -DARDUINO_AVR_NANO -DARDUINO_ARCH_AVR  -I"H:\Programs\Atmel\Studio\7.0\Packs\Atmel\ATmega_DFP\1.2.272\include" -I"../include" -I"..\\..\ArduinoCore\include" -I"..\\..\ArduinoCore\include\core" -I"..\\..\ArduinoCore\include\libraries\adafruit_gfx_library" -I"..\\..\ArduinoCore\include\libraries\adafruit_ssd1306" -I"..\\..\ArduinoCore\include\libraries\enableinterrupt" -I"..\\..\ArduinoCore\include\libraries\SPI" -I"..\\..\ArduinoCore\include\libraries\timerone" -I"..\\..\ArduinoCore\include\libraries\Wire" -I"..\\..\ArduinoCore\include\libraries\adafruit_gfx_library\Fonts" -I"..\\..\ArduinoCore\include\libraries\enableinterrupt\utility" -I"..\\..\ArduinoCore\include\libraries\enableinterrupt\examples\SimpleWithLibrary" -I"..\\..\ArduinoCore\include\libraries\timerone\config" -I"..\\..\ArduinoCore\include\libraries\Wire\utility" -I"..\\..\ArduinoCore\include\variants\eightanaloginputs" -I"..\\..\ArduinoCore\include\variants\standard"  -Os -fno-threadsafe-statics -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -w -mmcu=atmega328p -B "H:\Programs\Atmel\Studio\7.0\Packs\Atmel\ATmega_DFP\1.2.272\gcc\dev\atmega328p" -c -std=gnu++11 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR8/GNU Linker : 5.4.0
	$(QUOTE)H:\Programs\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="AD9833FunctionGenerator.map" -Wl,--start-group -Wl,-lm -Wl,-lArduinoCore  -Wl,--end-group -Wl,-L"H:\WORKSP~1\ElectronicsProjects\TestAndMeasurement\AD9833~1\AD9833~1\Software\DDSVCO~1\DDSVCO~1\DDSVCO~1\ARDUIN~1\Debug"  -Wl,--gc-sections -mmcu=atmega328p -B "H:\Programs\Atmel\Studio\7.0\Packs\Atmel\ATmega_DFP\1.2.272\gcc\dev\atmega328p" -Os  
	@echo Finished building target: $@
	"H:\Programs\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "AD9833FunctionGenerator.elf" "AD9833FunctionGenerator.hex"
	"H:\Programs\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "AD9833FunctionGenerator.elf" "AD9833FunctionGenerator.eep" || exit 0
	"H:\Programs\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "AD9833FunctionGenerator.elf" > "AD9833FunctionGenerator.lss"
	"H:\Programs\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "AD9833FunctionGenerator.elf" "AD9833FunctionGenerator.srec"
	"H:\Programs\Atmel\Studio\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "AD9833FunctionGenerator.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "AD9833FunctionGenerator.elf" "AD9833FunctionGenerator.a" "AD9833FunctionGenerator.hex" "AD9833FunctionGenerator.lss" "AD9833FunctionGenerator.eep" "AD9833FunctionGenerator.map" "AD9833FunctionGenerator.srec" "AD9833FunctionGenerator.usersignatures"
	