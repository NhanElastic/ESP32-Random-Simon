#pragma once

#include "GameState.h"
#include "../hardware/Buttons/ButtonManager.h"
#include "../hardware/LED/LedManager.h"
#include "../utils/SequenceGenerator.h"

class SimonGame {
    private:
        static constexpr int MAX_LEVEL = 100;

        int sequences[MAX_LEVEL];

        GameState state = GameState::START;
        ButtonManager buttons;
        LedManager leds;
        SequenceGenerator generator;

        void generateSequence();
        void handlePlayerInput();
        void showSequence();
        
        void nextLevel();
        void gameOver();

        int level = 1;
        int inputIndex = 0;

    public:
        void start();
        void update();
};