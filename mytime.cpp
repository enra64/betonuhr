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

#include "mytime.h"
#include "ds3231.h"

uint8_t MyTime::isDaylightSavingsTime() {
    //month < march and < october, it must be dst
    if (month > 3 && month < 10)
        return 1;
    //super advanced last sunday of the week heuristic
    if (month == 3 && day > 21)//after the 21., it should be dst in most cases
        return 1;
    if (month == 10 && day < 21)
        return 1;
    return 0;
}

uint8_t MyTime::isAllZero() {
    if (second == 0 && minute == 0 && hour == 0
        && dow == 0 && day == 0 && month == 0 && year == 0)
        return ERR_ALL_ZERO_RECEIVE;
    return ERR_NO_ERR;
}

void MyTime::setTime(uint8_t m, uint8_t h) {
    minute = m;
    hour = h;
}

MyTime::MyTime() {
    minute = 0;
    hour = 0;
}

MyTime::MyTime(uint8_t m, uint8_t h) {
    setTime(m, h);
}

void MyTime::setMinutes(uint8_t m) {
    minute = m;
}

void MyTime::setHours(uint8_t h) {
    hour = h;
}
