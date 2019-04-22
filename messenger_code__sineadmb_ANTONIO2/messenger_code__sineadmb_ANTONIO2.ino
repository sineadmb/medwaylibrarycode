#include <SoftwareSerial.h>;
SoftwareSerial BT(10, 11);

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
}

void loop() 
{ 
                //Give time to execute
  BT.print(Serial.read());
  Serial.print(BT.read());
}


