//
// Created by arne on 24.02.16.
//

#include "ButtonManager.h"

ButtonManager::ButtonManager() {
    //PCICR |= (1 << PCIE1);
    //PCMSK1 |= (1 << PCINT11);
    //input pullup for button
    DDRC &= ~(1 << PC3);
    PORTC |= (1 << PC3);
}

void ButtonManager::checkPressType() {
    if(mButtonIsHeldDown && !getButtonState())
        mButtonIsHeldDown = false;
    if(getButtonState() && ! mButtonIsHeldDown){
        delay(200);
        if(getButtonState())
            mDisplay->onLongButtonPress();
        else
            mDisplay->onShortButtonPress();
        mButtonIsHeldDown = true;
    }
}

bool ButtonManager::getButtonState() {
    return (bool) !(PINC & (1 << PC3));
}
