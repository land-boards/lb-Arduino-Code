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

  Credits:
     - Guido Lehwalder, https://github.com/guidol70 : using USB-serial Port for ANSI-Terminal (https://github.com/fdivitto/FabGL/issues/110)

*/

#include "fabgl.h"


fabgl::BitmappedDisplayController * DisplayController;
fabgl::PS2Controller                PS2Controller;
fabgl::Terminal                     Terminal;
fabgl::SerialPort                   SerialPort;
fabgl::SerialPortTerminalConnector  SerialPortTerminalConnector;


// RTS/CTS hardware flow gpios
#define UART_RTS 13
#define UART_CTS 35


// settings reset control
/* for old WROOM-32 boards
#define RESET_PIN        12
#define RESET_PIN_ACTIVE  1   // 0 = reset when low, 1 = reset when high
#define USERESETPIN       1   // 1 = reset enabled
//*/
#define RESET_PIN        39
#define RESET_PIN_ACTIVE  0   // 0 = reset when low, 1 = reset when high
#define USERESETPIN       0   // 1 = reset enabled


#define SHOWBREAKS        0




#include "confdialog.h"


void setup()
{
  #if FABGLIB_TERMINAL_DEBUG_REPORT
  Serial.begin(115200); delay(500); Serial.write("\n\nReset\n\n"); // DEBUG ONLY
  #endif

  disableCore0WDT();
  delay(100); // experienced crashes without this delay!
  disableCore1WDT();

  // more stack is required for the UI (used inside Terminal.onVirtualKey)
  Terminal.keyboardReaderTaskStackSize = 3000;

  Terminal.inputQueueSize = 2048; // 2048 good to pass vttest

  preferences.begin("AnsiTerminal", false);

  ConfDialogApp::checkVersion();

  #if USERESETPIN
  pinMode(RESET_PIN, INPUT);
  if (digitalRead(RESET_PIN) == RESET_PIN_ACTIVE)
    preferences.clear();
  #endif

  // because mouse is optional, don't re-try if it is not found (to speed-up boot)
  fabgl::Mouse::quickCheckHardware();

  // keyboard configured on port 0, and optionally mouse on port 1
  if (UARTPORT_FLAGS[ConfDialogApp::getUARTPortIndex()] & UARTFLAG_USE_PS2PORT1)
    PS2Controller.begin(PS2Preset::KeyboardPort0);  // mouse port used as serial port, so no mouse available
  else
    PS2Controller.begin(PS2Preset::KeyboardPort0_MousePort1);

  ConfDialogApp::setupDisplay();

  ConfDialogApp::loadConfiguration();
  
  #if FABGLIB_TERMINAL_DEBUG_REPORT
  Terminal.setLogStream(Serial);  // debug only
  #endif

  Terminal.clear();
  Terminal.enableCursor(true);

  if (ConfDialogApp::getBootInfo() == BOOTINFO_ENABLED) {
    Terminal.write("* *  FabGL - Serial Terminal                            * *\r\n");
    Terminal.write("* *  2019-2022 by Fabrizio Di Vittorio - www.fabgl.com  * *\r\n\n");
    Terminal.printf("Version            : %d.%d\r\n", TERMVERSION_MAJ, TERMVERSION_MIN);
    Terminal.printf("Screen Size        : %d x %d\r\n", DisplayController->getViewPortWidth(), DisplayController->getViewPortHeight());
    Terminal.printf("Terminal Size      : %d x %d\r\n", Terminal.getColumns(), Terminal.getRows());
    Terminal.printf("Keyboard Layout    : %s\r\n", PS2Controller.keyboard()->isKeyboardAvailable() ? SupportedLayouts::names()[ConfDialogApp::getKbdLayoutIndex()] : "No Keyboard");
    //Terminal.printf("Mouse              : %s\r\n", PS2Controller.mouse()->isMouseAvailable() ? "Yes" : "No");
    Terminal.printf("Terminal Type      : %s\r\n", SupportedTerminals::names()[(int)ConfDialogApp::getTermType()]);
    //Terminal.printf("Free Memory        : %d bytes\r\n", heap_caps_get_free_size(MALLOC_CAP_32BIT));
    Terminal.printf("Serial Port        : %s\r\n", UARTPORT_STR[ConfDialogApp::getUARTPortIndex()]);
    Terminal.printf("Serial Parameters  : %s\r\n", ConfDialogApp::getSerParamStr());

    Terminal.write("\r\nPress F12 to change terminal configuration and CTRL-ALT-F12 to reset settings\r\n\n");
  } else if (ConfDialogApp::getBootInfo() == BOOTINFO_TEMPDISABLED) {
    preferences.putInt(PREF_BOOTINFO, BOOTINFO_ENABLED);
  }

  // onVirtualKey is triggered whenever a key is pressed or released
  Terminal.onVirtualKeyItem = [&](VirtualKeyItem * vkItem) {
    if (vkItem->vk == VirtualKey::VK_F12) {
      // CTRL ALT F12 -> show reboot dialog
      // F12          -> show configuration dialog
      if (vkItem->CTRL && (vkItem->LALT || vkItem->RALT)) {
        Terminal.deactivate();
        preferences.clear();
        // show reboot dialog
        auto rebootApp = new RebootDialogApp;
        rebootApp->run(DisplayController);
      } else if (!vkItem->CTRL && !vkItem->LALT && !vkItem->RALT && !vkItem->down) {
        // releasing F12 key to open configuration dialog
        Terminal.deactivate();
        if (PS2Controller.mouse())
          PS2Controller.mouse()->emptyQueue();  // avoid previous mouse movements to be showed on UI
        auto dlgApp = new ConfDialogApp;
        dlgApp->run(DisplayController);
        auto progToInstall = dlgApp->progToInstall;
        // this is required, because the terminal may not cover the entire screen
        Terminal.canvas()->reset();
        Terminal.canvas()->setBrushColor(dlgApp->getBGColor());
        Terminal.canvas()->fillRectangle(dlgApp->frameRect);        
        delete dlgApp;
        Terminal.keyboard()->emptyVirtualKeyQueue();
        Terminal.activate();
        // it has been requested to install a demo program?
        if (progToInstall > -1)
          installProgram(progToInstall);
        vkItem->vk = VirtualKey::VK_NONE;
      }
    } else if (vkItem->vk == VirtualKey::VK_BREAK && !vkItem->down) {
      // BREAK (CTRL PAUSE) -> short break (TX low for 3.5 s)
      // SHIFT BREAK (SHIFT CTRL PAUSE) -> long break (TX low for 0.233 ms)
      SerialPort.sendBreak(true);
      vTaskDelay((vkItem->SHIFT ? 3500 : 233) / portTICK_PERIOD_MS);
      SerialPort.sendBreak(false);
      vkItem->vk = VirtualKey::VK_NONE;
    }
  };

  // onUserSequence is triggered whenever a User Sequence has been received (ESC + '_#' ... '$'), where '...' is sent here
  Terminal.onUserSequence = [&](char const * seq) {
    // 'R': change resolution (for example: ESC + "_#R512x384x64$")
    for (int i = 0; i < RESOLUTIONS_COUNT; ++i)
      if (strcmp(RESOLUTIONS_CMDSTR[i], seq) == 0) {
        // found resolution string
        preferences.putInt(PREF_TEMPRESOLUTION, i);
        if (ConfDialogApp::getBootInfo() == BOOTINFO_ENABLED)
          preferences.putInt(PREF_BOOTINFO, BOOTINFO_TEMPDISABLED);
        ESP.restart();
      }
  };
}


void loop()
{
  #if SHOWBREAKS
  if (SerialPort.breakDetected()) {
    Terminal.printf("BREAK\r\n");
  }
  vTaskDelay(50);
  #else

  // the job is done using UART interrupts
  vTaskDelete(NULL);

  #endif
}
