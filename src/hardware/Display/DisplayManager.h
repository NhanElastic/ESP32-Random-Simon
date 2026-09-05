#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class DisplayManager {
    private:
        Adafruit_SSD1306 display;

    public:
        DisplayManager();

        void begin();

        void showWelcome();
        void showLevel(int level);
        void showWatch();
        void showYourTurn();
        void showGameOver(int score);
};