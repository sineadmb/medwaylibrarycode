/*
Brim

45/2/18 by Gaston Marzoratti

The following code supports
-Bluetooth Control
-Two Motors
*/


# define debug false

#include <SoftwareSerial.h> //Creates serial ports for Digital IO
SoftwareSerial BT(10, 11);  //Create Serial Port 10-TX, 11-RX
                            //for Bluetooth Module


#define  NumberOfModes 2
#define RightDriveMotor 4
#define LeftDriveMotor 3
#define ServoClaw 5

#define ServoUp 6

#include <Servo.h>
#include <Wire.h>  //arduino to motorshield
#include<Adafruit_MotorShield.h>
#include"utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();  // Create Motorshield

Adafruit_DCMotor *LeftMotor = AFMS.getMotor(3);      // Create Motors
Adafruit_DCMotor *RightMotor = AFMS.getMotor(4);

//Joystick Values
int rx;    // variable to read the value from the analog pin
int ry;    // variable to read the value from the analog pin
int lx;    // variable to read the value from the analog pin
int ly;    // variable to read the value from the analog pin
int motorSpeed;

//Button States
int jrb;
int jlb;
int tb;
int lb;
int rb;
int bb;

void setup() 
{

   Serial.begin(9600); // Begin Serial for debug
   BT.begin(9600);      // Begin Serial for Bluetooth module

   AFMS.begin();         // Connect to the motor
   RightMotor->setSpeed(100);  // 10 rpm
   LeftMotor->setSpeed(100);  // 10 rpm


   RightMotor->setSpeed(50);         // Set start motor speed
   LeftMotor->setSpeed(50);          // from 0 (off) to 255 (max speed)

   RightMotor->run(FORWARD);         // turn on motor
   RightMotor->run(RELEASE);
   LeftMotor->run(FORWARD);          // turn on motor
   LeftMotor->run(RELEASE);


 
 
}

void loop() 
{
  if (BT.available())  //Do this if BT Command found
  {
    if(debug){Serial.println("looking");}

    if ('s' == BT.read())
    { //Read data
      getData();

      if(debug){
      Serial.print("Start--");
      Serial.print("s");
      Serial.print("--");
      Serial.print(rx);
      Serial.print("--");
      Serial.print(ry);
      Serial.print("--");
      Serial.print(lx);
      Serial.print("--");
      Serial.print(ly);
      Serial.print("--");
      Serial.print(jlb);
      Serial.print("--");
      Serial.print(jrb);
      Serial.print("--");
      Serial.print(tb);
      Serial.print("--");
      Serial.print(lb);
      Serial.print("--");
      Serial.print(rb);
      Serial.print("--");
      Serial.print(bb);
      Serial.println("--Done");
    }
    
    }
  } 
  //End of Getting Data


  //Set Right Motor speed
  if (ry < 412)
  {
    RightMotor->run(BACKWARD);
    motorSpeed = map(ry, 500, 0, 0, 255);  //scale to 0 and 255
    RightMotor->setSpeed(motorSpeed);
   // Serial.print("back");
   // Serial.print(motorSpeed);
  }
  else if (ry > 612)  //go forward
  {
    RightMotor->run(FORWARD);
    motorSpeed = map(ry, 523, 1023, 0, 255);  //scale to 0 and 255
    RightMotor->setSpeed(motorSpeed);
    //Serial.print("Forward");
    //Serial.print(motorSpeed);
  }
  else
  {
    motorSpeed = 0;
    RightMotor->run(RELEASE);
    motorSpeed = 0;
  }

  //Set Left Motor speed
  if (ly < 412)
  {
    LeftMotor->run(BACKWARD);
    motorSpeed = map(ry, 500, 0, 0, 255);  //scale to 0 and 255
    LeftMotor->setSpeed(motorSpeed);
   // Serial.print("back");
    //Serial.print(motorSpeed);
  }
  else if (ly > 612)  //go forward
  {
    LeftMotor->run(FORWARD);
    motorSpeed = map(ry, 523, 1023, 0, 255);  //scale to 0 and 255
    LeftMotor->setSpeed(motorSpeed);
  //  Serial.print("Forward");
  //  Serial.print(motorSpeed);
  }
  else
  {
    motorSpeed = 0;
    LeftMotor->run(RELEASE);
    motorSpeed = 0;
  }


}  //end of main loop


void getData()
{
      //Read data
    rx = BT.parseInt();
    ry = BT.parseInt();
    lx = BT.parseInt();
    ly = BT.parseInt();
    jlb = BT.parseInt();
    jrb = BT.parseInt();
    tb = BT.parseInt();
    lb = BT.parseInt();    
    rb = BT.parseInt();
    bb = BT.parseInt();
}


