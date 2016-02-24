/*
 * Copyright 2015 <copyright holder> <email>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#include "display.h"
#include "ds3231.h"

//set segments, enable digit, wait?, disable digit
void Display::enableDigit() {
    writeSegmentData(mData[mLastDisplayed]);
    switchDigit(DIGIT_PINS[mLastDisplayed], false);
}

void Display::disableDigit() {
    //disable the last activated digit
    switchDigit(DIGIT_PINS[mLastDisplayed], true);
    //change next displayed digit
    mLastDisplayed = (mLastDisplayed + 1) % 4;
}

void Display::switchDigit(uint8_t pin, bool state) {
    switch (pin) {
        case DIG_3:
            writePin(&PORTD, pin, state);
            break;
        default:
            writePin(&PORTB, pin, state);
    }
}

void Display::writePin(volatile uint8_t *port, int pin, bool val) {
    if (val)
        *port |= (1 << pin);
    else
        *port &= ~(1 << pin);
}

void Display::writeSegmentData(uint8_t data) {
    PORTD = data | (1 << 7);
}

void Display::processTime(MyTime *tm) {
    mData[0] = NUMBERS[tm->hour / 10];
    mData[1] = NUMBERS[tm->hour % 10];
    mData[2] = NUMBERS[tm->minute / 10];
    mData[3] = NUMBERS[tm->minute % 10];
}

void Display::byteWriteTest(uint8_t data) {
    writeSegmentData(NUMBERS[data]);
    switchDigit(DIG_1, true);
}

void Display::showError(uint8_t errCode) {
    mData[0] = CHARACTERS[0];
    mData[1] = CHARACTERS[1];
    mData[2] = CHARACTERS[1];
    mData[3] = NUMBERS[errCode];
}

void Display::init() {
    //we need all output pins on port d
    DDRD = 0xFF;
    //port b is ICSP and 3 digits
    DDRB |= (1 << DIG_4) | (1 << DIG_2) | (1 << DIG_1);
    initInterrupt();
}

//target is: normal mode, ON on overflow, OFF on compare match
void Display::initInterrupt() {
    cli();
    TCCR2A = 0;//wgm 00 for normal mode com 0000 for no oc toggling
    TCCR2B = (1 << CS21) | (1 << CS20);//F_CPU / 32 -> 250kHz
    TIMSK2 = (1 << OCIE2A) | (1 << TOIE2);//isr on ocr2a, ovf
    OCR2A = 250;
    sei();
}

void Display::onShortButtonPress() {
    if(mCurrentButtonState == set_hours){

    }
}

void Display::onLongButtonPress() {
    switch(mCurrentButtonState){
        case normal:
            mCurrentButtonState = set_hours;
            mSetHours = 8;
            break;
        case set_hours:
            mCurrentButtonState = set_minutes;
            mSetMinutes = 0;
            break;
        case set_minutes:
            mCurrentButtonState = normal;
            DS3231 writeTime;
            writeTime.writeTime(new MyTime(mSetMinutes, mSetHours));
            break;
    }
}
