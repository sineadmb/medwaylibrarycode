#include <SoftwareSerial.h>;
SoftwareSerial BT (10,11);

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#include <Servo.h>

Servo servoC;
Servo servoU;

#define version 5.0

#define RightMotorDrive 3
#define LeftMotorDrive 4
#define ServoClaw 9
#define ServoUp 10
#define NumofModes 2

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *LeftMotor = AFMS.getMotor(3);
Adafruit_DCMotor *RightMotor = AFMS.getMotor(4);

char state; 

int val; 
int s = 512; 
int d = 512;
int c = 512;
int u = 512;
int Mode = 0;
 

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

  servoC.attach(ServoClaw); 
  servoU.attach(ServoUp);
}

void loop() {
  if (BT.available())
  {
    state = BT.read();
//    Serial.print("state");
    
    //Serial.println(state);
      if (state == 's')
      {
      Serial.println("Got a s");
      val = BT.parseInt();
      s = val;
      } //end of "speed" loop
    
      else if (state == 'd')
      {
      Serial.println("Got a d");
      val = BT.parseInt();
      d = val;
      } //end of "direction" loop
      
      else if (state == 'c')
      {
      Serial.println("Got a c");
      val = BT.parseInt();
      c = val;  
      } //end of "claw" loop
      
      else if (state == 'u')
      {
      Serial.println("Got an u");
      val = BT.parseInt();
      u = val;
      } //end of "up" loop

      if (state == 'm')
      {
      Mode = Mode + 1;
      }
      if (Mode = NumofModes)
      {
      Mode = 0;
      }
      if (Mode = 0)
      {
      
      }
      if (Mode = 1)
      {
           if (state == 's')
      {
      Serial.println("Got a s");
      val = BT.parseInt();
      s = val;
      } //end of "speed" loop
    
      else if (state == 'd')
      {
      Serial.println("Got a d");
      val = BT.parseInt();
      d = val;
      } //end of "direction" loop
      
      else if (state == 'c')
      {
      Serial.println("Got a c");
      val = BT.parseInt();
      c = val;  
      } //end of "claw" loop
      
      else if (state == 'u')
      {
      Serial.println("Got an u");
      val = BT.parseInt();
      u = val;
      } //end of "up" loop
      }
//  Serial.println(s);
 setMotor(s,d);
 setServos(c,u);
}
}//end of main loop

void setMotor(int sp, int dr)//motors
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


void setServos(int cl, int up) //servos
{
  int claw;
  int lift;

  claw = map(claw, 0, 1023, 0, 180);
  lift = map(lift, 0, 1023, 0,180);
  servoC.write(claw);
  delay(3);
  servoU.write(lift);
  delay(4);
}

