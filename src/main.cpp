#include <Arduino.h>
#include "game/SimonGame.h"

SimonGame game;

void setup() {
  Serial.begin(9600);
  game.begin();
}

void loop() {
  game.update();
}