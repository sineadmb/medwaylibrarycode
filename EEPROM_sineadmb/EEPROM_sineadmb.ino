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
  EEPROMWriteInt(address,val);
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
  val = EEPROMReadInt(address);
  Serial.println("It says...");
  Serial.println(val);
  }
  else
  {
    Serial.println("Bad Command");
  }
}

void EEPROMWriteInt(int address, int value)
{
  byte lowbyte = ((value >> 0)& 0xFF);
  byte highbyte = ((value >> 8)& 0xFF);
  EEPROM.write(address+1,lowbyte);
  EEPROM.write(address,highbyte);
}

unsigned int EEPROMReadInt(int address)
{
  byte lowbyte = EEPROM.read(address+1);
  byte highbyte = EEPROM.read(address);
  int value = lowbyte + (highbyte << 8);
  return (value);
}

