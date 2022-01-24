# Using a Digital DEC LK401 Keyboard via USB
This repo contains code to run the DEC LK401 via USB
at modern computers.

Most of the things work, I am writing these lines
on the LK401.

## Required hardware
The LK401 is connected via a Arduino Micro, which
owns a USB connector. The Arduino Micro appears to
the PC as a standard USB keyboard.

More information on the approach is [here](http://spurtikus.de/posts/electronics-usb-keyboard/).

## How to build
This project was created with CLion.
It is a cmake based project and uses platform.io

To install platform.io together with CLion, see here
https://blog.jetbrains.com/clion/2020/08/arduino-from-hobby-to-prof-p1/

Command line:
```shell
cmake --build ./cmake-build-micro --target all
```

