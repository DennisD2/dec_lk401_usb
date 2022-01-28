/*
  Keyboard.cpp

  Based on Arduino Library code
*/

#include "Keyboard.h"
#include "KeyboardLayout.h"

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
size_t Keyboard_::press(uint8_t k, uint8_t shift, uint8_t ctrl, uint8_t alt) {
    k = pgm_read_byte(_asciimap + k);
    Serial.print(" sending: ");
    Serial.println(k, HEX);
    if (!k) {
        setWriteError();
        return 0;
    }
    if (shift) {
        _keyReport.modifiers |= (KEY_LEFT_SHIFT-0x7f);
    }
    if (ctrl) {
        _keyReport.modifiers |= (KEY_LEFT_CTRL-0x7f);
    }
    if (alt) {
        //_keyReport.modifiers |= (KEY_RIGHT_ALT-0x7f) ;
        _keyReport.modifiers |= 0x40;   // AltGr = right Alt
    }
    if (k == ISO_REPLACEMENT) {
        k = ISO_KEY;
    }

	// Add k to the key report only if it's not already present
	// and if there is an empty slot.
	if (_keyReport.keys[0] != k && _keyReport.keys[1] != k &&
		_keyReport.keys[2] != k && _keyReport.keys[3] != k &&
		_keyReport.keys[4] != k && _keyReport.keys[5] != k) {

        int i;
		for (i=0; i<6; i++) {
			if (_keyReport.keys[i] == 0x00) {
				_keyReport.keys[i] = k;
				break;
			}
		}
		if (i == 6) {
			setWriteError();
			return 0;
		}
	}
	sendReport(&_keyReport);
	return 1;
}

// release() takes the specified key out of the persistent key report and
// sends the report.  This tells the OS the key is no longer pressed and that
// it shouldn't be repeated any more.
size_t Keyboard_::release(uint8_t k, uint8_t shift, uint8_t ctrl, uint8_t alt)
{
    k = pgm_read_byte(_asciimap + k);
    if (!k) {
        return 0;
    }
    if (alt) {
        _keyReport.modifiers &= ~(0x40);   // AltGr = right Alt
        k &= 0x3F;
    }
    if (shift) {
        _keyReport.modifiers &= ~(0x02);	// the left shift modifier
        k &= 0x7F;
    }
    if (ctrl) {
        _keyReport.modifiers &= ~(KEY_LEFT_CTRL-0x7f);	// the left ctrl modifier
        k &= 0x7F;
    }
    if (k == ISO_REPLACEMENT) {
        k = ISO_KEY;
    }

	// Test the key report to see if k is present.  Clear it if it exists.
	// Check all positions in case the key is present more than once (which it shouldn't be)
    uint8_t i;
	for (i=0; i<6; i++) {
		if (0 != k && _keyReport.keys[i] == k) {
			_keyReport.keys[i] = 0x00;
		}
	}

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

size_t Keyboard_::write(uint8_t c)
{
    uint8_t shift=0;
    uint8_t ctrl=0;
    uint8_t alt=0;
	uint8_t p = press(c, shift, ctrl, alt);	// Keydown
	release(c, shift, ctrl, alt);		// Keyup
	return p;		// just return the result of press() since release() almost always returns 1
}

size_t Keyboard_::write(const uint8_t *buffer, size_t size) {
	size_t n = 0;
	while (size--) {
		if (*buffer != '\r') {
			if (write(*buffer)) {
				n++;
			} else {
				break;
			}
		}
		buffer++;
	}
	return n;
}

Keyboard_ Keyboard;

#endif
