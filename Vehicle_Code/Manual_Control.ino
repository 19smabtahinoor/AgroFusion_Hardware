void manual_control() {
  while (Serial.available()) {
    command = Serial.read();
    switch (command) {

      case 'F':
        forward();
        break;

      case 'B':
        back();
        break;

      case 'L':
        left();
        break;

      case 'R':
        right();
        break;

      case 'V':
        servo_rotation();
        break;

      default:
        stopme();
    }
  }
}
