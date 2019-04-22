volatile int ISRCount = 0;
void setup() {
  pinMode (2,INPUT_PULLUP); //button
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2),countISR, RISING);
}

void loop() {
  delay (1000);
 Serial.print("Count = ");
 Serial.println(ISRCount,DEC);
}

void countISR (){
ISRCount++;
}

