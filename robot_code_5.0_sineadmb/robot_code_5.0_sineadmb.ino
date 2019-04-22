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
   rightMotor->setSpeed(100);  // 10 rpm
   leftMotor->setSpeed(100);  // 10 rpm


   RightMotor->setSpeed(50);         // Set start motor speed
   LeftMotor->setSpeed(50);          // from 0 (off) to 255 (max speed)

   RightMotor->run(FORWARD);         // turn on motor
   RightMotor->run(RELEASE);
   LeftMotor->run(FORWARD);          // turn on motor
   LeftMotor->run(RELEASE);

   servoC.attach(ServoClaw);
   servoU.attach(ServoUp);
 
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

/*    
    
    Serial.println(state);

    if (mode == 0 ) 
    {
     if (state=='m')
     { 
      DriveMode=DriveMode+1;
      
      if (DriveMode==NumberOfModes);
      DriveMode=0; 
      digitalWrite(ledPin, DriveMode );
     }
    }
    else if (mode == 1 )
    {
      if (state == 's')     // speed state
      {
        val = BT.parseInt();               // Get Int from serial port
        s = val;
      } //End of "speed" state
      
     else if (state == 'd')  //Left Motor
      {
        val = BT.parseInt();              // Get Int from serial port
        d = val;
      }
      
        else if (state=='m')
       { 
        DriveMode=DriveMode+1;
        
        if (DriveMode==NumberOfModes);
        DriveMode=0; 
        digitalWrite(ledPin, DriveMode );
      }
    }
    else if (mode == 2 )
    {
      //Tank Mode
    }
    
  }
    
{
 // Serial.print(s);
 // Serial.print(d);
 // Serial.println("testing-");
  

  setMotors(s, d);
}  
*/
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


