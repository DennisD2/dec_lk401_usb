#include <Arduino.h>
/*
 * LK401 keyboard to USB code
 * 
 * This code connects via Serial1 to a Digital DEC LK401 keyboard.
 * By using three tables (for unshifted, shifted and ctrl-ed key codes), it is controlled what
 * codes are sent via USB to USB host. Because the Arduino Keyboard module is used, the LK401 looks 
 * to the host computer like any other USB keyboard.
 * 
 * Open issues:
 * * §,^,° character not usable
 * * CTRL-codes mostly not working
 * * Code was written for a german layout keyboard, needs to be reworked for other languages
 * 
 */
#include "Keyboard.h"
#include "KeyboardLayout.h"

unsigned char convertCode(unsigned char inCode);

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

#define LK401_CMD_LED_OFF 0x11
#define LK401_CMD_LED_ON 0x13
#define LK401_CMD_KEY_CLICK_ON 0x1b
#define LK401_CMD_KEY_CLICK_OFF 0x99

// keycodes to send, unshifted, shifted and with CTRL
unsigned char k[256], s[256], c[256];

/* state variables */
boolean shift = false; /* Shift key is pressed */
boolean ctrl = false; /* CTRL key is pressed */
boolean altEmulation = false; /* emulate missing ALT key */
boolean shift_hold = false; /* reflects state of Shift Hold key */

unsigned char key_click_volume = 0;

unsigned char lastCode = 0; /* Last character sent */
// testing only
unsigned int testCode = 0;


void setup() {
  Keyboard.begin(KeyboardLayout_dec_lk401_AG);
  Serial.begin(115200);
  // Configure serial connection to LK401
  Serial1.begin(4800, SERIAL_8N1);
  
  delay(200);
  Serial.println("DEC LK401 to USB");
  delay(100);

  // set up k,s,c tables. Index is keycode from LK401. Value is char to send to USB
  k[0xbf] = '^'; s[0xbf] = 126; // ^/°
  
  k[0xc0] = '1'; s[0xc0] = '!';
  k[0xc1] = 'q'; s[0xc1] = 'Q';
  k[0xc2] = 'a'; s[0xc2] = 'A'; c[0xc2] = 210;
  k[0xc3] = 'y'; s[0xc3] = 'Y'; 
  k[0xc5] = '2'; s[0xc5] = '"';
  k[0xc6] = 'w'; s[0xc6] = 'W';
  k[0xc7] = 's'; s[0xc7] = 'S';
  k[0xc8] = 'x'; s[0xc8] = 'X';
  k[0xc9] = '<'; s[0xc9] = '>'; 
    k[0xcb] = '3'; s[0xcb] = 35; // wrong: expected §, got #
  k[0xcc] = 'e'; s[0xcc] = 'E'; c[0xcc] = 225;
  k[0xcd] = 'd'; s[0xcd] = 'D';
  k[0xce] = 'c'; s[0xce] = 'C'; 
  
  k[0xd0] = '4'; s[0xd0] = '$';
  k[0xd1] = 'r'; s[0xd1] = 'R';
  k[0xd2] = 'f'; s[0xd2] = 'F';
  k[0xd3] = 'v'; s[0xd3] = 'V';
  k[0xd4] = ' '; s[0xd4] = ' ';
  k[0xd6] = '5'; s[0xd6] = '%';
  k[0xd7] = 't'; s[0xd7] = 'T'; 
  k[0xd8] = 'g'; s[0xd8] = 'G';
  k[0xd9] = 'b'; s[0xd9] = 'B';
  k[0xdb] = '6'; s[0xdb] = '&';
  k[0xdc] = 'z'; s[0xdc] = 'Z';
  k[0xdd] = 'h'; s[0xdd] = 'H';
  k[0xde] = 'n'; s[0xde] = 'N';
   
  k[0xe0] = '7'; s[0xe0] = '/';
  k[0xe1] = 'u'; s[0xe1] = 'U';
  k[0xe2] = 'j'; s[0xe2] = 'J';
  k[0xe3] = 'm'; s[0xe3] = 'M';
  k[0xe5] = '8'; s[0xe5] = '(';
  k[0xe6] = 'i'; s[0xe6] = 'I';
  k[0xe7] = 'k'; s[0xe7] = 'K';
  k[0xe8] = ','; s[0xe8] = ';';
  k[0xea] = '9'; s[0xea] = ')';
  k[0xeb] = 'o'; s[0xeb] = 'O';
  k[0xec] = 'l'; s[0xec] = 'L';
  k[0xed] = '.'; s[0xed] = ':';
  k[0xef] = '0'; s[0xef] = '=';

  k[0xf0] = 'p'; s[0xf0] = 'P';
  
  k[0xf2] = 123; s[0xf2] = 124; // german kbd: ö/Ö
  k[0xf3] = '-'; s[0xf3] = '_'; // german kbd: -/_
  
    k[0xf5] = 64; s[0xf5] = 96; // german kbd: ´/`
  k[0xf6] = '+'; s[0xf6] = '*';  // german kbd: +/*
  k[0xf7] = '#'; s[0xf7] = '\''; // german kbd: #/'
  
  k[0xf9] = 127; s[0xf9] = '?';// german kbd: ß/?
  
  k[0xfa] = 125; s[0xfa] = 126; // german kbd: ü/Ü
  k[0xfb] = 91; s[0xfb] = 93; // german kbd: ä/Ä

  // Arrow keys
  k[0xa8] = KEY_RIGHT_ARROW; 
  k[0xa7] = KEY_LEFT_ARROW; 
  k[0xa9] = KEY_DOWN_ARROW; 
  k[0xaa] = KEY_UP_ARROW; 

  k[0xb1] = 39; // Gruppenumschaltung
  k[0xbc] = KEY_BACKSPACE; // Backspace, 0x08 also works
  k[0xbd] = KEY_RETURN; // // CR, 0xa also works
  k[0xbe] = KEY_TAB; // TAB, 0x9

  k[0x56] = KEY_F1; // F1
  k[0x57] = KEY_F2; // F2
  k[0x58] = KEY_F3; // F3
  k[0x59] = KEY_F4; // F4
  k[0x5a] = KEY_F5; // F5
  k[0x64] = KEY_F6; // F6
  k[0x65] = KEY_F7; // F7
  k[0x66] = KEY_F8; // F8
  k[0x67] = KEY_F9; // F9
  k[0x68] = KEY_F10; // F10
  k[0x71] = KEY_F11; // F11
  k[0x72] = KEY_F12; // F12
  k[0x73] = KEY_F13; // F13
  k[0x74] = KEY_F14; // F14
  k[0x80] = KEY_F17; // F17
  k[0x81] = KEY_F18; // F18
  k[0x82] = KEY_F19; // F19
  k[0x83] = KEY_F20; // F20

  k[0x7c] = 0xed; // Hilfe, mapped to KEY_MENU
  k[0x7d] = KEY_ESC; // 0x1b; // Ausführen, mapped to missing ESC key

  k[0x8a] = KEY_HOME; // Suchen, mapped to KEY_HOME
  k[0x8b] = KEY_INSERT; // Einfügen
  k[0x8c] = KEY_DELETE; // Löschen
  k[0x8d] = KEY_END; // Selektieren, mapped to KEY_END
  k[0x8e] = KEY_PAGE_UP; // Page Up
  k[0x8f] = KEY_PAGE_DOWN; // Page Down

  // numeric pad
  k[0xa1] = 39; // PF1
  k[0xa2] = 39; // PF2
  k[0xa3] = 39; // PF3
  k[0xa4] = 39; // PF4
  k[0x9d] = '7'; // 7
  k[0x9e] = '8'; // 8
  k[0x9f] = '9'; // 9
  k[0xa0] = '-'; // -
  k[0x99] = '4'; // 4
  k[0x9a] = '5'; // 5
  k[0x9b] = '6'; // 6
  k[0x9c] = ','; // ,
  k[0x96] = '1'; // 1
  k[0x97] = '2'; // 2
  k[0x98] = '3'; // 3
  k[0x95] = 10; // Eingabe
  k[0x92] = '0'; // 0
  k[0x94] = '.'; // .

  // Switch Shift LED off
  Serial1.write(LK401_CMD_LED_OFF);
  Serial1.write(0x80|LK401_LED_SHIFT);
}

void loop() {
  unsigned char inCode, outCode=0;
  boolean doSend = true;

  if (Serial1.available() <= 0) {
    return;
  }
  inCode = Serial1.read();

  switch (inCode) {
    case LK401_CODE_METRONOME:
      // 'metronom code' - last key is continuously pressed
      // we just resend last keycode
      outCode = lastCode;
      break;
      
    case LK401_CODE_SHIFT:
      // shift key is pressed
      shift=true;
      doSend=false;
      break;
    case LK401_CODE_CTRL:
      // CTRL key is pressed
      ctrl=true;
      doSend=false;
      break;
    case LK401_CODE_ALL_UPS:
      // shift and/or CTRL key is released
      shift=false;
      ctrl=false;
      doSend=false;
      break;

    case LK401_CODE_GRUPPENUMSCH:
      // emulate ALT key
      altEmulation= !altEmulation;
      doSend=false;
      break;    
      
    case LK401_CODE_SHIFT_HOLD:
      // shift hold key is pressed
      shift_hold = !shift_hold;
      doSend=false;
      if (shift_hold) {
        Serial1.write(LK401_CMD_LED_ON);
      } else {
        Serial1.write(LK401_CMD_LED_OFF);
      }
      Serial1.write(0x80|LK401_LED_SHIFT); 
      break;

    case LK401_CODE_F20:
      // we use F20 to control keyboard click audio level
      if (key_click_volume == 0) {
        Serial1.write(LK401_CMD_KEY_CLICK_OFF);
      } else {
        Serial1.write(LK401_CMD_KEY_CLICK_ON);
        Serial1.write(0x80|key_click_volume);
      }
      if (++key_click_volume == 8) {
        key_click_volume = 0;
      }
      break;
      
    default:
      outCode = convertCode(inCode);
      lastCode = outCode;
      break;
  }

/*
  outCode = ++testCode;
  if (testCode==238)
    testCode++;
*/
   
  Serial.print("LK401: ");
  Serial.print(inCode, HEX);
  Serial.print(", sending: ");
  Serial.println(outCode);

  if (doSend == true) {
    Keyboard.press(outCode, shift, ctrl);
    delay(20);
    Keyboard.releaseAll();
  }
}

unsigned char convertCode(unsigned char inCode) {
  if (shift || shift_hold) {
    return s[inCode];
  } 
  if (ctrl) {
    return c[inCode];
  }
  return k[inCode];
}
