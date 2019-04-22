#include <SoftwareSerial.h>;
SoftwareSerial BT (10,11);

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *LeftMotor = AFMS.getMotor(3);
Adafruit_DCMotor *RightMotor = AFMS.getMotor(4);

char state; 
int val;
int val1;
int val2;
 


void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  AFMS.begin();
  RightMotor->setSpeed(50);
  LeftMotor->setSpeed(50);

  RightMotor->run(FORWARD);
  RightMotor->run(RELEASE);
  LeftMotor->run(FORWARD);
  LeftMotor->run(RELEASE);
  
}

void loop() {
  if (BT.available())
  {
    state = BT.read();
   Serial.println(state);
    if (state == 's')
    {
      
      val = BT.parseInt();
      if (val < 500)
      {
        RightMotor->run(FORWARD);
        LeftMotor->run(FORWARD);
        val2 = map(val,500,0,0,255);
        val1 = map(val,500,0,0,200);
        RightMotor->setSpeed(val1);
        LeftMotor->setSpeed(val2);
        
        Serial.println(val);
      }
      
      else if (val >523)
      {
        RightMotor->run(BACKWARD);
        LeftMotor->run(BACKWARD);
        val1 = map(val,523,1023,0,255);
        RightMotor->setSpeed(val);
        LeftMotor->setSpeed(val);
      }
      else
      {
        RightMotor->run(RELEASE);
        LeftMotor->run(RELEASE);
      }
        
      }
    }
  }

