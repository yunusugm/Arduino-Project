void setup_servo() {
  EXIT.attach(EXIT_PIN);
  ENTER.attach(ENTER_PIN);
  EXIT.write(close_pos);
  ENTER.write(close_pos);
  Serial.println("SG-90 is ready!");
}

void read_servo() {
  int exit_angle = EXIT.read();
  Serial.print("Exit angle: ");
  Serial.println(exit_angle);
}

void exit_interrupt() {
  if (kaldist < 25) {
    EXIT.write(180);
  }
}

void perform_exit() {
  time = millis();
  if (kaldist <= 15) {
    EXIT.write(open_pos);
    previous = time;
  } else {
    if (time - previous >= interval) {
      EXIT.write(close_pos);
      previous = time;
    }
  }

  if (capacity > 0) capacity -= 1;
}