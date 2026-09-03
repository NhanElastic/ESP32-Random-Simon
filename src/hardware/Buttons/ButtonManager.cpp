#include "ButtonManager.h"
#include "../../configs/Pins.h"

#include <Arduino.h>

void ButtonManager::begin() {
    for (int i = 0; i < PINS_COUNT; ++i) {
        pinMode(BUTTON_PINS[i], INPUT);
    }
}

int ButtonManager::getButtonPressed() {
    for (int i = 0; i < PINS_COUNT; ++i) {
        if(detectPress(i)) return i;
    }
    return -1;
}

bool ButtonManager::detectPress(int index) {
    bool reading = digitalRead(BUTTON_PINS[index]);
    unsigned long now = millis();

    if (reading != lastReading[index]) {
        lastReading[index] = reading;
        lastChangeTime[index] = now;
    }

    if (now - lastChangeTime[index] < DEBOUNCE_TIME)
        return false;

    if (reading == stableState[index])
        return false;

    stableState[index] = reading;

    return reading == HIGH;
}