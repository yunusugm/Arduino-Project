const int pinLed = 6;
const int sensorPin = A0;
int sensorValue;

void setup()
{
  Serial.begin(9600);
  pinMode(pinLed, OUTPUT);
}

void loop()
{
  sensorValue = analogRead(sensorPin);
  if (sensorValue < 20)
  {
    digitalWrite(pinLed, HIGH);
  }
  else
  {
    digitalWrite(pinLed, LOW);
  }

  Serial.print("Sensor Output : ");
  Serial.println(sensorValue);
  delay(100);
}