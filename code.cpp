#include <Servo.h>

/* ------------ Servo Motors ------------ */
Servo FL;   // Front Left
Servo FR;   // Front Right
Servo RL;   // Rear Left
Servo RR;   // Rear Right

/* ------------ IR Sensors ------------ */
// Black line  -> LOW
// White floor -> HIGH
int IR_L2 = 2;   // Extreme Left
int IR_L1 = 3;   // Left
int IR_R1 = 4;   // Right
int IR_R2 = 5;   // Extreme Right

/* ------------ Servo Pins ------------ */
int FL_pin = 6;
int FR_pin = 7;
int RL_pin = 9;
int RR_pin = 10;

/* ------------ Speed Control ------------ */
// Continuous rotation servo values
int STOP_SPEED = 90;
int FORWARD_SPEED = 105;
int TURN_SPEED = 120;

void setup() {
  // Attach servos
  FL.attach(FL_pin);
  FR.attach(FR_pin);
  RL.attach(RL_pin);
  RR.attach(RR_pin);

  // IR sensor inputs
  pinMode(IR_L2, INPUT);
  pinMode(IR_L1, INPUT);
  pinMode(IR_R1, INPUT);
  pinMode(IR_R2, INPUT);

  stopCar();
}

void loop() {
  // Read IR sensors
  int L2 = digitalRead(IR_L2);
  int L1 = digitalRead(IR_L1);
  int R1 = digitalRead(IR_R1);
  int R2 = digitalRead(IR_R2);

  /* ------------ Decision Logic ------------ */

  // Straight line
  if (L1 == LOW && R1 == LOW) {
    moveForward();
  }
  // Slight left correction
  else if (L1 == LOW && R1 == HIGH) {
    turnLeft();
  }
  // Slight right correction
  else if (L1 == HIGH && R1 == LOW) {
    turnRight();
  }
  // Sharp left (90-degree turn)
  else if (L2 == LOW) {
    sharpLeft();
  }
  // Sharp right (90-degree turn)
  else if (R2 == LOW) {
    sharpRight();
  }
  // Line lost
  else {
    stopCar();
  }
}

/* ------------ Movement Functions ------------ */

void moveForward() {
  FL.write(FORWARD_SPEED);
  RL.write(FORWARD_SPEED);
  FR.write(180 - FORWARD_SPEED);
  RR.write(180 - FORWARD_SPEED);
}

void turnLeft() {
  FL.write(STOP_SPEED);
  RL.write(STOP_SPEED);
  FR.write(180 - TURN_SPEED);
  RR.write(180 - TURN_SPEED);
}

void turnRight() {
  FL.write(TURN_SPEED);
  RL.write(TURN_SPEED);
  FR.write(180 - STOP_SPEED);
  RR.write(180 - STOP_SPEED);
}

void sharpLeft() {
  FL.write(STOP_SPEED);
  RL.write(STOP_SPEED);
  FR.write(180 - TURN_SPEED);
  RR.write(180 - TURN_SPEED);
  delay(300);   // adjust for exact 90-degree turn
}

void sharpRight() {
  FL.write(TURN_SPEED);
  RL.write(TURN_SPEED);
  FR.write(180 - STOP_SPEED);
  RR.write(180 - STOP_SPEED);
  delay(300);   // adjust for exact 90-degree turn
}

void stopCar() {
  FL.write(STOP_SPEED);
  FR.write(STOP_SPEED);
  RL.write(STOP_SPEED);
  RR.write(STOP_SPEED);
}
