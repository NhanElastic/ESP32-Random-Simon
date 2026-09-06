#pragma once 

#include "../../hardware/Buttons/ButtonManager.h"
#include "../../hardware/LED/LedManager.h"

enum class InputResult {
    CORRECT,
    WRONG,
    NONE,
    COMPLETE
};

class PlayerInput {
    private:
        enum class PlayerInputState {
            WAITING_BUTTONS,
            FEEDBACK
        };

        static constexpr long FEEDBACK_TIME = 200;

        PlayerInputState state = PlayerInputState::WAITING_BUTTONS;
        ButtonManager& buttons;
        LedManager& leds;

        const int* sequence = nullptr;

        int length;
        int index;

        int currentButton = -1;

        bool waitingFeedback = false;
        unsigned long lastTime = 0;

    public:
        PlayerInput(
            ButtonManager& buttons,
            LedManager& leds
        );

        void begin(const int* sequence, int length);

        InputResult update();
};