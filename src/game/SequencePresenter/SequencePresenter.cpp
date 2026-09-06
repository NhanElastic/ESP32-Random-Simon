#include "SequencePresenter.h"

#include <Arduino.h>

SequencePresenter::SequencePresenter(
    LedManager& leds,
    DisplayManager& display
) : leds(leds), display(display) {}

void SequencePresenter::begin(const int* sequence, int level) {
    this->sequence = sequence;
    this->length = level;

    index = 0;

    display.showLevel(level);

    previousMillis = millis();
    state = State::SHOW_LEVEL;
}

bool SequencePresenter::update() {
    unsigned long now = millis();

    switch (state) {
        case State::SHOW_LEVEL:
            if (now - previousMillis < LEVEL_DURATION) {
                return false;
            }

            display.showWatch();

            previousMillis = now;
            state = State::SHOW_WATCH;
            return false;

        case State::SHOW_WATCH:
            if (now - previousMillis < WATCH_DURATION) {
                return false;
            }

            leds.turnOn(sequence[index]);

            previousMillis = now;
            state = State::LED_ON;
            return false;

        case State::LED_ON:
            if (now - previousMillis < LED_ON_DURATION) {
                return false;
            }

            leds.turnOff(sequence[index]);

            previousMillis = now;
            state = State::LED_OFF;
            return false;

        case State::LED_OFF:
            if (now - previousMillis < LED_OFF_DURATION) {
                return false;
            }

            ++index;

            if (index >= length) {
                state = State::IDLE;
                return true;
            }

            leds.turnOn(sequence[index]);

            previousMillis = now;
            state = State::LED_ON;
            return false;

        case State::IDLE:
            return false;
    }

    return false;
}