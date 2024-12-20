/*
    Vibration Motor Control with Relative Feedback (Joystick)
*/

int motorPin1 = 4; // North motor
int motorPin2 = 5; // East motor
int motorPin3 = 6; // South motor
int motorPin4 = 7; // West motor

int xAxis = A0;    // Joystick X-axis
int threshold = 100; // Threshold to detect significant movement

void setup()
{
  // Set motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  // Start serial communication for debugging
  Serial.begin(9600);
}

void loop()
{
  // Read joystick X-axis value
  int xValue = analogRead(xAxis);
  int xVal = xValue - 512; // Center joystick value around 0

  // Check joystick direction
  if (xVal > threshold) {
    // Correct movement: Right
    Serial.println("Correct Movement: Positive Feedback");
    givePositiveFeedback();
  } else if (xVal < -threshold) {
    // Incorrect movement: Left
    Serial.println("Incorrect Movement: Negative Feedback");
    giveNegativeFeedback();
  }

  delay(100); // Small delay to stabilize readings
}

void givePositiveFeedback()
{
  // Two short vibration bursts
  for (int i = 0; i < 2; i++) {
    setMotors(HIGH); // Turn motors on
    delay(200);      // Short burst duration (200ms)
    setMotors(LOW);  // Turn motors off
    delay(200);      // Pause between bursts
  }
}

void giveNegativeFeedback()
{
  // Two long vibration bursts
  for (int i = 0; i < 2; i++) {
    setMotors(HIGH); // Turn motors on
    delay(500);      // Long burst duration (500ms)
    setMotors(LOW);  // Turn motors off
    delay(500);      // Pause between bursts
  }
}

void setMotors(int state)
{
  // Set all motors to the specified state (HIGH or LOW)
  digitalWrite(motorPin1, state);
  digitalWrite(motorPin2, state);
  digitalWrite(motorPin3, state);
  digitalWrite(motorPin4, state);
}
