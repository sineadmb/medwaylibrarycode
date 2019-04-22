//Today

#include <Servo.h>

# define debug false

#include <SoftwareSerial.h> //Creates serial ports for Digital IO
SoftwareSerial BT(10, 11);  //Create Serial Port 10-TX, 11-RX
                            //for Bluetooth Module
Servo awesomeservo;

#define  NumberOfModes 2
#define RightDriveMotor 4
#define LeftDriveMotor 3
#define ServoClaw 5
#define ServoUp 6 

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

//Button States
int jrb;
int jlb;
int CarModeButton;
int lb;
int TankModeButton;
int bb;

int motorSpeed;

int servo;

void setup() 
{

   Serial.begin(9600); // Begin Serial for debug
   BT.begin(9600);      // Begin Serial for Bluetooth module

   AFMS.begin();         // Connect to the motor
   RightMotor->setSpeed(100);  // 10 rpm
   LeftMotor->setSpeed(100);  // 10 rpm

   awesomeservo.attach(9);
 
   RightMotor->setSpeed(50);         // Set start motor speed
   LeftMotor->setSpeed(50);          // from 0 (off) to 255 (max speed)

   RightMotor->run(FORWARD);         // turn on motor
   RightMotor->run(RELEASE);
   LeftMotor->run(FORWARD);          // turn on motor
   LeftMotor->run(RELEASE);
}

void loop()
{
  
  getCommand();
  if (TankModeButton) {
    moveTank;
  }
  else if (CarModeButton){
    moveCar(rx, ry);
  }
  servo=map(lx,0,1023,0,180);
  awesomeservo.write(servo);
  delay (50);
  
  if (debug) {
    SendDebugData();
  }
}  //end of void loop



void getData()
{
      //Read data
    rx = BT.parseInt();
    ry = BT.parseInt();
    lx = BT.parseInt();
    ly = BT.parseInt();
    jlb = BT.parseInt();
    jrb = BT.parseInt();
    CarModeButton = BT.parseInt();
    lb = BT.parseInt();    
    TankModeButton = BT.parseInt();
    bb = BT.parseInt();
}

void SendDebugData()
{ 
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
    Serial.print(CarModeButton);
    Serial.print("--");
    Serial.print(lb);
    Serial.print("--");
    Serial.print(TankModeButton);
    Serial.print("--");
    Serial.print(bb);
    Serial.println("--Done");
}

void moveTank()
{
  //Set Right Motor speed
  if (ry < 412)
  {
    RightMotor->run(BACKWARD);
    motorSpeed = map(ry, 500, 0, 0, 255);  //scale to 0 and 255
    RightMotor->setSpeed(motorSpeed);
    Serial.print("back");
    Serial.print(motorSpeed);
  }
  else if (ry > 612)  //go forward
  {
    RightMotor->run(FORWARD);
    motorSpeed = map(ry, 523, 1023, 0, 255);  //scale to 0 and 255
    RightMotor->setSpeed(motorSpeed);
    Serial.print("Forward");
    Serial.print(motorSpeed);
  }
  else
  {
    motorSpeed = 0;
    RightMotor->run(RELEASE);
  }

  //Set Left Motor speed
  if (ly < 412)
  {
    LeftMotor->run(BACKWARD);
    motorSpeed = map(ly, 500, 0, 0, 255);  //scale to 0 and 255
    LeftMotor->setSpeed(motorSpeed);
    Serial.print("back");
    Serial.print(motorSpeed);
  }
  else if (ly > 612)  //go forward
  {
    LeftMotor->run(FORWARD);
    motorSpeed = map(ly, 523, 1023, 0, 255);  //scale to 0 and 255
    LeftMotor->setSpeed(motorSpeed);
    Serial.print("Forward");
    Serial.print(motorSpeed);
  }
  else
  {
    motorSpeed = 0;
    LeftMotor->run(RELEASE);
  }
}

void moveCar(int x, int y)
 {
  int steering;
  
  if ((y > 482) && (y < 562))//if knob is in the deadzone
  { 
  LeftMotor->run(RELEASE);
  RightMotor->run(RELEASE);
  }
  else if ((x > 482) && (x < 562))//if knob is straight
  {
    if (y > 562)//forward
    {
      LeftMotor->run(FORWARD);
      RightMotor->run(FORWARD);
      motorSpeed = map(y, 562, 1023, 0, 255);
      LeftMotor->setSpeed(motorSpeed);
      RightMotor->setSpeed(motorSpeed);
    }
    else//backward 
    {
    LeftMotor->run(BACKWARD);
    RightMotor->run(BACKWARD);
    motorSpeed = map(y, 562, 1023, 0, 255);
    LeftMotor->setSpeed(motorSpeed);
    RightMotor->setSpeed(motorSpeed);
    }
  }
  else if (y > 512)//if y is forward
  {
    if (x > 512)//if x is right
    { 
      LeftMotor->run(FORWARD);//turn right
      RightMotor->run(FORWARD);
      motorSpeed = map(y, 562, 1023, 0, 255);
      steering = map(x, 523, 1023, 255, 0);
      LeftMotor->setSpeed(motorSpeed);
      RightMotor->setSpeed((motorSpeed*steering)/255);
    }
    else if (x < 512)//if x is left
    { 
      LeftMotor->run(FORWARD);//turn left
      RightMotor->run(FORWARD);
      motorSpeed = map(y, 562, 1023, 0, 255);
      steering = map(x, 500, 0, 255, 0);
      LeftMotor->setSpeed((motorSpeed*steering)/255);
      RightMotor->setSpeed(motorSpeed);
    }
  }
  else if (y < 512)//if y is backward
  {
    if (x > 512)//if x is right
    { 
      LeftMotor->run(BACKWARD);//turn backward and right
      RightMotor->run(BACKWARD);
      motorSpeed = map(y, 562, 1023, 0, 255);
      steering = map(x, 523, 1023, 255, 0);
      LeftMotor->setSpeed(motorSpeed);
      RightMotor->setSpeed((motorSpeed*steering)/255);
    }
    else if (x < 512)//if x is left
    { 
      LeftMotor->run(BACKWARD);//turn backward and left
      RightMotor->run(BACKWARD);
      motorSpeed = map(y, 562, 1023, 0, 255);
      steering = map(x, 500, 0, 255, 0);
      LeftMotor->setSpeed((motorSpeed*steering)/255);
      RightMotor->setSpeed(motorSpeed);
    }
  }
 }


void getCommand()
{
  if (BT.available())
  {
    if(debug){Serial.println("looking");}

    if ('s' == BT.read())
    { //Read data
      getData();

      if(debug)
    {
     SendDebugData;
    }
    
    }
  } 
  //End of Getting Data
}
 
