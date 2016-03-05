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

void Display::processTime() {
    unsigned long secondsSinceStart = millis() / 1000;
    unsigned long minutesSinceStart = secondsSinceStart / 60;
    unsigned long currentHoursOffset = minutesSinceStart / 60;
    unsigned long currentMinutesOffset = minutesSinceStart - currentHoursOffset * 60;

    mNormalTime->setTime(04 + currentMinutesOffset, 13 + currentHoursOffset);
    //MyTime *tm = mCurrentButtonState == normal ? mNormalTime : mChangeTime;
    if(mCurrentButtonState == STATE_NORMAL){
        mData[0] = NUMBERS[mNormalTime->hour / 10];
        mData[1] = NUMBERS[mNormalTime->hour % 10];
        mData[2] = NUMBERS[mNormalTime->minute / 10];
        mData[3] = NUMBERS[mNormalTime->minute % 10];
    }
    else{
        mData[0] = NUMBERS[mCurrentButtonState];//mChangeTime->hour / 10];
        mData[1] = NUMBERS[mChangeTime->hour % 10];
        mData[2] = NUMBERS[mChangeTime->minute / 10];
        mData[3] = NUMBERS[mChangeTime->minute % 10];
        //mCurrentButtonState = 9;
    }
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
    switch(mCurrentButtonState){
        case STATE_CHANGE_HOURS:
            mChangeTime->setHours((mChangeTime->hour + 1) % 24);
            //blink(true);
            break;
        case STATE_CHANGE_MINUTES:
            mChangeTime->setMinutes((mChangeTime->minute + 1) % 60);
            break;
        case STATE_NORMAL:
        default:
            break;
    }
}

void Display::onLongButtonPress() {
    if(mCurrentButtonState == 7){
        mCurrentButtonState = 0;
        //blink(false);
    }
    if (mCurrentButtonState == 3){
        mCurrentButtonState = 7;
        //blink(false);
    }
    if(mCurrentButtonState == 0) {
        mCurrentButtonState = 3;
        //mChangeTime = new MyTime(0, 8);
    }
}

void Display::blink(bool shortPress) {
    if(shortPress){
        digitalWrite(LED, HIGH);
        delay(10);
        digitalWrite(LED, LOW);
    }
    else{
        digitalWrite(LED, HIGH);
        delay(100);
        digitalWrite(LED, LOW);
    }
}

Display::Display() {
    mCurrentButtonState = STATE_NORMAL;
    //mChangeTime = new MyTime(0, 8);
}
