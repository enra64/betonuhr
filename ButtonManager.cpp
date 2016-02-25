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
    if(mLastToggleState) return; //button not pressed
    _delay_ms(140);
    if(getButtonState() == mLastToggleState){
        delay(350);
        mDisplay->onLongButtonPress();
        digitalWrite(LED, 1);
        delay(50);
        digitalWrite(LED, 0);
    }
    else{
        mDisplay->onShortButtonPress();
        digitalWrite(LED, 1);
        delay(50);
        digitalWrite(LED, 0);
        delay(200);
        digitalWrite(LED, 1);
        delay(50);
        digitalWrite(LED, 0);
    }
}

bool ButtonManager::getButtonState() {
    return (bool) (PINC & (1 << PC3));
}
