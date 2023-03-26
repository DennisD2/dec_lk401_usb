//
// Created by dennis on 04.02.22.
//
#include <Arduino.h>

#ifndef KEYBOARD_LOG_H
#define KEYBOARD_LOG_H

#define DO_LOGGING

void logSerialInit(unsigned long rate);
void logSerial(const String& s);
void logSerial(unsigned char s, int base = 10);
void logLn();

#endif //KEYBOARD_LOG_H
