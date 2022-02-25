const int numLed = 6;
int pinLed[6] = {2, 3, 4, 5, 6, 7};
int sensorPin = A0;
int delayTime = 1000;

void setup()
{
  for (int i = 0; i < numLed; i++)
  {
    pinMode(pinLed[i], OUTPUT);
  }
}

void loop()
{
  for (int i = 0; i < 6; i++)
  {
    delayTime = analogRead(sensorPin);
    digitalWrite(pinLed[i], HIGH);
    delay(delayTime);
    digitalWrite(pinLed[i], LOW);
  }
  for (int i = 5; i >= 0; i--)
  {
    delayTime = analogRead(sensorPin);
    digitalWrite(pinLed[i], HIGH);
    delay(delayTime);
    digitalWrite(pinLed[i], LOW);
  }
}