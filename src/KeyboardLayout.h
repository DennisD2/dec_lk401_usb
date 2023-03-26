/*
  KeyboardLayout.h

  This file is not part of the public API. It is meant to be included
  only in Keyboard.cpp and the keyboard layout files. Layout files map
  ASCII character codes to keyboard scan codes (technically, to USB HID
  Usage codes), possibly altered by the SHIFT or ALT_GR modifiers.

  == Creating your own layout ==

  In order to create your own layout file, copy an existing layout that
  is similar to yours, then modify it to use the correct keys. The
  layout is an array in ASCII order. Each entry contains a scan code,
  possibly modified by "|SHIFT" or "|ALT_GR", as in this excerpt from
  the Italian layout:

      0x35,          // bslash
      0x30|ALT_GR,   // ]
      0x2e|SHIFT,    // ^

  Do not change the control characters (those before scan code 0x2c,
  corresponding to space). Do not attempt to grow the table past DEL. Do
  not use both SHIFT and ALT_GR on the same character: this is not
  supported. Unsupported characters should have 0x00 as scan code.

  For a keyboard with an ISO physical layout, use the scan codes below:

      +---+---+---+---+---+---+---+---+---+---+---+---+---+-------+
      |35 |1e |1f |20 |21 |22 |23 |24 |25 |26 |27 |2d |2e |BackSp |
      +---+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-----+
      | Tab |14 |1a |08 |15 |17 |1c |18 |0c |12 |13 |2f |30 | Ret |
      +-----++--++--++--++--++--++--++--++--++--++--++--++--++    |
      |CapsL |04 |16 |07 |09 |0a |0b |0d |0e |0f |33 |34 |31 |    |
      +----+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+---+----+
      |Shi.|32 |1d |1b |06 |19 |05 |11 |10 |36 |37 |38 |  Shift   |
      +----+---++--+-+-+---+---+---+---+---+--++---+---++----+----+
      |Ctrl|Win |Alt |                        |AlGr|Win |Menu|Ctrl|
      +----+----+----+------------------------+----+----+----+----+

  The ANSI layout is identical except that key 0x31 is above (rather
  than next to) Return, and there is not key 0x32.

  Give a unique name to the layout array, then declare it in Keyboard.h
  with a line of the form:

    extern const uint8_t KeyboardLayout_xx_YY[];

  == Encoding details ==

  All scan codes are less than 0x80, which makes bit 7 available to
  signal that a modifier (Shift or AltGr) is needed to generate the
  character. With only one exception, keys that are used with modifiers
  have scan codes that are less than 0x40. This makes bit 6 available
  to signal whether the modifier is Shift or AltGr. The exception is
  0x64, the key next next to Left Shift on the ISO layout (and absent
  from the ANSI layout). We handle it by replacing its value by 0x32 in
  the layout arrays.
*/

#include <Arduino.h>

#define SHIFT 0x80
#define ALT_GR 0xc0
#define ISO_KEY 0x64
#define ISO_REPLACEMENT 0x32

// Defines from LK401 keyboard
#define LK401_CODE_METRONOME 0xb4
#define LK401_CODE_SHIFT_LEFT 0xae
#define LK401_CODE_SHIFT_RIGHT 0xab
#define LK401_CODE_CTRL 0xaf
#define LK401_CODE_ALL_UPS 0xb3
#define LK401_CODE_SHIFT_HOLD 0xb0
#define LK401_CODE_F20 0x83

/* 'Gruppenumschaltung' */
#define LK401_CODE_COMPOSE_LEFT 0xb1
#define LK401_CODE_COMPOSE_RIGHT 0xad
/* Zusatzfunktion */
#define LK401_CODE_ALT_FUNCTION_LEFT 0xac
#define LK401_CODE_ALT_FUNCTION_RIGHT 0xb2

#define LK401_LED_SHIFT 0x4
#define LK401_LED_LOCK 0x8

#define LK401_CMD_LED_OFF 0x11
#define LK401_CMD_LED_ON 0x13
#define LK401_CMD_KEY_CLICK_ON 0x1b
#define LK401_CMD_KEY_CLICK_OFF 0x99

// Enable 401 mode, gives access to LAlt, RAlt, RCompose and RShift.
// See Linux driver module lkkbd.c
#define LK401_CMD_ENABLE_LK401 0xe9

// _0=off, _7=highest,
#define LK401_VOLUME_0 0x8
#define LK401_VOLUME_1 0x7
#define LK401_VOLUME_2 0x6
#define LK401_VOLUME_3 0x5
#define LK401_VOLUME_4 0x4
#define LK401_VOLUME_5 0x3
#define LK401_VOLUME_6 0x2
#define LK401_VOLUME_7 0x1
#define LK401_VOLUME_8 0x0