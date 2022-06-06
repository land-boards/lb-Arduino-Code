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

 #include "fabui.h"
 #include "uistyle.h"

 #include "programs.h"



 struct ProgsDialog : public uiFrame {

  uiComboBox *      progComboBox;
  uiStaticLabel *   helpLabel1;
  uiStaticLabel *   helpLabel2;


  ProgsDialog(uiFrame * parent)
    : uiFrame(parent, "Programs installer", UIWINDOW_PARENTCENTER, Size(330, 130), true, STYLE_FRAME) {
    frameProps().resizeable        = false;
    frameProps().moveable          = false;
    frameProps().hasMaximizeButton = false;
    frameProps().hasMinimizeButton = false;

    onKeyUp = [&](uiKeyEventInfo const & key) {
      if (key.VK == VirtualKey::VK_ESCAPE)
        exitModal(0);
    };

    int y = 24;

    // help labels
    helpLabel1 = new uiStaticLabel(this, "", Point(120, y + 15), true, STYLE_LABELHELP);
    helpLabel1->setText(PROGRAMS_HELP[0]);
    helpLabel2 = new uiStaticLabel(this, "", Point(120, y + 30), true, STYLE_LABELHELP);
    helpLabel2->setText(PROGRAMS_HELP[1]);

    // select program
    new uiStaticLabel(this, "Program", Point(10,  y), true, STYLE_STATICLABEL);
    progComboBox = new uiComboBox(this, Point(10, y + 12), Size(100, 20), 66, true, STYLE_COMBOBOX);
    progComboBox->items().append(PROGRAMS_NAME, PROGRAMS_COUNT);
    progComboBox->selectItem(0);
    progComboBox->onChange = [&]() {
      auto idx = progComboBox->selectedItem();
      if (idx >= 0) {
        helpLabel1->setText(PROGRAMS_HELP[idx * 2]);
        helpLabel2->setText(PROGRAMS_HELP[idx * 2 + 1]);
      }
    };

    y += 70;

    // Install
    auto installButton = new uiButton(this, "Install", Point(10, y), Size(70, 20), uiButtonKind::Button, true, STYLE_BUTTON);
    installButton->onClick = [&]() {
      exitModal(1);
    };

    // Cancel
    auto cancelButton = new uiButton(this, "Cancel", Point(90, y), Size(70, 20), uiButtonKind::Button, true, STYLE_BUTTON);
    cancelButton->onClick = [&]() {
      exitModal(0);
    };

  }

};


