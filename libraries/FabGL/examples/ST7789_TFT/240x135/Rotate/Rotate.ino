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


/*
* Example for TTGO T-Display V1.1
*/



#include "fabgl.h"



fabgl::TTGOTDisplayV11Controller DisplayController;


#define TFT_SCK         18
#define TFT_MOSI        19
#define TFT_DC          16
#define TFT_RESET       23
#define TFT_CS           5
#define TFT_BL           4
#define TFT_FREQ  20000000
#define TFT_SPIBUS VSPI_HOST



void test(Color bcolor, char const * msg)
{
  Canvas cv(&DisplayController);
  cv.setBrushColor(bcolor);
  cv.clear();
  cv.setBrushColor(Color::BrightRed);
  int w = cv.getWidth();
  int h = cv.getHeight();
  //Serial.printf("%d %d\n", w, h);
  Point pts[3] = { {w/2, 0}, {w-1, h-1}, {0, h-1} };
  cv.fillPath(pts, 3);
  cv.drawPath(pts, 3);
  cv.selectFont(&fabgl::FONT_8x14);
  cv.drawTextFmt(w/3, h - 20, "%s", msg);
  delay(2000);
}


void setup()
{
  //Serial.begin(115200); delay(500); Serial.write("\n\n\n"); // DEBUG ONLY

  DisplayController.begin(TFT_SCK, TFT_MOSI, TFT_DC, TFT_RESET, TFT_CS, TFT_SPIBUS, TFT_BL, TFT_FREQ);
  DisplayController.setResolution(TFT_135x240);
}


void loop()
{
  DisplayController.setOrientation(fabgl::TFTOrientation::Rotate0);
  test(Color::Blue, "Rotate0");
  DisplayController.setOrientation(fabgl::TFTOrientation::Rotate90);
  test(Color::Green, "Rotate90");
  DisplayController.setOrientation(fabgl::TFTOrientation::Rotate180);
  test(Color::Yellow,"Rotate180");
  DisplayController.setOrientation(fabgl::TFTOrientation::Rotate270);
  test(Color::Magenta, "Rotate270");
}
