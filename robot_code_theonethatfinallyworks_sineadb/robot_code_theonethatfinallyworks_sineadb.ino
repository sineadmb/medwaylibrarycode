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
int s = 512; 
int d = 512;

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
    if (state == 's')
    {
       Serial.print("Got an s");
      val = BT.parseInt();
      s = val;
    } //end of "speed" loop
    
       else if (state == 'd')
    {
      val = BT.parseInt();
      d = val;
    } //end of direction loop
  } //end of bluetooth loop
  Serial.println(s);
 setMotor(s,d);
}//end of main loop

void setMotor(int sp, int dr)
{

  int motorSpeed;
  int steering;
//get motor speed and direction
  if (sp < 500) //go backward
  {
    RightMotor->run(BACKWARD);
    LeftMotor->run(BACKWARD);
    motorSpeed = map(sp, 500, 0, 0, 255); //scale to 0 to 255
  }
  else if (sp > 523) //go forward
  {
    RightMotor->run(FORWARD);
    LeftMotor->run(FORWARD);
    motorSpeed = map(sp, 523, 1023, 0, 255); //scale to 0 to 255
  }
  else
  {
    RightMotor->run(RELEASE);
    LeftMotor->run(RELEASE);
    motorSpeed = 0;
  }
  if (dr < 490) //turn left
  {
    steering = map(dr, 490, 0, 255, 100); //scale to 0 to 255
    RightMotor->setSpeed(motorSpeed);
    LeftMotor->setSpeed(motorSpeed * steering / 255);
  }
  else if (dr > 530) //turn right
  {
    steering = map(dr, 530, 1023, 255, 100); //scale to 0 to 255
    RightMotor->setSpeed(motorSpeed * steering / 255);
    LeftMotor->setSpeed(motorSpeed);
  }
  else //go straight
  {
    RightMotor->setSpeed(motorSpeed);
    LeftMotor->setSpeed(motorSpeed);
  }
}

