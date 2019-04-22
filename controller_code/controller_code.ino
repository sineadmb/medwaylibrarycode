#include <SoftwareSerial.h>;
SoftwareSerial BT(10, 11);

int knobX = 0;
int knobY = 1;
int valy;
int valx;

void setup() {
//  Serial.begin(9600);
  BT.begin(9600);

}

void loop() {
  
  valx = analogRead(knobX);
  BT.print("x");
//  Serial.print("Here");
  BT.print(valx);
  delay(100);

  valy = analogRead(knobY);
  BT.print("y");
  BT.print(valy);
  delay(100);

}
