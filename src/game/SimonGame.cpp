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

void SimonGame::nextLevel() {
    ++level;

    state = GameState::GENERATE_SEQUENCE;
}

void SimonGame::startGameOver() {
    gameOverBlink = 0;
    gameOverLedOn = true;
    gameOverStarted = true;

    for (int i = 0; i < PINS_COUNT; ++i) 
        leds.turnOn(i);

    gameOverMillis = millis();
}

bool SimonGame::updateGameOver() {
    unsigned long now = millis();

    if (now - gameOverMillis < GAME_OVER_BLINK_DURATION) return false; 

    gameOverMillis = now;
    
    if (gameOverLedOn) {
            leds.turnOffAll();
            gameOverLedOn = false;
            return false;
    }
    
    ++gameOverBlink;

    if (gameOverBlink >= GAME_OVER_BLINK_COUNT) {
        display.showGameOver(level - 1);
        return true;
    }

    for (int i = 0; i < PINS_COUNT; ++i) leds.turnOn(i);

    gameOverLedOn = true;

    return false;
}

void SimonGame::update() {
    switch (state)
    {
        case GameState::START:
            level = 1;

            state = GameState::GENERATE_SEQUENCE;
            break;

        case GameState::GENERATE_SEQUENCE:
            if (level > MAX_LEVEL) {
                state = GameState::GAME_OVER;
                break;
            }

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
                state = GameState::GAME_OVER;
                break;
            }

            if (result == InputResult::COMPLETE) {
                state = GameState::LEVEL_COMPLETE;
                break;
            }

            break;
        }
        
        case GameState::LEVEL_COMPLETE:
            nextLevel();
            break;
        
        case GameState::GAME_OVER:
            if (!gameOverStarted) startGameOver();

            if (updateGameOver()) {
                gameOverStarted = false;
                state = GameState::WAITING_RESTART;
            }
            break;

        case GameState::WAITING_RESTART:
            break;
    }
}