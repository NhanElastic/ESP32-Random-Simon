#include "PlayerInput.h"

#include <Arduino.h>

PlayerInput::PlayerInput(ButtonManager& buttons, LedManager& leds) : buttons(buttons), leds(leds) {}

void PlayerInput::begin(
    const int* sequence,
    int length
) {
    this->sequence = sequence;
    this->length = length;

    index = 0;
    currentButton = -1;
    state = PlayerInputState::WAITING_BUTTONS;
};

InputResult PlayerInput::update() {
    unsigned long now = millis();

    switch(state) {
        case PlayerInputState::WAITING_BUTTONS: {
            int button = buttons.getButtonPressed();

            if (button == -1) 
                return InputResult::NONE;

            currentButton = button;
            leds.turnOn(currentButton);

            lastTime = now;
            state = PlayerInputState::FEEDBACK;

            return InputResult::NONE;
        }

        case PlayerInputState::FEEDBACK: {
            if (now - lastTime < FEEDBACK_TIME) 
                return InputResult::NONE;
            
            leds.turnOff(currentButton);

            state = PlayerInputState::WAITING_BUTTONS;

            if (currentButton != sequence[index])
                return InputResult::WRONG;

            ++index;

            if (index == length) 
                return InputResult::COMPLETE;

            return InputResult::CORRECT;
        }
    }
    return InputResult::NONE;
}

