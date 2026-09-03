#include <Arduino.h>

#define BUTTION 4
#define LED 5

bool buttonState;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BUTTION, INPUT);

  digitalWrite(LED, LOW);


}

void loop() {
  buttonState = digitalRead(BUTTION);

  if(buttonState == HIGH) {
    Serial.println("LED ON");
    digitalWrite(LED, HIGH);
  } else {
    Serial.println("LED OFF");
    digitalWrite(LED, LOW);
  }
}