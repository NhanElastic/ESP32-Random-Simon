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
        unsigned long endGameMillis = 0;
        int endGameBlink = 0;
        bool endGameLedOn = false;
        bool endGameStarted = false;

        static constexpr unsigned long END_GAME_BLINK_DURATION = 200;
        static constexpr int END_GAME_BLINK_COUNT = 5;

        void startEndGame();
        bool updateEndGame();

        static constexpr int MAX_LEVEL = 100;

        int sequences[MAX_LEVEL];
        int level = 1;

        GameState state = GameState::START;
        GameResult gameResult = GameResult::NONE;

        ButtonManager buttons;
        LedManager leds;
        DisplayManager display;
        SequenceGenerator generator;
        PlayerInput playerInput;
        SequencePresenter sequencePresenter;

        void generateSequence();
        void startGame();

        void nextLevel();

        void showResult();

    public:
        SimonGame();
        void begin();
        void update();
};