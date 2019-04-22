#include "button_input.h"

int ButtonPress = 0;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(8, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {
  ButtonPress = 0;
  getInput();
  Serial.println(getInput());
}


