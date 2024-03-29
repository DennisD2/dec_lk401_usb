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
#include "log.h"


/* state variables */
boolean shift_hold = false; /* reflects state of Shift Hold key */
int8_t key_click_volume = 0; /* key click volume, values see LK401_VOLUME_* defines */
unsigned char lastCode = 0; /* last character sent */

void enable401Mode();

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

void enable401Mode() {
    Serial1.write(LK401_CMD_ENABLE_LK401);
}

void setup() {
    Keyboard.begin(Keycodes_dec_lk401_AG);
    logSerialInit(115200);
    // Configure serial connection to LK401
    Serial1.begin(4800, SERIAL_8N1);

    delay(200);
    logSerial("DEC LK401 to USB");
    logLn();
    delay(100);

    // "Greeting" with LEDs, then switch LEDs off
    led(LK401_LED_LOCK, true);
    delay(200);
    led(LK401_LED_SHIFT, true);
    delay(200);
    led(LK401_LED_LOCK, false);
    delay(200);
    led(LK401_LED_SHIFT, false);

    // Set keyclick volume to off, keeping my nerves healthy
    keyClickVolume(LK401_VOLUME_0);

    // Enable 401 mode
    enable401Mode();

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
            Keyboard.press(lastCode, false);
            break;

        case LK401_CODE_SHIFT_LEFT:
            // shift key is pressed
            Keyboard.press(inCode, false);
            break;
        case LK401_CODE_SHIFT_RIGHT:
            // shift key is pressed
            Keyboard.press(inCode, false);
            break;
        case LK401_CODE_CTRL:
            // CTRL key is pressed
            Keyboard.press(inCode, false);
            break;
        case LK401_CODE_ALT_FUNCTION_LEFT:
            Keyboard.press(inCode, false);
            break;
        case LK401_CODE_ALT_FUNCTION_RIGHT:
            Keyboard.press(inCode, false);
            break;
        case LK401_CODE_ALL_UPS:
            // shift and/or CTRL key is released
            Keyboard.release(inCode, false);
            break;

        case LK401_CODE_SHIFT_HOLD:
            // shift hold key is pressed
            shift_hold = !shift_hold;
            Keyboard.press(inCode, shift_hold);
            led(LK401_LED_SHIFT, shift_hold);
            break;

        case LK401_CODE_F20:
            // we use F20 to control keyboard click audio level
            if (--key_click_volume == -1) {
                key_click_volume = LK401_VOLUME_0;
                // "ACK" volume zero with LED
                led(LK401_LED_LOCK, true);
                delay(200);
                led(LK401_LED_LOCK, false);
            }
            keyClickVolume(key_click_volume);
            break;

        default:
            lastCode = inCode;
            Keyboard.press(inCode, false);
            delay(20);
            Keyboard.release(inCode, false);
            break;
    }

    logSerial("LK401: 0x");
    logSerial(inCode, HEX);
    logSerial(", ");
    logSerial(inCode, DEC);
    logSerial(", SH=");
    logSerial(shift_hold);
    logLn();
}


