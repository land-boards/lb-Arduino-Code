/*
  Created by Fabrizio Di Vittorio (fdivitto2013@gmail.com) - <http://www.fabgl.com>
  Copyright (c) 2019-2022 Fabrizio Di Vittorio.
  All rights reserved.


* Please contact fdivitto2013@gmail.com if you need a commercial license.


* This library and related software is available under GPL v3.

  FabGL is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  FabGL is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with FabGL.  If not, see <http://www.gnu.org/licenses/>.
 */


#pragma once


/**
 * @file
 *
 * @brief This file contains fabgl::GraphicsAdapter definition.
 */



#include <stdlib.h>
#include <stdint.h>

#include "fabgl.h"



namespace fabgl {



class GraphicsAdapter {

public:

  enum class Emulation {
    None,
    
    // CGA Color Text Mode (PC BIOS 00h/01h)
    // Requires 2 * 40 * 25 = 2000 bytes
    PC_Text_40x25_16Colors,
    
    // CGA Color Text Mode (PC BIOS 02h/03h)
    // This is not visually like CGA because use 640x400 screen with 8x16 fonts, while should be 640x200 with 8x8 fonts
    // Requires 2 * 80 * 25 = 4000 bytes
    PC_Text_80x25_16Colors,
    
    // CGA 320x200, 4 Colors Graphics Mode (PC BIOS 04h/05h)
    // Requires 320 / 4 * 200 = 16000 bytes
    PC_Graphics_320x200_4Colors,
    
    // CGA 640x200, 2 Colors Graphics Mode (PC BIOS 06h)
    // Requires 640 / 8 * 200 = 16000 bytes
    PC_Graphics_640x200_2Colors,
    
    // Hercules 720x348 Graphics Black/White
    // Requires 720 / 8 * 348 = 31320 bytes
    PC_Graphics_HGC_720x348,
  };


  GraphicsAdapter();
  ~GraphicsAdapter();

  void setEmulation(Emulation emulation);
  Emulation emulation()                                    { return m_emulation; }

  bool enableVideo(bool value);

  void setVideoBuffer(void const * videoBuffer);

  // text modes methods
  void setCursorShape(int start, int end);
  void setCursorPos(int row, int column);
  void setCursorVisible(bool value)                        { m_cursorVisible = value; }
  void setBit7Blink(bool value)                            { m_bit7blink = value; }
  int getTextColumns()                                     { return m_columns; }
  int getTextRows()                                        { return m_rows; }

  // PC graphics modes methods
  void setPCGraphicsBackgroundColorIndex(int colorIndex);
  void setPCGraphicsForegroundColorIndex(int colorIndex);
  void setPCGraphicsPaletteInUse(int paletteIndex);
  int getGraphWidth()                                      { return m_VGADCtrl.getViewPortWidth(); }
  int getGraphHeight()                                     { return m_VGADCtrl.getViewPortHeight(); }

  bool VSync()                                             { return m_VGADCtrl.VSync(); }


private:

  void cleanupFont();

  void freeLUT();
  void setupLUT();

  void setFont(FontInfo const * font);

  void createCursorGlyph(int width, int height, int start, int end);

  void setupEmulation(Emulation emulation);

  static void drawScanline_PC_Text_80x25_16Colors(void * arg, uint8_t * dest, int scanLine);
  static void drawScanline_PC_Text_40x25_16Colors(void * arg, uint8_t * dest, int scanLine);
  static void drawScanline_PC_Graphics_320x200_4Colors(void * arg, uint8_t * dest, int scanLine);
  static void drawScanline_PC_Graphics_640x200_2Colors(void * arg, uint8_t * dest, int scanLine);
  static void drawScanline_PC_Graphics_HGC_720x348(void * arg, uint8_t * dest, int scanLine);


  VGADirectController m_VGADCtrl;
  Emulation           m_emulation;
  uint8_t const *     m_videoBuffer;

  uint8_t *           m_rawLUT;

  uint32_t            m_frameCounter;

  // text mode parameters
  FontInfo            m_font;
  int16_t             m_columns;
  int16_t             m_rows;
  int16_t             m_cursorRow;
  int16_t             m_cursorCol;
  uint8_t             m_cursorStart;  // cursor shape scanline start
  uint8_t             m_cursorEnd;    // cursor shape scanline end
  bool                m_cursorVisible;
  uint8_t *           m_cursorGlyph;
  bool                m_bit7blink;

  // PC graphics parameters
  int8_t              m_PCGraphicsBackgroundColorIndex; // used as background color index on 320x200
  int8_t              m_PCGraphicsForegroundColorIndex; // used as foreground color index on 640x200
  int8_t              m_PCGraphicsPaletteInUse;         // 0 = palette 0 low intensity, 1 = palette 0 high intensity, 2 = palette 1 low intensity, 3 = palette 2 high intensity

  bool                m_videoEnabled;

};



};  // fabgl namespace
