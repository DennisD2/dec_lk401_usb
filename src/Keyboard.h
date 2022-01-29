/*
  Keyboard.h
  Based on Arduino Library code
*/

#ifndef KEYBOARD_h
#define KEYBOARD_h

#include "HID.h"

#if !defined(_USING_HID)

#warning "Using legacy HID core (non pluggable)"

#else

//================================================================================
//================================================================================
//  Keyboard

// Modifiers
#define KEY_LEFT_CTRL     0x80
#define KEY_LEFT_SHIFT    0x81
#define KEY_LEFT_ALT      0x82
#define KEY_LEFT_GUI      0x83
#define KEY_RIGHT_CTRL    0x84
#define KEY_RIGHT_SHIFT   0x85
#define KEY_RIGHT_ALT     0x86
#define KEY_RIGHT_GUI     0x87

// Supported keyboard layouts
extern const uint8_t Keycodes_dec_lk401_AG[];

// Low level key report: up to 6 keys and shift, ctrl etc at once
typedef struct
{
  uint8_t modifiers;
  uint8_t reserved;
  uint8_t keys[6];
} KeyReport;

class Keyboard_ : public Print
{
private:
  KeyReport _keyReport;
  const uint8_t *_asciimap;
  void sendReport(KeyReport* keys);
public:
  Keyboard_(void);
  void begin(const uint8_t *layout = Keycodes_dec_lk401_AG);
  void end(void);
  size_t write(uint8_t k){};
  size_t write(const uint8_t *buffer, size_t size){};
  size_t press(uint8_t k, uint8_t shiftHold, uint8_t alt);
  size_t release(uint8_t k, uint8_t shiftHold, uint8_t alt);
  void releaseAll(void);
};
extern Keyboard_ Keyboard;

#endif
#endif
