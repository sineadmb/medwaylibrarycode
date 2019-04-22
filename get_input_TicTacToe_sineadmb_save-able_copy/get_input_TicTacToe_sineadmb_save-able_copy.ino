#include "button_input.h"

int ButtonPress = 0;

void setup() {
  startButtons();
   Serial.begin(9600);
}

void loop() {
  ButtonPress = 0;
  getInput();
  Serial.println(getInput());
  printBoard();
  CheckWinner();
  getInput();
}


