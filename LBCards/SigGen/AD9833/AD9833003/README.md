# AD9833 Basic Arduino Library

This is a simple, cut-down library to get the AD9833 up and running as a signal generator. It provides an initialisation function and then a function to set the frequency and waveform.<br>

* The project was based on a more comprehensive library here: https://github.com/Billwilliams1952/AD9833-Library-Arduino
* AD9833 datasheet here: http://www.analog.com/media/en/technical-documentation/data-sheets/AD9833.pdf

## Installation
Download the ZIP file and extract it to the **Arduino/libraries** folder. Open the Arduino IDE, click **File**-**Examples**-**AD9833_test**.

| AD9833 Pin | Arduino Pin |
| :--------- | :---------- |
| **CLK** | **SCK** |
| **DAT** | **MOSI** |
| **FNC** | Any digital pin (default **D4**) |
| **VCC** | **5V** |
| **GND** | **GND** |
| **REF** | NC |

## Usage
There are only two functions required to initialise and then control the device and generate a simple output signal.<br>
First instantiate the AD9833 object and select a function pin for SPI communication control:
```
#define FNC_PIN 4
AD9833 ad9833;
```
Initialise the chip in the Arduino **setup()** function:
```
ad9833.begin(FNC_PIN);
```
Within either the **setup()** or **loop()** functions you can then tell the device to start generating a signal:<br>
This method accepts a waveform type of either **SINE_WAVE**, **SQUARE_WAVE**, or **TRIANGLE_WAVE**, and a frequency in KHz.
```
ad9833.setFrequency(waveType, frequencyInKHz);
```
<br>
That's it. The device should now be generating the requested signal.