/*
 * Digital DEC LK401 german keyboard layout
 */

#include "KeyboardLayout.h"

#define RES 0x00 /* reserved */
#define UNUSED 0x00 /* unused */

extern const uint8_t Keycodes_dec_lk401_AG[256] PROGMEM = {
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        UNUSED,
        UNUSED,
        UNUSED,
        UNUSED,
        UNUSED,
        UNUSED,
        UNUSED,
        UNUSED,
        UNUSED,
        UNUSED,
        UNUSED,
        UNUSED,
        UNUSED,
        UNUSED,
        UNUSED,
        UNUSED,
        UNUSED,
        UNUSED,
        UNUSED,
        UNUSED,
        UNUSED,
        0x00, // Hold screen
        0x00, // Print screen
        0x00, // Set-Up
        0x3d, // F4
        0x00, // Break
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        0x00, // Interrupt
        0x00, // Resume
        0x00, // Cancel
        0x00, // Main screen
        0x00, // Exit
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        0x00, // undocumented code
        RES,
        0x44, // F11
        0x45, // F12
        0x68, // F13
        0x00, // Addtnl Options
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        0x76, // Help, mapped to KEY_MENU
        0x00, // Do
        RES,
        RES,
        0x6c, // F17
        0x6d, // F18
        0x6e, // F19
        0x6f, // F20
        RES,
        RES,
        RES,
        RES,
        RES,
        RES,
        0x4a, // Suchen, mapped to KEY_HOME
        0x49, // Insert
        0x4c, // Delete forward
        0x4d, // Selektieren mapped to KEY_END
        0x4b, // page up
        0x4e, // page down
        RES,
        RES,
        0x27, // 0
        RES,
        0x36, // .
        0x58, // Enter
        0x1e, // 1
        0x1f, // 2
        0x20, // 3
        0x21, // 4
        0x22, // 5
        0x23, // 6
        0x37, // ,
        0x24, // 7
        0x25, // 8
        0x26, // 9
        0x38, // -
        0x70, // PF1 mapped to F21
        0x71, // PF2 mapped to F22
        0x72, // PF3 mapped to F23
        0x73, // PF4 mapped to F24
        RES,
        RES,
        0x50, // left arrow
        0x4f, // right arrow
        0x51, // down arrow
        0x52, // up arrow
        RES,
        RES,
        RES,
        0x00, // Shift
        0x00, // Ctrl
        0x00, // Lock
        0x00, // Compose
        RES,
        0x00, // All Ups
        0x00, // Metronome
        0x00, // Output error
        0x00, // Input error
        0x00, // KBD LOCKED ACK
        0x00, // TEST MODE
        0x00, // Prefix to keys down
        0x00, // MODE CHANGE ACK
        RES,
        0x2a, // backspace
        0x28, // return
        0x2b, // tab
        0x35, // ^
        0x1e, // 1
        0x14, // q
        0x04, // a
        0x1d, // y
        RES,
        0x1f, // 2
        0x1a, // w
        0x16, // s
        0x1b, // x
        0x32, // <
        RES,
        0x20, // 3
        0x08, // e
        0x07, // d
        0x06, // c
        RES,
        0x21, // 4
        0x15, // r
        0x09, // f
        0x19, // v
        0x2c, // SPACE
        RES,
        0x22, // 5
        0x17, // t
        0x0a, // g
        0x05, // b
        RES,
        0x23, // 6
        0x1c, // z
        0x0b, // h
        0x11, // n
        RES,
        0x24, // 7
        0x18, // u
        0x0d, // j
        0x10, // m
        RES,
        0x25, // 8
        0x0c, // i
        0x0e, // k
        0x36, // ,
        RES,
        0x26, // 9
        0x12, // o
        0x0f, // l
        0x37, // .
        RES,
        0x27, // 0
        0x13, // p
        RES,
        0x33, // ö
        0x38, // -
        RES,
        0x2e, // ´
        0x30, // +
        0x31, // #
        RES,
        0x2d, // ß
        0x2f, // ü
        0x34, // ä
        RES,
        RES,
        RES,
        RES
};
