#include <LiquidCrystal_I2C.h>
#include <Servo.h>

Servo EXIT;
Servo ENTER;

#define EXIT_PIN 9
#define ENTER_PIN 10
#define TRIG_PIN 5
#define ECHO_PIN 2

const int open_pos = 180, close_pos = 0;
int capacity = 0, interval = 2000;
double distance, duration, kaldist;
unsigned long time, previous;

void setup() {
  Serial.begin(115200);
  setup_hcsr();
  setup_servo();

  // attachInterrupt(digitalPinToInterrupt(ECHO_PIN), exit_interrupt, FALLING);
}

void loop() {
  transmit_hcsr();
  distance = read_distance_cm();
  kaldist = kalman_hcsr(distance);
  // debug_plotter(distance, kaldist);
  perform_exit();
}
