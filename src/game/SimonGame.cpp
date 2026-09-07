#include "SimonGame.h"

#include <Arduino.h>

SimonGame::SimonGame() : playerInput(buttons, leds), sequencePresenter(leds, display) {}

void SimonGame::begin() {
    buttons.begin();
    leds.begin();
    display.begin();

    display.showWelcome();
}

void SimonGame::generateSequence() {
    generator.generate(sequences, level, PINS_COUNT);
}

void SimonGame::startGame() {
    level = 1;
    gameResult = GameResult::NONE;

    endGameMillis = 0;
    endGameBlink = 0;
    endGameLedOn = false;
    endGameStarted = false;

    leds.turnOffAll();
    state = GameState::GENERATE_SEQUENCE;
}

void SimonGame::nextLevel() {
    if (level >= MAX_LEVEL) {
        gameResult = GameResult::WIN;
        state = GameState::END_GAME;
        return;
    }

    ++level;

    state = GameState::GENERATE_SEQUENCE;
}

void SimonGame::startEndGame() {
    endGameBlink = 0;
    endGameLedOn = true;
    endGameStarted = true;

    for (int i = 0; i < PINS_COUNT; ++i) 
        leds.turnOn(i);

    endGameMillis = millis();
}

bool SimonGame::updateEndGame() {
    unsigned long now = millis();

    if (now - endGameMillis < END_GAME_BLINK_DURATION) return false; 

    endGameMillis = now;
    
    if (endGameLedOn) {
        leds.turnOffAll();
        endGameLedOn = false;
        return false;
    }
    
    ++endGameBlink;

    if (endGameBlink >= END_GAME_BLINK_COUNT) {
        showResult();
        return true;
    }

    for (int i = 0; i < PINS_COUNT; ++i) 
        leds.turnOn(i);

    endGameLedOn = true;

    return false;
}

void SimonGame::showResult() {
    if (gameResult == GameResult::WIN) {
        display.showWin();
        return;
    }

    display.showGameOver(level - 1);
}

void SimonGame::update() {
    switch (state) {
        case GameState::START:
            if (buttons.getButtonPressed() != -1)
                startGame();
            break;

        case GameState::GENERATE_SEQUENCE:
            generateSequence();

            sequencePresenter.begin(sequences, level);

            state = GameState::SHOW_SEQUENCE;
            break;

        case GameState::SHOW_SEQUENCE:
            if (sequencePresenter.update()) {
                display.showYourTurn();

                playerInput.begin(sequences, level);

                state = GameState::WAITING_INPUT;
            }

            break;

        case GameState::WAITING_INPUT: {
            InputResult result = playerInput.update();

            if (result == InputResult::WRONG) {
                gameResult = GameResult::LOSE;
                state = GameState::END_GAME;
            } else if (result == InputResult::COMPLETE) 
                state = GameState::LEVEL_COMPLETE;

            break;
        }
        
        case GameState::LEVEL_COMPLETE:
            nextLevel();
            break;
        
        case GameState::END_GAME:
            if (!endGameStarted) startEndGame();

            if (updateEndGame()) {
                endGameStarted = false;
                state = GameState::WAITING_RESTART;
            }
            break;

        case GameState::WAITING_RESTART:
            if (buttons.getButtonPressed() != -1)
                startGame();
            break;
    }
}