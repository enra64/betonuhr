//
// Created by arne on 24.02.16.
//

#ifndef CLION_SOURCE_BUTTONMANAGER_H
#define CLION_SOURCE_BUTTONMANAGER_H

#define BUTTON_INPUT PCINT11
#define __AVR_ATmega328P__
#include <avr/io.h>
#include "display.h"


class ButtonManager {
public:
    void toggled();
    void checkPressType();
    ButtonManager();
private:
    bool mLastToggleState = false;
    unsigned long mLastToggleTime;
    bool getButtonState();
    Display *mDisplay;
};


#endif //CLION_SOURCE_BUTTONMANAGER_H
