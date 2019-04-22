#include<Servo.h>
Servo LCstick;
Servo RCstick;

int valy;
int valx;

void setup() {
   myservo1.attach(9);
   myservo2.attach(7);
 
}

void loop() {
 valy=analogRead(0);
 valx=analogRead(1);
 valy=map(valy,0,1023,0,180);
 valx=map(valx,0,1023,0,180);
 myservo1.write(valy);
 delay(50);
 myservo2.write(valx);
 delay(50);
}
