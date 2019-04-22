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
    if (state == 'x')
    {
      
      val = BT.parseInt();
      if (val < 500)
      {
        RightMotor->run(BACKWARD);
        val = map(val,500,0,0,255);
        RightMotor->setSpeed(val);
        Serial.println(val);
      }
      else if (val >523)
      {
        RightMotor->run(FORWARD);
        val = map(val,523,1023,0,255);
        RightMotor->setSpeed(val);
      }
      else
      {
        RightMotor->run(RELEASE);
      }
    }
       else if (state == 'y')
    {
      val = BT.parseInt();
      if (val < 500)
      {
        LeftMotor->run(BACKWARD);
        val = map(val,500,0,0,255);
        LeftMotor->setSpeed(val);
      }
      else if (val >523)
      {
        LeftMotor->run(FORWARD);
        val = map(val,523,1023,0,255);
        LeftMotor->setSpeed(val);
      }
      else
      {
        LeftMotor->run(RELEASE);
      }
    }
  }
}
