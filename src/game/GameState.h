#pragma once

enum class GameState {
    START,
    GENERATE_SEQUENCE,
    SHOW_SEQUENCE,
    WAITING_INPUT,
    LEVEL_COMPLETE,
    GAME_OVER
};