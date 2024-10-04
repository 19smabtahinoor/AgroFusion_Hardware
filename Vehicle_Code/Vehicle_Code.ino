#include <AFMotor.h>
#include <Servo.h>

Servo myservo;  // create Servo object to control a servo
int pos = 0;    // variable to store the servo position

#define motorSpeed 50
#define servoDelay 40

//Initial motors pin
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
char command;

void setup() {
  delay(5000);
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
  motor1.setSpeed(motorSpeed);  //Define maximum velocity
  motor2.setSpeed(motorSpeed);  //Define maximum velocity
  motor3.setSpeed(motorSpeed);  //Define maximum velocity
  motor4.setSpeed(motorSpeed);  //Define maximum velocity
}

void loop() {
  manual_control();
  //automated_movement();
}

void forward() {
  motor1.run(FORWARD); //rotate the motor clockwise
  motor2.run(FORWARD); //rotate the motor clockwise
  motor3.run(FORWARD); //rotate the motor clockwise
  motor4.run(FORWARD); //rotate the motor clockwise
}

void back() {
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.run(BACKWARD); //rotate the motor clockwise
  motor4.run(BACKWARD); //rotate the motor clockwise
}

void left() {
  motor1.run(BACKWARD); //rotate the motor anti-clockwise
  motor2.run(FORWARD); //rotate the motor anti-clockwise
  motor3.run(FORWARD); //rotate the motor anti-clockwise
  motor4.run(BACKWARD); //rotate the motor anti-clockwise
}

void right() {
  motor1.run(FORWARD); //rotate the motor anti-clockwise
  motor2.run(BACKWARD); //rotate the motor anti-clockwise
  motor3.run(BACKWARD); //rotate the motor anti-clockwise
  motor4.run(FORWARD); //rotate the motor anti-clockwise
}

void stopme() {
  motor1.run(RELEASE); //rotate the motor anti-clockwise
  motor2.run(RELEASE); //rotate the motor anti-clockwise
  motor3.run(RELEASE); //rotate the motor anti-clockwise
  motor4.run(RELEASE); //rotate the motor anti-clockwise
}
