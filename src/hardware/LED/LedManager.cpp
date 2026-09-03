#include "LedManager.h"
#include "../../configs/Pins.h"

#include <Arduino.h>

void LedManager::begin() {
    for (int i = 0; i < PINS_COUNT; ++i) {
        pinMode(LED_PINS[i], OUTPUT);
    }
}

void LedManager::turnOn(int index) {
    digitalWrite(LED_PINS[index], HIGH);
}

void LedManager::turnOff(int index) {
    digitalWrite(LED_PINS[index], LOW);
}

void LedManager::turnOffAll() {
    for (int i = 0; i < PINS_COUNT; ++i) {
        digitalWrite(LED_PINS[i], LOW);
    }
}