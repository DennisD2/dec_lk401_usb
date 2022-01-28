/*
 * Digital DEC LK401 german keyboard layout.
 */

#include "KeyboardLayout.h"
#include "Keyboard.h"

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
        0x00,          //
        0x00,          //
        0x00,          //
        KEY_F4,          //
        0x00,          //
        RES,          //
        RES,          //
        RES,          //
        RES,          //
        RES,          //
        RES,          //
        RES,          //
        RES,          //
        RES,          //
        0x00,          //
        0x00,          //
        0x00,          //
        0x00,          //
        0x00,          //
        RES,          //
        RES,          //
        RES,          //
        RES,          //
        RES,          //
        RES,          //
        0x00,          //
        RES,          //
        KEY_F11,          //
        KEY_F12,          //
        KEY_F13,          //
        0x00,          //
        RES,          //
        RES,          //
        RES,          //
        RES,          //
        RES,          //
        RES,          //
        RES,          //
        KEY_MENU,          // Help, mapped to KEY_MENU
        0x00,          //
        RES,          //
        RES,          //
        KEY_F17,          //
        KEY_F18,          //
        KEY_F19,          //
        KEY_F20,          //
        RES,          //
        RES,          //
        RES,          //
        RES,          //
        RES,          //
        RES,          //
        KEY_HOME,          // Suchen, mapped to KEY_HOME
        KEY_INSERT,          //
        KEY_DELETE,          //
        KEY_END,          // Selektieren mapped to KEY_END
        KEY_PAGE_UP,          //
        KEY_PAGE_DOWN,          //
        RES,          //
        RES,          //
        '0',          //
        RES,          //
        '.',          //
        KEY_RETURN,          // or 10 ???
        '1',          //
        '2',          //
        '3',          //
        '4',          //
        '5',          //
        '6',          //
        ',',          //
        '7',          //
        '8',          //
        '9',          //
        '-',          //
        KEY_F21,          //
        KEY_F22,          //
        KEY_F23,          //
        KEY_F24,          //
        RES,          //
        RES,          //
        KEY_LEFT_ARROW,          //
        KEY_RIGHT_ARROW,          //
        KEY_DOWN_ARROW,          //
        KEY_UP_ARROW,          //
        RES,          //
        RES,          //
        RES,          //
        0x00,          // Shift
        0x00,          // Ctrl
        0x00,          // Lock
        0x00,          // Compose
        RES,          //
        0x00,          // All Ups
        0x00,          // Metronome
        0x00,          // Output error
        0x00,          // Input error
        0x00,          // KBD LOCKED ACK
        0x00,          // TEST MODE
        0x00,          // Prefix to keys down
        0x00,          // MODE CHANGE ACK
        RES,          //
        KEY_BACKSPACE,          //
        KEY_RETURN,    //
        KEY_TAB,          //
        0x00,          // soll ~
        0x1e,          // 1
        0x14,          // q
        0x04,          // a
        0x1d,          // y
        RES,
        0x1f,          // 2
        0x1a,          // w
        0x16,          // s
        0x1b,          // x
        '>',          //
        RES,
        0x20,          // 3
        0x08,          // e
        0x07,          // d
        0x06,          // c
        RES,
        0x21,          // 4
        0x15,          // r
        0x09,          // f
        0x19,          // v
        ' ',          // SPACE
        RES,
        0x22,          // 5
        0x17,          // t
        0x0a,          // g
        0x05,          // b
        RES,
        0x23,          // 6
        0x1c,          // z
        0x0b,          // h
        0x11,          // n
        RES,
        0x24,          // 7
        0x18,          // u
        0x0d,          // j
        0x10,          // m
        RES,
        0x25,          // 8
        0x0c,          // i
        0x0e,          // k
        '"',          // ???
        RES,
        0x26,          // 9
        0x12,          // o
        0x0f,          // l
        '.',          // ???
        RES,
        0x27,          // 0
        0x13,          // p
        RES,
        ':',          // ???
        '?',          // ???
        RES,
        '+',          // ???
        '}',          // ???
        '|',          // ???
        RES,
        '_',          // ???
        '{',          // ???
        ',',          // ???
        RES,
        RES,
        RES,
        RES
};

extern const uint8_t KeyboardLayout_dec_lk401_AG[129] PROGMEM = {
                0x00,          // NUL
                0x00,          // SOH
                0x00,          // STX
                0x00,          // ETX
                0x00,          // EOT
                0x00,          // ENQ
                0x00,          // ACK
                0x00,          // BEL
                0x2a,          // BS  Backspace
                0x2b,          // TAB Tab
                0x28,          // LF  Enter
                0x00,          // VT
                0x00,          // FF
                0x00,          // CR
                0x00,          // SO
                0x00,          // SI
                0x00,          // DEL
                0x00,          // DC1
                0x00,          // DC2
                0x00,          // DC3
                0x00,          // DC4
                0x00,          // NAK
                0x00,          // SYN
                0x00,          // ETB
                0x00,          // CAN
                0x00,          // EM
                0x00,          // SUB
                0x00,          // ESC
                0x00,          // FS
                0x00,          // GS
                0x00,          // RS
                0x00,          // US

                0x2c,          // ' '
                0x1e|SHIFT,    // !
                0x1f|SHIFT,    // "
                0x31,          // #
                0x21|SHIFT,    // $
                0x22|SHIFT,    // %
                0x23|SHIFT,    // &
                0x31|SHIFT,    // '
                0x25|SHIFT,    // (
                0x26|SHIFT,    // )
                0x30|SHIFT,    // *
                0x30,          // +
                0x36,          // ,
                0x38,          // -
                0x37,          // .
                0x24|SHIFT,    // /
                0x27,          // 0
                0x1e,          // 1
                0x1f,          // 2
                0x20,          // 3
                0x21,          // 4
                0x22,          // 5
                0x23,          // 6
                0x24,          // 7
                0x25,          // 8
                0x26,          // 9
                0x37|SHIFT,    // :
                0x36|SHIFT,    // ;
                0x32,          // <
                0x27|SHIFT,    // =
                0x32|SHIFT,    // >
                0x2d|SHIFT,    // ?
                0x2e, // 0x14|ALT_GR,   // @ -> ´
                0x04|SHIFT,    // A
                0x05|SHIFT,    // B
                0x06|SHIFT,    // C
                0x07|SHIFT,    // D
                0x08|SHIFT,    // E
                0x09|SHIFT,    // F
                0x0a|SHIFT,    // G
                0x0b|SHIFT,    // H
                0x0c|SHIFT,    // I
                0x0d|SHIFT,    // J
                0x0e|SHIFT,    // K
                0x0f|SHIFT,    // L
                0x10|SHIFT,    // M
                0x11|SHIFT,    // N
                0x12|SHIFT,    // O
                0x13|SHIFT,    // P
                0x14|SHIFT,    // Q
                0x15|SHIFT,    // R
                0x16|SHIFT,    // S
                0x17|SHIFT,    // T
                0x18|SHIFT,    // U
                0x19|SHIFT,    // V
                0x1a|SHIFT,    // W
                0x1b|SHIFT,    // X
                0x1d|SHIFT,    // Y
                0x1c|SHIFT,    // Z
                0x34,       // 0x25|ALT_GR,   // [ -> ä
                0x2d|ALT_GR,   // bslash
                0x34|SHIFT, // 0x26|ALT_GR,   // ] -> Ä
                0x00,          // ^  not supported (requires dead key + space)
                0x38|SHIFT,    // _
                0x2e|SHIFT, // 0x00,          // `  not supported (requires dead key + space)
                0x04,          // a
                0x05,          // b
                0x06,          // c
                0x07,          // d
                0x08,          // e
                0x09,          // f
                0x0a,          // g
                0x0b,          // h
                0x0c,          // i
                0x0d,          // j
                0x0e,          // k
                0x0f,          // l
                0x10,          // m
                0x11,          // n
                0x12,          // o
                0x13,          // p
                0x14,          // q
                0x15,          // r
                0x16,          // s
                0x17,          // t
                0x18,          // u
                0x19,          // v
                0x1a,          // w
                0x1b,          // x
                0x1d,          // y
                0x1c,          // z
                0x33,       // 0x24|ALT_GR,   // { -> ö
                0x33|SHIFT, // 0x32|ALT_GR,   // | -> Ö
                0x2f,       // 0x27|ALT_GR,   // } -> ü
                0x2f|SHIFT, // 0x30|ALT_GR,   // ~ -> Ü
                0x2d,        // 0x00           // DEL -> ß 0x2d
                0x40        // CTRL+ALT+DEL
        };
