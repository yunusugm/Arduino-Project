int buzzerPin = 13;
int sensorPin = 8;
int ledPin = 7;
int value;

void setup()
{
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  value = digitalRead(sensorPin);
  if (value == 1)
  {
    // digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
  }
  Serial.println(value);
  delay(500);
}