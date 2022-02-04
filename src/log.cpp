//
// Created by dennis on 04.02.22.
//
#include <WString.h>
#include "log.h"

void logSerialInit(unsigned long rate) {
#ifdef DO_LOGGING
    Serial.begin(rate);
#endif
}
void logSerial(const String& s) {
#ifdef DO_LOGGING
    Serial.print(s);
#endif
}

void logSerial(unsigned char s, int base) {
#ifdef DO_LOGGING
    Serial.print(s, base);
#endif
}

void logLn() {
#ifdef DO_LOGGING
    Serial.println();
#endif
}