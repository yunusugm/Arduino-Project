#include <Servo.h>
Servo servo;

// ? Angle Awal
int angle = 0;
// ? Set Pin
const int triggerPin = 12;
const int echoPin = 11;
// ? Set Variable
int distance;
long duration;

void setup()
{
  // ? Komunikasi serial
  Serial.begin(9600);
  // ? Set servo pin
  servo.attach(8);
  servo.write(angle);
  // ? Set Sensor PinMode
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  // ? Clear triggerPin 2 microsec
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // ? Set tiggerPin ke HIGH untuk 10 microsec
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  // ? Read echoPin return waktu tempuh gelombang suara dalam microsec
  duration = pulseIn(echoPin, HIGH);
  // ? Calc distance
  distance = duration * 0.034 / 2;
  Serial.print("Distance : ");
  Serial.println(distance);
  delay(100);

  // ? Set logic servo
  if (distance < 20)
  {
    servo.write(180);
  }
  else
  {
    servo.write(60);
  }
}