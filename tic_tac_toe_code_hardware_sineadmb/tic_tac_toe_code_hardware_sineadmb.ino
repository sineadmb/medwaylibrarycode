void setup() {
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
digitalWrite(2, HIGH);
digitalWrite(3, HIGH);
digitalWrite(4, HIGH);
pinMode(5, INPUT_PULLUP);
pinMode(6, INPUT_PULLUP);
pinMode(7, INPUT_PULLUP);
Serial.begin(9600);
}

void loop() {
digitalWrite(2, LOW);
if(!digitalRead(5)){
Serial.println("2,5");
}
digitalWrite(2, LOW);
if(!digitalRead(6)){
Serial.println("2,6");
}
digitalWrite(2, LOW);
if(!digitalRead(7)){
Serial.println("2,7");
}
digitalWrite(2, HIGH);


digitalWrite(3, LOW);
if(!digitalRead(5)){
Serial.println("3,5");
}
digitalWrite(3, LOW);
if(!digitalRead(6)){
Serial.println("3,6");
}
digitalWrite(3, LOW);
if(!digitalRead(7)){
Serial.println("3,7");
}
digitalWrite(3, HIGH);


digitalWrite(4, LOW);
if(!digitalRead(5)){
Serial.println("4,5");
}
digitalWrite(4, LOW);
if(!digitalRead(6)){
Serial.println("4,6");
}
digitalWrite(4, LOW);
if(!digitalRead(7)){
Serial.println("4,7");
}
digitalWrite(4, HIGH);
}
