//
// Created by arne on 24.02.16.
//

#include "ButtonManager.h"

ButtonManager::ButtonManager() {
    PCICR |= (1 << PCIE1);
    PCMSK1 |= (1 << PCINT11);
    //input pullup for button
    DDRC &= ~(1 << PC3);
    PORTC |= (1 << PC3);
}

void ButtonManager::toggled() {
    mLastToggleState = getButtonState();
    mLastToggleTime = millis();
}

void ButtonManager::checkPressType() {
    if(millis() - mLastToggleTime < 10) return; //wait
    if(getButtonState() != mLastToggleState) return; //button bounced
    _delay_ms(90);
    if(getButtonState() == mLastToggleState){
        delay(400);
        mDisplay->onLongButtonPress();
    }
    else{
        mDisplay->onShortButtonPress();
    }
}

bool ButtonManager::getButtonState() {
    return (bool) (PINC & (1 << PC3));
}
