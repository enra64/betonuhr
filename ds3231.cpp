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

#include "ds3231.h"

uint8_t DS3231::bcdToDec(uint8_t val){ return ((val / 16 * 10) + (val % 16)); }
uint8_t DS3231::decToBcd(uint8_t val){ return( (val/10*16) + (val%10) ); }

void DS3231::init()
{
  Wire.begin();
}

uint8_t DS3231::readTime(MyTime* tm)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS); // reset DS1307 register pointer 
  Wire.write(0);
  
  if (Wire.endTransmission())                //rtc is stopped?
    return ERR_RTC_STOPPED;
    
  if (Wire.requestFrom(DS3231_I2C_ADDRESS, 7))       // report any receive esrrors
    return ERR_RTC_RECEIVE;
    
  if(Wire.available() <7)
    return ERR_RTC_WONKY;

  tm->second = bcdToDec(Wire.read() & 0x7F);
  tm->minute = bcdToDec(Wire.read());
  tm->hour = bcdToDec(Wire.read());
  tm->dow = bcdToDec(Wire.read());
  tm->day = bcdToDec(Wire.read());
  tm->month = bcdToDec(Wire.read());
  tm->year = bcdToDec(Wire.read()) + 2000;
  return tm->isAllZero();//returns 4 if everything is zero, 0 otherwise
}

uint8_t DS3231::writeTime(MyTime* tm){
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(tm->second)); // set seconds
  Wire.write(decToBcd(tm->minute)); // set minutes
  Wire.write(decToBcd(tm->hour)); // set hours
  Wire.write(decToBcd(tm->dow)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(tm->day)); // set date (1 to 31)
  Wire.write(decToBcd(tm->month)); // set month
  Wire.write(decToBcd(tm->year)); // set year (0 to 99)
  Wire.endTransmission();
  return 0;
}
