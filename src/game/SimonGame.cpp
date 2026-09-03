#include "SimonGame.h"

#include <Arduino.h>

void SimonGame::start() {
    buttons.begin();
    leds.begin();
}

void SimonGame::generateSequence() {
    return generator.generate(sequences, level, PINS_COUNT);
}

void SimonGame::showSequence() {
    for (int i = 0; i < level; ++i) {
        int ledIndex = sequences[i];

        leds.turnOn(ledIndex);
        delay(500);

        leds.turnOff(ledIndex);
        delay(200);
    }
}

void SimonGame::nextLevel() {
    ++level;
    inputIndex = 0;

    state = GameState::GENERATE_SEQUENCE;
}

void SimonGame::gameOver() {
    if (state == GameState::GAME_OVER)
        return;

    for (int blink = 0; blink < 5; ++blink) {
        for (int i = 0; i < PINS_COUNT; ++i) {
            leds.turnOn(i);
        }

        delay(200);
        leds.turnOffAll();
        delay(200);
    }

    state = GameState::GAME_OVER;
}

void SimonGame::handlePlayerInput() {
    int button = buttons.getButtonPressed();

    if (button == -1)
        return;

    if (button != sequences[inputIndex]) {
        gameOver();
        return;
    }

    ++inputIndex;

    if (inputIndex == level) 
        state = GameState::LEVEL_COMPLETE;
}

void SimonGame::update() {
    switch (state)
    {
        case GameState::START:
            level = 1;
            inputIndex = 0;
            state = GameState::GENERATE_SEQUENCE;
            break;

        case GameState::GENERATE_SEQUENCE:
            if (level > 100) {
                state = GameState::GAME_OVER;
                break;
            }

            generateSequence();

            state = GameState::SHOW_SEQUENCE;
            break;

        case GameState::SHOW_SEQUENCE:
            showSequence();
            
            inputIndex = 0;
            state = GameState::WAITING_INPUT;
            break;

        case GameState::WAITING_INPUT:
            handlePlayerInput();
            break;

        case GameState::LEVEL_COMPLETE:
            nextLevel();
            break;
        
        case GameState::GAME_OVER:
            gameOver();
            break;
    default:
        break;
    }
};