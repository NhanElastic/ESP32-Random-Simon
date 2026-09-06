#pragma once

#include "GameState.h"
#include "../hardware/Buttons/ButtonManager.h"
#include "../hardware/LED/LedManager.h"
#include "../hardware/Display/DisplayManager.h"
#include "../utils/SequenceGenerator.h"
#include "PlayerInput/PlayerInput.h"
#include "SequencePresenter/SequencePresenter.h"

class SimonGame {
    private:
        unsigned long gameOverMillis = 0;
        int gameOverBlink = 0;
        bool gameOverLedOn = false;
        bool gameOverStarted = false;

        static constexpr unsigned long GAME_OVER_BLINK_DURATION = 200;
        static constexpr int GAME_OVER_BLINK_COUNT = 5;

        void startGameOver();
        bool updateGameOver();

        static constexpr int MAX_LEVEL = 100;

        int sequences[MAX_LEVEL];
        int level = 1;

        GameState state = GameState::START;

        ButtonManager buttons;
        LedManager leds;
        DisplayManager display;
        SequenceGenerator generator;
        PlayerInput playerInput;
        SequencePresenter sequencePresenter;

        void generateSequence();

        void nextLevel();
    public:
        SimonGame();
        void begin();
        void update();
};