#define __AVR_ATmega328P__

#include <Wire.h>
#include "display.h"
#include "mytime.h"
#include "ds3231.h"
#include "avr/interrupt.h"
#include "ButtonManager.h"

Display mDisplay;
DS3231 mRtc;
MyTime mTime;
ButtonManager *mButtonManager;

#define LED A2

void loop() {
    uint8_t err = mRtc.readTime(&mTime);
    if (err > 0)
        mDisplay.showError(err);
    else
        mDisplay.processTime(&mTime);
    mButtonManager->checkPressType();
}

void setup() {
    mRtc.init();

    mRtc.writeTime(&mTime);

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

ISR(PCINT1_vect){
    mButtonManager->toggled();
}