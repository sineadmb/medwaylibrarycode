class Flasher
{
    int ledPin;
    long onTime;
    long offTime;
    int ledState;
    unsigned long previousMillis;
  public:
    Flasher(int Pin, long on, long off)
    {
      ledPin = Pin;
      pinMode(ledPin, OUTPUT);
      onTime = on;
      offTime = off;
      ledState = LOW;
      previousMillis = 0;
    }
    void Update()
    {
      unsigned long currentMillis = millis();
      if ((ledState == HIGH) && (currentMillis - previousMillis >= onTime))
      {
        ledState = LOW;
        previousMillis = currentMillis;
        digitalWrite(ledPin, ledState);
      }
      else if ((ledState == LOW) && (currentMillis - previousMillis == offTime))
      {
        ledState = HIGH;
        previousMillis = currentMillis;
        digitalWrite(ledPin, ledState);
      }
    }
};
