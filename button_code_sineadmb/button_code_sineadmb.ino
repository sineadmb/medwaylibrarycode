int buttonState;

void setup() {
 pinMode(2,OUTPUT);
 pinMode(5,INPUT_PULLUP);
 Serial.begin(9600);
}

void loop() {
  digitalWrite(2, LOW);
  buttonState = digitalRead(5);
  Serial.println(buttonState);
}
