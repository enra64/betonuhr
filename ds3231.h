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

#ifndef DS3231_H
#define DS3231_H

#define __AVR_ATmega328P__

#include <Wire.h>
#include "mytime.h"


#define DS3231_I2C_ADDRESS 0x68

//error codes
#define ERR_NO_ERR 0
#define ERR_RTC_STOPPED 1
#define ERR_RTC_RECEIVE 2
#define ERR_RTC_WONKY 3
#define ERR_ALL_ZERO_RECEIVE 4

class DS3231
{
private:
  uint8_t bcdToDec(uint8_t val);
  uint8_t decToBcd(uint8_t val);
public:
  uint8_t readTime(MyTime* tm);
  uint8_t writeTime(MyTime* tm);
  void init();
};

#endif // DS3231_H
