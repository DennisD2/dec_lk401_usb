#include <Arduino.h>
/*
 * LK401 keyboard to USB code
 * 
 * This code connects via Serial1 to a Digital DEC LK401 keyboard.
 * By using a table, it is controlled what
 * codes are sent via USB to USB host. Because the Arduino Keyboard module is used, the LK401 looks 
 * to the host computer like any other USB keyboard.
 * 
 * Open issues:
 * * ESC is on "Ausführen" key (LK401 has no ESC key)
 * * Code was written for a german layout keyboard, needs to be reworked for other languages
 *
 */
#include "Keyboard.h"
#include "KeyboardLayout.h"

// Defines from LK401 keyboard
#define LK401_CODE_METRONOME 0xb4
#define LK401_CODE_SHIFT 0xae
#define LK401_CODE_CTRL 0xaf
#define LK401_CODE_ALL_UPS 0xb3
#define LK401_CODE_SHIFT_HOLD 0xb0
#define LK401_CODE_F20 0x83
/* 'Gruppenumschaltung' */
#define LK401_CODE_GRUPPENUMSCH 0xb1

#define LK401_LED_SHIFT 0x4
#define LK401_LED_LOCK 0x8

#define LK401_CMD_LED_OFF 0x11
#define LK401_CMD_LED_ON 0x13
#define LK401_CMD_KEY_CLICK_ON 0x1b
#define LK401_CMD_KEY_CLICK_OFF 0x99

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

/* state variables */
boolean shift = false; /* Shift key is pressed */
boolean ctrl = false; /* CTRL key is pressed */
boolean alt_emul = false; /* emulate missing ALT key */
boolean shift_hold = false; /* reflects state of Shift Hold key */
unsigned char key_click_volume = 0;
unsigned char lastCode = 0; /* Last character sent */

void led(uint8_t id, uint8_t on) {
    if (on) {
        Serial1.write(LK401_CMD_LED_ON);
    } else {
        Serial1.write(LK401_CMD_LED_OFF);
    }
    Serial1.write(0x80 | id);
}

void keyClickVolume(uint8_t volume) {
    if (volume == LK401_VOLUME_0) {
        Serial1.write(LK401_CMD_KEY_CLICK_OFF);
    } else {
        Serial1.write(LK401_CMD_KEY_CLICK_ON);
        Serial1.write(0x80 | volume);
    }
}

void setup() {
    Keyboard.begin(Keycodes_dec_lk401_AG);
    Serial.begin(115200);
    // Configure serial connection to LK401
    Serial1.begin(4800, SERIAL_8N1);

    delay(200);
    Serial.println("DEC LK401 to USB");
    delay(100);

    // "Greeting" with LEDs, then switch LEDs off
    led(LK401_LED_SHIFT, true);
    delay(200);
    led(LK401_LED_LOCK, true);
    delay(200);
    led(LK401_LED_SHIFT, false);
    delay(200);
    led(LK401_LED_LOCK, false);

    // Set keyclick volume to off, keeping my nerves healthy
    keyClickVolume(LK401_VOLUME_0);

    Keyboard.releaseAll();
}

void loop() {
    unsigned char inCode; //, outCode = 0;

    if (Serial1.available() <= 0) {
        return;
    }
    inCode = Serial1.read();

    switch (inCode) {
        case LK401_CODE_METRONOME:
            // 'metronome code' - last key is continuously pressed
            // we just resend last keycode
            Keyboard.press(lastCode, false, false, false);
            break;

        case LK401_CODE_SHIFT:
            // shift key is pressed
            shift = true;
            Keyboard.press(inCode, true, false, false);
            break;
        case LK401_CODE_CTRL:
            // CTRL key is pressed
            ctrl = true;
            Keyboard.press(inCode, false, true, false);
            break;
        case LK401_CODE_ALL_UPS:
            // shift and/or CTRL key is released
            shift = false;
            ctrl = false;
            Keyboard.release(inCode, true, true, false);
            break;

        case LK401_CODE_GRUPPENUMSCH:
            // emulate ALT key
            alt_emul = true;
            Keyboard.press(inCode, false, false, true);
            led(LK401_LED_LOCK, alt_emul);
            break;

        case LK401_CODE_SHIFT_HOLD:
            // shift hold key is pressed
            shift_hold = !shift_hold;
            Keyboard.press(inCode, shift_hold, false, false);
            led(LK401_LED_SHIFT, shift_hold);
            break;

        case LK401_CODE_F20:
            // we use F20 to control keyboard click audio level
            keyClickVolume(key_click_volume);
            if (++key_click_volume == 9) {
                key_click_volume = 0;
            }
            break;

        default:
            lastCode = inCode;
            Keyboard.press(inCode, shift | shift_hold, ctrl, alt_emul);
            delay(20);
            Keyboard.release(inCode, shift | shift_hold, ctrl, alt_emul);

            if (alt_emul) {
                alt_emul=false;
                Keyboard.release(inCode, false, false, true);
                led(LK401_LED_LOCK, alt_emul);
            }
            break;
    }

    Serial.print("LK401: ");
    Serial.print(inCode, HEX);
    Serial.print(", SHCA=");
    Serial.print(shift);
    Serial.print(shift_hold);
    Serial.print(ctrl);
    Serial.println(alt_emul);
}

