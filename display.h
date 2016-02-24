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

#ifndef DISPLAY_H
#define DISPLAY_H

#define __AVR_ATmega328P__

#include "avr/io.h"
#include "mytime.h"

//SIG_SEG in eagle, but these are digits
#define DIG_1 PB2
#define DIG_2 PB1
#define DIG_3 PD7
#define DIG_4 PB0

//these are the actual segments
#define SEG_1 PD0 //pd0 is connected to IN1 and IN8, in8 is not connected to jack shit
#define SEG_2 PD6
#define SEG_3 PD5
#define SEG_4 PD4
#define SEG_5 PD3
#define SEG_6 PD2
#define SEG_7 PD1

enum State {normal, set_hours, set_minutes};

// A   0
//B G 1 6
// E   4
//C F 2 5
// D   3

const uint8_t NUMBERS[] = {
        //76543210
        0b01101111,
        0b01100000,
        0b01011101,
        0b01111001,
        0b01110010,
        0b00111011,
        0b00111111,
        0b01100001,
        0b01111111,
        0b01111011
};

const uint8_t CHARACTERS[] = {
        0b00011111,//E
        0b00010100//r
};

const uint8_t DIGIT_PINS[] = {DIG_1, DIG_2, DIG_3, DIG_4};
const uint8_t SEGMENT_PINS[] = {SEG_1, SEG_2, SEG_3, SEG_4, SEG_5, SEG_6, SEG_7};

class Display {
private:
    uint8_t mLastDisplayed = 0;
    uint8_t mData[4];
    State mCurrentButtonState = normal;

    uint8_t mSetHours = 8;
    uint8_t mSetMinutes = 8;

    void writeSegmentData(uint8_t data);

    void switchDigit(uint8_t which, bool state);

    void writePin(volatile uint8_t *port, int pin, bool val);

    void initInterrupt();
public:

    void init();

    void byteWriteTest(uint8_t data);

    void onLongButtonPress();

    void onShortButtonPress();

    void enableDigit();

    void disableDigit();

    void processTime(MyTime *tm);

    void showError(uint8_t errCode);
};

#endif // DISPLAY_H
