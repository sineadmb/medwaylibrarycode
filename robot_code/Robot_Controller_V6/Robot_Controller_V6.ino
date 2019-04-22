/*
  Controller Code for Medway space robot
  4/2/18
  by Gaston Marzoratti
  This supports
  -Bluetooth
  -two Knob
  -4 buttons
*/

# define debug false
                                                                                 
#include <SoftwareSerial.h> //Creates serial ports for Digital IO
SoftwareSerial BT(10, 11);  //Creates Serial Port 10-TX, 11-RX
//for Blutooth Module

// Define the analog pins and knob connections

# define JoyRX 3  // Right joy stick up dowm
# define JoyRY 2  //d
# define JoyRB 6  //c
# define JoyLX 1  //
# define JoyLY 0  //d
# define JoyLB 7  //c

# define ButTop    2
# define ButLeft   4
# define ButRight  3
# define ButBottom 5

int rx;    // variable to read the value from the analog pin
int ry;    // variable to read the value from the analog pin
int lx;    // variable to read the value from the analog pin
int ly;    // variable to read the value from the analog pin

int jrb;
int jlb;
int tb;
int lb;
int rb;
int bb;

void setup()
{
  Serial.begin(9600);  // Begin Serial for debug
  BT.begin(9600);      // Begin Serial for Bluetooth module
  
  int ledPin = 13;
  pinMode(ledPin, OUTPUT);
  pinMode(JoyRB, INPUT_PULLUP);  
  pinMode(JoyLB, INPUT_PULLUP);
  pinMode(ButTop, INPUT_PULLUP);
  pinMode(ButRight, INPUT_PULLUP);
  pinMode(ButLeft, INPUT_PULLUP);
  pinMode(ButBottom, INPUT_PULLUP);

}

void loop()
{
  //Read Joy Sticks axis
  rx = analogRead(JoyRX);   // read potentiometer (value between 0 and 1023)
  ry = analogRead(JoyRY);
  lx = analogRead(JoyLX);
  ly = analogRead(JoyLY);

  //Read Buttons
  jrb = digitalRead(JoyRB);
  jlb = digitalRead(JoyLB);
  tb = digitalRead(ButTop);
  lb = digitalRead(ButLeft);
  rb = digitalRead(ButRight);
  bb = digitalRead(ButBottom);

  //Send Data
  BT.print('s');
  BT.print(rx);
  BT.print("_");
  BT.print(ry);
  BT.print("_");
  BT.print(lx);
  BT.print("_");
  BT.print(ly);
  BT.print("_");
  BT.print(jlb);
  BT.print("_");
  BT.print(jrb);
  BT.print("_");
  BT.print(tb);
  BT.print("_");
  BT.print(lb);
  BT.print("_");
  BT.print(rb);
  BT.print("_");
  BT.print(bb);

  if(debug)
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
    Serial.print(tb);
    Serial.print("--");
    Serial.print(lb);
    Serial.print("--");
    Serial.print(rb);
    Serial.print("--");
    Serial.print(bb);
    Serial.println("--Done");
  }

  
  delay(100);                //Give time to execute

}

