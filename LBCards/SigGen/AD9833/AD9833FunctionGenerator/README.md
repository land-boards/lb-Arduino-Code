# DDS Function Generator
## Specification
- Produces sine, square, triange output
- Output waveform resolution of 0.1 Hz
- Frequency range: 1Hz - 100KHz
- Selectable ranges: 0-1KHz, 0-10KHz, 0-100KHz
- Frequency sweep mode with lower/upper range and speed control.
- Output amplitude up to 10 V peak-to-peak (+20dBv)
- DC offset voltage adjustable between -10V to +10V
- Output impedance of 600 Ω.

<img src="https://github.com/cracked-machine/AD9833FunctionGenerator/blob/master/docs/scope/OpAmpGBPComparisons/LM7171/100KHZ_SIN.png" alt="100KHz Sine Wave @ 10vpp" title="100KHz Sine Wave @ 10vpp" width="400"/>

---

## Improved signal integrity at 100KHz
This is the square wave signal with +20dBv gain @ 10KHz

<img src="https://github.com/cracked-machine/AD9833FunctionGenerator/blob/master/docs/scope/OpAmpGBPComparisons/TLO7/10KHZ_SQ.png" alt="10KHz Square Wave @ 10vpp using TL071 opamp" title="10KHz Square Wave @ 10vpp using TL071 opamp" width="400"/>


This is the same signal @ 100KHz. You can see the TL071 opamp (3MHz Unity GBP) is unable to amplify the huge number of odd-integer harmonics of the waveform. This has an undesirable bandpass filter effect on the signal.

<img src="https://github.com/cracked-machine/AD9833FunctionGenerator/blob/master/docs/scope/OpAmpGBPComparisons/TLO7/100KHZ_SQ.png" alt="100KHz Square Wave @ 10vpp using TL071 opamp" title="100KHz Square Wave @ 10vpp using TL071 opamp" width="400"/>

The LM7171 opamp (200MHz Unity GBP) is able to maintain the square wave harmonics for +20dBv @ 100KHz.  

<img src="https://github.com/cracked-machine/AD9833FunctionGenerator/blob/master/docs/scope/OpAmpGBPComparisons/LM7171/100KHZ_SQ.png" alt="100KHz Square Wave @ 10vpp using LM7171 opamp" title="100KHz Square Wave @ 10vpp using LM7171 opamp" width="400"/>

---

## Schematic

[Schematic](https://github.com/cracked-machine/AD9833FunctionGenerator/blob/master/docs/Schematic/AD9833FunctionGenerator.pdf)



