/*
  Keyboard.cpp

  Based on Arduino Library code

  For the modifier codes, I found not much info.
  This here:
  Also both the left and right hand modifiers appear to be mapped:

\arduino-1.0.1\hardware\teensy\cores\teensy\Keylayouts.h:

#define MODIFIERKEY_CTRL ( 0x01 | 0x8000 )
#define MODIFIERKEY_SHIFT ( 0x02 | 0x8000 )
#define MODIFIERKEY_ALT ( 0x04 | 0x8000 )
#define MODIFIERKEY_GUI ( 0x08 | 0x8000 )
#define MODIFIERKEY_LEFT_CTRL ( 0x01 | 0x8000 )
#define MODIFIERKEY_LEFT_SHIFT ( 0x02 | 0x8000 )
#define MODIFIERKEY_LEFT_ALT ( 0x04 | 0x8000 )
#define MODIFIERKEY_LEFT_GUI ( 0x08 | 0x8000 )
#define MODIFIERKEY_RIGHT_CTRL ( 0x10 | 0x8000 )
#define MODIFIERKEY_RIGHT_SHIFT ( 0x20 | 0x8000 )
#define MODIFIERKEY_RIGHT_ALT ( 0x40 | 0x8000 )
#define MODIFIERKEY_RIGHT_GUI ( 0x80 | 0x8000 )

 I found in some forum for teensy hardware
 https://forum.pjrc.com/threads/1269-Observations-on-Teensy-USB-keyboard-support
*/

#include "Keyboard.h"
#include "KeyboardLayout.h"
#include "log.h"

#if defined(_USING_HID)

//================================================================================
//================================================================================
//  Keyboard

static const uint8_t _hidReportDescriptor[] PROGMEM = {

    //  Keyboard
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)  // 47
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x85, 0x02,                    //   REPORT_ID (2)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)

    0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)

    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)

    0x95, 0x06,                    //   REPORT_COUNT (6)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x73,                    //   LOGICAL_MAXIMUM (115)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)

    0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x73,                    //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xc0,                          // END_COLLECTION
};

Keyboard_::Keyboard_(void)
{
	static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
	HID().AppendDescriptor(&node);
	_asciimap = Keycodes_dec_lk401_AG;
}

void Keyboard_::begin(const uint8_t *layout)
{
	_asciimap = layout;
}

void Keyboard_::end(void)
{
}

void Keyboard_::sendReport(KeyReport* keys)
{
	HID().SendReport(2,keys,sizeof(KeyReport));
}

uint8_t USBPutChar(uint8_t c);

// press() adds the specified key (printing, non-printing, or modifier)
// to the persistent key report and sends the report.  Because of the way
// USB HID works, the host acts like the key remains pressed until we
// call release(), releaseAll(), or otherwise clear the report and resend.
size_t Keyboard_::press(uint8_t k, uint8_t shiftHold) {
    k = pgm_read_byte(_asciimap + k);
    logSerial(" press: 0x");
    logSerial(k, HEX);
    logSerial( ", ");
    logSerial(k, DEC);
    logLn();

    if (k == LK401_CODE_SHIFT_LEFT) {
        _keyReport.modifiers |= (KEY_LEFT_SHIFT-0x7f);
        k=0x00;
    }
    if (k == LK401_CODE_SHIFT_RIGHT) {
        _keyReport.modifiers |= (KEY_RIGHT_SHIFT-0x7f);
        k=0x00;
    }
    if (k == LK401_CODE_CTRL) {
        _keyReport.modifiers |= (KEY_LEFT_CTRL-0x7f);
        k=0x00;
    }
    if (k == LK401_CODE_ALT_FUNCTION_LEFT) {
        //_keyReport.modifiers |= (KEY_LEFT_ALT-0x7f) ;
        _keyReport.modifiers |= 0x04;   // Left Alt
        k=0x00;
    }
    if (k == LK401_CODE_ALT_FUNCTION_RIGHT) {
        //_keyReport.modifiers |= (KEY_LEFT_ALT-0x7f) ;
        _keyReport.modifiers |= 0x40;   // AltGr = right Alt
        k=0x00;
    }

    if (k == LK401_CODE_SHIFT_HOLD) {
        if (shiftHold) {
            _keyReport.modifiers |= (KEY_LEFT_SHIFT-0x7f);	// the left shift modifier
        } else {
            _keyReport.modifiers &= ~(0x02); // the left shift modifier
        };
        k=0x00;
    }

    _keyReport.keys[0] = k;
	sendReport(&_keyReport);
	return 1;
}

// release() takes the specified key out of the persistent key report and
// sends the report.  This tells the OS the key is no longer pressed and that
// it shouldn't be repeated any more.
size_t Keyboard_::release(uint8_t k, uint8_t shiftHold)
{
    k = pgm_read_byte(_asciimap + k);
    logSerial(" release: ");
    logSerial(k, HEX);
    logSerial( ", ");
    logSerial(k, DEC);
    logLn();

    if (k == LK401_CODE_ALL_UPS) {
        // All Up: Shift Up, CTRL Up, AltGr Up
        _keyReport.modifiers &= ~(0x02); // the left shift modifier
        _keyReport.modifiers &= ~(0x20); // the right shift modifier
        _keyReport.modifiers &= ~(KEY_LEFT_CTRL-0x7f);	// the left ctrl modifier
        _keyReport.modifiers &= ~(KEY_RIGHT_CTRL-0x7f);	// the right ctrl modifier
        _keyReport.modifiers &= ~(0x40); // AltGr = right Alt
        _keyReport.modifiers &= ~(0x4); // Left Alt
    }

    // release key
    _keyReport.keys[0] = 0x00;
	sendReport(&_keyReport);
	return 1;
}

void Keyboard_::releaseAll(void)
{
	_keyReport.keys[0] = 0;
	_keyReport.keys[1] = 0;
	_keyReport.keys[2] = 0;
	_keyReport.keys[3] = 0;
	_keyReport.keys[4] = 0;
	_keyReport.keys[5] = 0;
	_keyReport.modifiers = 0;
	sendReport(&_keyReport);
}

Keyboard_ Keyboard;

#endif
