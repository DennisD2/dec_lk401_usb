# Using a Digital DEC LK401 Keyboard via USB
This repo contains code to run the DEC LK401 via USB
at modern computers.

Most of the things work, I am writing these lines
on the LK401.

## Special keys
The following hints are for using the keyboard.

![DEC LK401AG](./images/dec_lk_401.png)

For standard characters, shifted keys and CTRL keys (like
CTRL-C etc.), the keyboard is exactly as one would expect from
any other keyboard. Same is with arrow keys, function keys 
F1-F19, special keys (insert, delete, backspace, CR, space,
scroll up, scroll down, tab). Also with the numeric key pad.

Special behaviour is:
* Bottom most left ```Zusatzfunktion``` key maps to ```AltGr``` (Alt Right). 
I need to
  do this because the keyboard has no ```Alt``` or ```AltGr``` keys at all.
  You need to press and release that key first, then enter the character key you want .
  So for the ```@``` character, press and release ```Zusatzfunktion```, then press the ```q``` key.
  To get the character that is written on top right of the key (like ```£``` for key ```3```), 
 press ```Shift```+```3```.
* "Ausführen" maps to ```ESC```
* Numeric key function keys ```PF1```-```PF4``` map to function keys 
 ```F21```-```F24```
* ```Suchen``` key maps to ```Go to Pos1``` function
* ```Selektieren``` maps map to ```Go to End```
* ```Hilfe``` maps to ```Menu``` key
* Function key ```F20``` controls the key click volume. Default is off. Pressing the key loops through the available 
  7 volume levels.
* At least on my german version of the keyboard, all "Zusatz*" keys
  except the bottom left one do not produce any key codes, this
  is burned into hardware or keyboard firmware and cannot be changed.

## Required hardware
The LK401 is connected via a Arduino Micro, which
owns a USB connector. The Arduino Micro appears to
the PC as a standard USB keyboard.

More information on the approach is [here](http://spurtikus.de/posts/electronics-usb-keyboard/).

## How to build
This project was created with [CLion](https://www.jetbrains.com/clion/).
It is a cmake based project and uses [platform.io](https://platformio.org/)

To install platform.io together with CLion, see here
https://blog.jetbrains.com/clion/2020/08/arduino-from-hobby-to-prof-p1/

After installation of tools above, the project can be build
with a mouse click in CLion, or on command line:
```shell
cmake --build ./cmake-build-micro --target all
```

## Getting the serial debug output
While getting the output in Arduino IDE is trivial,
without Arduino IDE we get it like this:
```shell
stty -F /dev/ttyACM0 1000000 raw -clocal -echo
cat /dev/ttyACM0
```
Replace ```/dev/ACM0``` with the correct device for your environment.

## Further reading and todos

How to send CTRL+ALT+DEL : https://forum.arduino.cc/t/this-is-how-to-send-control-alt-delete-with-virtual-usb-keyboard-library/146305/2

USB HUT Documentation [Link](./doc/Hut1_12v2.pdf)