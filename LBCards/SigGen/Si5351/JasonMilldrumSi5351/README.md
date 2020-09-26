Si5351 Library for avr-gcc
==========================
This is a basic library for the Si5351 series of clock generator ICs from [Silicon Labs][1] for the avr-gcc development environment. It will allow you to control the Si5351 with an AVR microcontroller with a TWI peripheral module, and without depending on the proprietary ClockBuilder software from Silicon Labs.

This library is focused towards usage in RF/amateur radio applications, but it may be useful in other cases. However, keep in mind that coding decisions are and will be made with those applications in mind first, so if you need something a bit different, please do fork this repository. Also, since the Si5351A3 version is the one which seems most useful in amateur radio applications, this is where the current development will be focused. Once the Si5351A3 has a decent and mature feature set, hopefully we will be able to turn to the 8-output version, and perhaps even the B and C variants.

The library is currently in a minimalistic and bit of an untested state. Many of the features are not yet implemented. Unimplemented features will added according to usefulness in RF/amateur radio applications, as stated above. Please feel free to use the issues feature of GitHub if you run into problems or have suggestions for important features to implement.

Hardware Requirements and Setup
-------------------------------
An 8-bit AVR microcontroller with the TWI peripheral is required for this library. It has currently only been tested with the ATmega328P microcontroller, but should be portable to at least the ATmega88 and ATmega168, although the code size is currently about 8 kB (due to the math in the PLL calculations), so you will most likely need at least 16 kB of program space.

The Si5351 is a +3.3 V only part, so if you are not using a +3.3 V microcontroller, be sure you have some kind of level conversion strategy.

Wire the SDA and SCL pins of the Si5351 to the corresponding pins on the AVR. Since the I2C interface is set to 400 kHz, use 1 k&Omega; pullup resistors from +3.3 V to the SDA and SCL lines.

Connect a 25 MHz or 27 MHz crystal with a load capacitance of 6, 8, or 10 pF to the Si5351 XA and XB pins. Locate the crystal as close to the Si5351 as possible and keep the traces as short as possible. Please use a SMT crystal. A crystal with leads will have too much stray capacitance.

Usage
-----
Include the si5351.c, si5351.h, i2c.c, and i2c.h files into your avr-gcc project as you would with any other standard project.

The "public" functions of the library are documented in the code. It should be fairly self-explanatory, but here's a very short introduction.

Before you do anything with the Si5351, you will need to initialize the communications and the IC:

    si5351_init();

Now let's set the CLK0 output to 10 MHz:

    si5351_set_freq(10000000, 0, SI5351_CLK0);
    
The second value passed in the above function is the desired driving PLL frequency. Entering a 0 will have the function choose a PLL frequency for you. If you would like to use a fixed PLL frequency to drive a multisynth (in order to ensure glitch-free tuning), set the desired PLL frequency first using the function below, then specify that frequency in the si5351_set_freq() function:

    si5351_set_pll(900000000, SI5351_PLLA);
    si5351_set_freq(10000000, 900000000, SI5351_CLK0);

The PLL frequency only needs to be set once. Any additional frequency changes only need to use the si5351_set_freq() function as long as you are using the same PLL frequency as before.

If we like we can adjust the output drive power:

    si5351_drive_strength(SI5351_CLK0, SI5351_DRIVE_4MA);

Also, there will be some inherent error in the reference crystal's actual frequency, so we can measure the difference between the actual and nominal output frequency in Hz, multiply by 10, make it an integer, and enter this correction factor into the library to store in EEPROM for future use. Once this is stored, it should not need to be set again unless you want to redo the calibration. With an accurate measurement at one frequency, this calibration should be good across the entire tuning range:

    si5351_set_correction(-900);

One thing to note: the library is set for a 25 MHz reference crystal. If you are using a 27 MHz crystal, please change the SI5351_XTAL_FREQ define in si5351.h.

Also, the si5351_init() function sets the crystal load capacitance for 8 pF. Change this value if you are using a crystal with a different load capacitance.

Oddities
--------
The Si5351 datasheet specifies an I2C address of 0b1100000 (0x60), but this has not been the correct address on the samples used at the NT7S lab. Using the Bus Pirate's I2C address scan macro, we have determined that the address that the Si5351A wants to see is 0x6F (0xDE in 8-bit format), so that is what we use in the library. If you have trouble communicating with your Si5351, you may want to adjust this value in the si5351.h file back to the specified value (0xC0 in 8-bit format). Given the high number of errors we have found in the datasheet so far, this is unsurprising.

**Update:** It turns out that we were sent defective parts. Another batch was ordered from a different vendor and they work on the proper I2C address of 0x60. The code has been updated to reflect the correct address.

Right now, this code is focused solely on the 3-output 10-MSOP variant (Si5351A3). Since some of the code was derived from the Si5351 driver in the Linux kernel, it may be useable on with the other variants, but certainly many features won't work yet. With any luck, we will get the library to work with the other variants as well, or even better, maybe someone will take the initiative, write the code, and send me a pull request.

TODO
----
 - [x] Status flag or return correction constant
 - [ ] Implement tuning below 1 MHz
 - [ ] Implement tuning above 150 MHz

> Written with [StackEdit](https://stackedit.io/).

  [1]: http://www.silabs.com
