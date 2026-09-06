#pragma once

#include "../../hardware/Display/DisplayManager.h"
#include "../../hardware/LED/LedManager.h"

class SequencePresenter {
    private:
        enum class State {
            IDLE,
            SHOW_LEVEL,
            SHOW_WATCH,
            LED_ON,
            LED_OFF
        };

        static constexpr unsigned long LEVEL_DURATION = 700;
        static constexpr unsigned long WATCH_DURATION = 500;
        static constexpr unsigned long LED_ON_DURATION = 500;
        static constexpr unsigned long LED_OFF_DURATION = 200;

        LedManager& leds;
        DisplayManager& display;

            const int* sequence = nullptr;

        int length = 0;
        int index = 0;

        unsigned long previousMillis = 0;

        State state = State::IDLE;

    public:
        SequencePresenter(LedManager& leds, DisplayManager& display);

        void begin(const int* sequence, int length, int level);
        bool update();
};