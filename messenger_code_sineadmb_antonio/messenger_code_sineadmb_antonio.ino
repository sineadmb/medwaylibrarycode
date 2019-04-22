#include <SoftwareSerial.h>;
SoftwareSerial BT(10, 11);

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
}

void loop()
{
  if ( Serial.available()){
    while(Serial.available())
    {
    BT.write(Serial.read());
  }
  BT.println();
  }
  
   if (BT.available())
   {
    while (BT.available())
    {
    Serial.write(BT.read());
  }
  Serial.println();
}
delay(50);
}
