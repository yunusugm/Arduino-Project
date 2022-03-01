const int pinLed[3] = {3, 4, 5};
const byte pushButton = 2;
int state = 0;

void setup()
{
  pinMode(pushButton, INPUT);
  for (int i = 0; i < 3; i++)
  {
    pinMode(pinLed[i], OUTPUT);
  }
}

void loop()
{
  if (digitalRead(pushButton) == HIGH)
  {
    if (state == 0)
    {
      state = 1;
      digitalWrite(pinLed[0], HIGH);
      digitalWrite(pinLed[1], HIGH);
      digitalWrite(pinLed[2], HIGH);
    }
    else
    {
      state = 0;
      digitalWrite(pinLed[0], LOW);
      digitalWrite(pinLed[1], LOW);
      digitalWrite(pinLed[2], LOW);
    }
    delay(1000);
  }
}