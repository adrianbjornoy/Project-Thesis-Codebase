/*
    Vibration Motor Control with Joystick and Arduino
*/

int motorPin1 = 4; // North motor
int motorPin2 = 5; // East motor
int motorPin3 = 6; // South motor
int motorPin4 = 7; // West motor

int xAxis = A0;    // Joystick X-axis
int yAxis = A1;    // Joystick Y-axis

void setup()
{
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}

void loop()
{
  int xValue = analogRead(xAxis);
  int yValue = analogRead(yAxis);

  // Center the joystick values around 0
  int xVal = xValue - 512;
  int yVal = yValue - 512;

  int threshold = 100; // 

  // Initialize motor states
  bool motor1On = false; // North
  bool motor2On = false; // East
  bool motor3On = false; // South
  bool motor4On = false; // West

  // Determine which motors to activate
  if (yVal > threshold) {
    motor1On = true; // North
  }
  if (yVal < -threshold) {
    motor3On = true; // South
  }
  if (xVal > threshold) {
    motor2On = true; // East
  }
  if (xVal < -threshold) {
    motor4On = true; // West
  }

  // Update motor states
  digitalWrite(motorPin1, motor1On ? HIGH : LOW);
  digitalWrite(motorPin2, motor2On ? HIGH : LOW);
  digitalWrite(motorPin3, motor3On ? HIGH : LOW);
  digitalWrite(motorPin4, motor4On ? HIGH : LOW);

  delay(50); // Small delay to stabilize readings
}
