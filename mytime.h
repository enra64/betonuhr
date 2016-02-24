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

#ifndef MYTIME_H
#define MYTIME_H

#define __AVR_ATmega328P__

#include <Arduino.h>

class MyTime {
private:
    uint8_t isDaylightSavingsTime();

public:
    MyTime();

    MyTime(uint8_t m, uint8_t h);

    uint8_t isAllZero();

    uint8_t second, minute = 01, hour = 23, dow, day, month, year;

    void setTime(uint8_t m, uint8_t h);
};

#endif // MYTIME_H
