// A simple NTP based clock for ESP8266/ESP32
//
// This uses two displays to show the time and data.
// Decimal points are used to separate the time and date fields.
// It takes around four seconds for the time to sync with the ntp server.
//

#include <Arduino.h>
#include <MAX72XX.h>

#include <sys/time.h>   // struct timeval
#include <time.h>       // time() ctime()

#include <Ticker.h>

#if defined ESP8266
  #include <ESP8266WiFiMulti.h>
  #include <TZ.h>

  ESP8266WiFiMulti wifiMulti;       // create WiFi object

  constexpr uint8_t latchPin = D1;  // change to reflect your latchPin
#elif defined ESP32
  #include <WiFiMulti.h>

  WiFiMulti wifiMulti;              // create WiFi object

  constexpr uint8_t latchPin = 15;  // change to reflect your latchPin
#endif

constexpr auto STASSID = "<<WIFI SSID>";
constexpr auto STAPSK = "<<WIFI SECRET>>";

 // change to your timezone or use a value from TZ.h (ESP8266)
#define TZ PSTR("ICT-7")

constexpr uint8_t numDevices = 2; // the number of devices

// for hardware SPI
// create the object for the device chain
MAX72XX dispChain(latchPin, numDevices);

// for software SPI
// constexpr uint8_t dataPin = D0;   // change to reflect your dataPin
// constexpr uint8_t clockPin = D2;  // change to reflect your clockPin

// create the object for the device chain
// MAX72XX dispChain(dataPin, clockPin, latchPin, numDevices);

// create the time displays
MAX72XXDisplay  hourDisp(&dispChain, 14, 2);
MAX72XXDisplay  minDisp(&dispChain, 12, 2);
MAX72XXDisplay  secDisp(&dispChain, 10, 2);
MAX72XXDisplay  meridDisp(&dispChain, 8, 2);

// create the date displays
MAX72XXDisplay  dayDisp(&dispChain, 6, 2);
MAX72XXDisplay  monDisp(&dispChain, 4, 2);
MAX72XXDisplay  yearDisp(&dispChain, 0, 4);

// create the ticker to update the displays
Ticker updateTicker;

void setup() {
  wifiMulti.addAP(STASSID, STAPSK); // add the ssid and secret

  WiFi.mode(WIFI_STA); // set the wifi type to station

  // setup ntp sync
  #if defined ESP8266
    configTime(TZ, "pool.ntp.org");
  #elif defined ESP32
    configTzTime(TZ,  "pool.ntp.org");
  #endif

  dispChain.setIntensity(6); // set the intensity for all the devices

  // this ticker is called every 500ms to update the time and date
  updateTicker.attach_ms(500, []() {
    // get the time
    auto now = time(nullptr);
    const tm* tm = localtime(&now);

    // hour
    static int currHour = -1;
    if (currHour != tm->tm_hour) {
      currHour = tm->tm_hour;
      int32_t hour = ((tm->tm_hour % 12) != 0) ? tm->tm_hour % 12 : 12;
      hourDisp.writeNumber(hour, MAX72XX::Character::BLANK, 0);

      // set either A or P for AM or PM
      meridDisp.writeChar(1, (tm->tm_hour < 12) ? 0b01110111 : 0b01100111);
      meridDisp.update();
    }

    // minute
    static int currMin = -1;
    if (currMin != tm->tm_min) {
      currMin = tm->tm_min;
      minDisp.writeNumber(tm->tm_min, MAX72XX::Character::ZERO, 0);
    }

    // second
    secDisp.writeNumber(tm->tm_sec, MAX72XX::Character::ZERO);

    // date, update if the day or year changes
    static int currDay = -1;
    static int currYear = -1;
    if (currDay != tm->tm_mday || currYear != tm->tm_year) {
      currDay = tm->tm_mday;
      currYear = tm->tm_year;
      dayDisp.writeNumber(tm->tm_mday, MAX72XX::Character::ZERO, 0);
      monDisp.writeNumber(tm->tm_mon + 1, MAX72XX::Character::ZERO, 0);
      yearDisp.writeNumber(1900 + tm->tm_year, MAX72XX::Character::BLANK);
    }
  });
}

void loop() {
  wifiMulti.run(); // conenct to wifi with reconnect if required
}
