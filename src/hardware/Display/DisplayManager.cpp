#include "DisplayManager.h"
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

DisplayManager::DisplayManager()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

void DisplayManager::begin() {
    Wire.begin(21, 22);

    display.begin(
        SSD1306_SWITCHCAPVCC,
        SCREEN_ADDRESS
    );

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
}

void DisplayManager::showWelcome() {
    display.clearDisplay();

    display.setTextSize(2);
    display.setCursor(10, 15);
    display.println("SIMON");

    display.setTextSize(1);
    display.setCursor(20, 45);
    display.println("Press button");

    display.display();
}

void DisplayManager::showLevel(int level) {
    display.clearDisplay();

    display.setTextSize(2);
    display.setCursor(20, 10);
    display.println("LEVEL");

    display.setTextSize(3);
    display.setCursor(55, 35);
    display.println(level);

    display.display();
}

void DisplayManager::showYourTurn() {
    display.clearDisplay();

    display.setTextSize(2);
    display.setCursor(5, 25);
    display.println("YOUR TURN");

    display.display();
}

void DisplayManager::showGameOver(int score) {
    display.clearDisplay();

    display.setTextSize(2);
    display.setCursor(10, 10);
    display.println("GAME OVER");

    display.setTextSize(1);
    display.setCursor(30, 45);
    display.print("Score: ");
    display.println(score);

    display.display();
}

void DisplayManager::showWatch() {
    display.clearDisplay();

    display.setTextSize(2);
    display.setCursor(25, 25);
    display.println("WATCH!");

    display.display();
}