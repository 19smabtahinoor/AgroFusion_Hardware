void automated_movement() {
  forward();
  delay(800);
  stopme();
  delay(500);
  servo_rotation();
  delay(500);
  
  back();
  delay(1000);
  stopme();
  delay(500);
  servo_rotation();
  delay(500);
}

void servo_rotation() {
  myservo.write(0); //Turn clockwise at high speed
  delay(3000);
  myservo.detach();//Stop. You can use deatch function or use write(x), as x is the middle of 0-180 which is 90, but some lack of precision may change this value
  delay(2000);
  myservo.attach(9);//Always use attach function after detach to re-connect your servo with the board
  myservo.write(180);
  delay(3000);
  myservo.detach();//Stop
  delay(2000);
  myservo.attach(9);
}
