#define __AVR_ATmega328P__

#include <Wire.h>
#include "display.h"
#include "mytime.h"
#include "ds3231.h"
#include "avr/interrupt.h"
#include "ButtonManager.h"

Display mDisplay;
ButtonManager *mButtonManager;

#define LED A2

void loop() {
    mDisplay.processTime();
    mButtonManager->checkPressType();
}

void setup() {
    mDisplay.init();

    mButtonManager = new ButtonManager();

    pinMode(LED, OUTPUT);
}

ISR(TIMER2_OVF_vect) {
    mDisplay.enableDigit();
}

ISR(TIMER2_COMPA_vect) {
    mDisplay.disableDigit();
}