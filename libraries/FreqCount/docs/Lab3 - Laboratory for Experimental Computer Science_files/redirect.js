// url's to content of old website
var comeFrom = ["http://interface.khm.de/index.php/category/personen/mitarbeiter/",
"http://interface.khm.de/index.php/category/personen/scherffig/",
"http://interface.khm.de/index.php/labor/",
"http://interface.khm.de/index.php/labor/experimente/",
"http://interface.khm.de/index.php/labor/sensoraktor-shield/",
"http://interface.khm.de/index.php/labor/sensoraktor-basics/",
"http://interface.khm.de/index.php/labor/experimente/arduino-realtime-audio-processing/",
"http://interface.khm.de/index.php/labor/experimente/real-time-gps-to-gmap/",
"http://interface.khm.de/index.php/labor/experimente/connect-a-ltc2400-high-precision-24-bit-analog-to-digital-converter/",
"http://interface.khm.de/index.php/labor/experimente/input-channel-extender/",
"http://interface.khm.de/index.php/labor/experimente/arduino-frequency-counter-library/",
"http://interface.khm.de/index.php/labor/experimente/theremin-as-a-capacitive-sensing-device/",
"http://interface.khm.de/index.php/labor/experimente/sleep_watchdog_battery/",
"http://interface.khm.de/index.php/labor/sensoraktor-shield/introducing-the-board/"];
// redirects
var redirects = ["http://interface.khm.de/index.php/personen/mitarbeiter/",
"http://interface.khm.de/index.php/personen/doktoranden/lasse-scherffig/",
"http://interface.khm.de/index.php/lab/",
"http://interface.khm.de/index.php/lab/experiments/",
"http://interface.khm.de/index.php/lab/sensoraktor-shield/",
"http://interface.khm.de/index.php/lab/sensoraktor-basics/",
"http://interface.khm.de/index.php/lab/experiments/arduino-realtime-audio-processing/",
"http://interface.khm.de/index.php/lab/experiments/real-time-gps-to-gmap/",
"http://interface.khm.de/index.php/lab/experiments/connect-a-ltc2400-high-precision-24-bit-analog-to-digital-converter/",
"http://interface.khm.de/index.php/lab/experiments/input-channel-extender/",
"http://interface.khm.de/index.php/lab/experiments/arduino-frequency-counter-library/",
"http://interface.khm.de/index.php/lab/experiments/theremin-as-a-capacitive-sensing-device/",
"http://interface.khm.de/index.php/lab/experiments/sleep_watchdog_battery/",
"http://interface.khm.de/index.php/lab/sensoraktor-shield/introducing-the-board/"];
// get url
var url = window.location;
// loop through array 'comeFrom'
for(var i=0; i<comeFrom.length; i++){
	// redirect
	if(url == comeFrom[i]){
		window.location = redirects[i];
	}
}