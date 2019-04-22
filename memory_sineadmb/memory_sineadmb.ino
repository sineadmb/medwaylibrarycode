 
 #include <EEPROM.h> 
 int val;
 char state;
 int address;

void setup() {
  Serial.begin(9600);
  
}

void loop() {
  while(!Serial.available()){
  delay(10);
  }
  state = Serial.read();
  if (state == 'w')
  {
  Serial.println("Write data:");
  Serial.println("Where?");
  while(!Serial.available()){
  delay(10);}
  address = Serial.parseInt();
  Serial.println("What int?");
  while(!Serial.available()){
  delay(10);}
  val = Serial.parseInt();
  EEPROM.write(address,val);
  Serial.println("Wrote");
  Serial.println(val);
  Serial.println("to");
  Serial.println(address);
  }
  else if (state == 'r')
  {
  Serial.println("Read data:");
  Serial.println("From where?");
  while(!Serial.available()){
  delay(10);}
  address = Serial.parseInt();
  val = EEPROM.read(address);
  Serial.println(val);
  }
  else
  {
    Serial.println("Bad Command");
  }
}

