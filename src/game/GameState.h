#pragma once

enum class GameState {
    START,
    GENERATE_SEQUENCE,
    SHOW_SEQUENCE,
    WAITING_INPUT,
    LEVEL_COMPLETE,
    END_GAME,
    WAITING_RESTART
};

enum class GameResult {
    NONE,
    WIN,
    LOSE
};