# Using a Digital DEC LK401 Keyboard via USB

This repo contains code to run the DEC LK401 via USB at modern computers.

Most of the things work, I am writing these lines on the LK401.

## Special keys

The following hints are for using the keyboard.

![DEC LK401AG](./images/dec_lk_401.png)

For standard characters, shifted keys and CTRL keys (like CTRL-C etc.), the keyboard is exactly as one would expect from
any other keyboard. Same is with arrow keys, function keys F1-F19, special keys (insert, delete, backspace, CR, space,
scroll up, scroll down, tab). Also with the numeric key pad.

Alternate Right Key also works as expected and brings up alternate key values (upper left vales of a key).

Special behaviour is:
* "Ausführen" maps to ```ESC```
* Numeric key function keys ```PF1```-```PF4``` map to function keys
  ```F21```-```F24```
* ```Suchen``` key maps to ```Go to Pos1``` function
* ```Selektieren``` maps map to ```Go to End```
* ```Hilfe``` maps to ```Menu``` key
* Function key ```F20``` controls the key click volume. Default is off. Pressing
  the key loops through the available 7 volume levels. The volume 0 (volume off)
  is feedbacked by flashing the "lock" LED.

## Required hardware

The LK401 is connected via an Arduino Micro, which owns a USB connector. The Arduino Micro appears to the PC as a 
standard USB keyboard.

More information on the approach is [here](http://spurtikus.de/posts/electronics/diy-usb-keyboard/).

## How to build
This project was created with [CLion](https://www.jetbrains.com/clion/).
It leaves the well known Arduino IDE approach, where a single *.ino Sketch file is used and uses standard C++ source and
header files. It is a CMake based project and uses [platform.io](https://platformio.org/)

To install platform.io together with CLion, see here
https://blog.jetbrains.com/clion/2020/08/arduino-from-hobby-to-prof-p1/

After installation of tools above, the project can be build with a mouse click in CLion, or on command line:

```shell
mkdir cmake-build-micro
cd cmake-build-micro
cmake -DCMAKE_BUILD_TYPE=micro -G "CodeBlocks - Unix Makefiles" /<path to project>/keyboard

cmake --build ./cmake-build-micro --target all
```

## Getting the serial debug output
While getting the output in Arduino IDE is trivial, without Arduino IDE we get it like this:

```shell
stty -F /dev/ttyACM0 1000000 raw -clocal -echo
cat /dev/ttyACM0
```

Replace ```/dev/ACM0``` with the correct device for your environment.

## Todos
* From the four keys Compose Character Left+Right, Alt Function Left+Right, currently only Alt Function Right is used. 
  Add code for other keys too.

## Further reading and todos
* USB HUT Documentation, see page 53 for keyboard codes [Link](./doc/Hut1_12v2.pdf)
* (Digital DEC documentation for keyboard *VCB02 Video Subsystem Technical Manual* is >120MB PDF, too large to put it 
  here)
* Linux Keyboard Driver file for LK401 [Link](doc/lkkbd.c.txt)
* How to send CTRL+ALT+DEL:
  https://forum.arduino.cc/t/this-is-how-to-send-control-alt-delete-with-virtual-usb-keyboard-library/146305/2
