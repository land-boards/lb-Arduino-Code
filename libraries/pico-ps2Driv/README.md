# pico-ps2Driv
PS2 keyboard library for pico-sdk \
Based on [PS2Keyboard](https://github.com/PaulStoffregen/PS2Keyboard)
## Usage
Add the _pico-ps2Driv_ subdirectory to the CMakeLists.txt of your project and include the library in _target_link_libraries_.
### Initializing the keyboard
Before reading the keyboard, it must be initialized with _PS2_init_.\
_PS2_init_ takes the data and clock pins as a parameters.\
_Example:_ `PS2_init(3, 2);` initializes the keyboard, using GPIO3 as data and GPIO2 as clock.
### Reading the keybaord
`PS2_keyAvailable()` returns 1 if there are keys to be read, 0 otherwise.\
`PS2_readKey()` returns the character associated to the next keystroke in the buffer.

