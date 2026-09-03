#pragma once

#include "../../configs/Pins.h"

class ButtonManager {
    private:
        static constexpr unsigned long DEBOUNCE_TIME = 30;

        bool lastReading[PINS_COUNT] {};
        bool stableState[PINS_COUNT] {};
        unsigned long long lastChangeTime[PINS_COUNT] {};

        bool detectPress(int index);

    public: 
        void begin();

        int getButtonPressed();
};