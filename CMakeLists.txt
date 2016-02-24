cmake_minimum_required(VERSION 3.3)
project(clion_source)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Os")

include_directories(/opt/arduino-1.6.6/hardware/arduino/avr/cores/arduino /opt/arduino-1.6.6/hardware/tools/avr/avr/include /opt/arduino-1.6.6/hardware/arduino/avr/variants/standard)
include_directories(/opt/arduino/hardware/arduino/avr/cores/arduino /opt/arduino-1.6.6/hardware/arduino/avr/libraries/Wire/ /opt/arduino/hardware/tools/avr/avr/include /opt/arduino/hardware/arduino/avr/variants/standard)

set(CMAKE_C_COMPILER   avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)

set(SOURCE_FILES
    "clion source.ino"
    display.cpp
    display.h
    ds3231.cpp
    ds3231.h
    mytime.cpp
    mytime.h ButtonManager.cpp ButtonManager.h)

add_executable(clion_source ${SOURCE_FILES})