void setup_hcsr() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.println("HC-SR04 is ready!");
}

void transmit_hcsr() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
}

double read_distance_cm() {
  duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

void debug_plotter(double dist, double kalmaned) {
  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.print(", ");
  Serial.print("Kalman: ");
  Serial.println(kalmaned);
}

double kalman_hcsr(double U) {
  static const double R = 40;
  static const double H = 1.00;
  static double Q = 10;
  static double P = 0;
  static double U_hat = 0;
  static double K = 0;
  K = P * H / (H * P * H + R);
  U_hat += +K * (U - H * U_hat);
  P = (1 - K * H) * P + Q;
  return U_hat;
}