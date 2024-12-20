// Pin assignments for the LEDs
const int led1 = 2;  // Up
const int led2 = 3;  // Down
const int led3 = 4;  // Right
const int led4 = 5;  // Left

// Pin assignments for the joystick
const int joystickX = A0;  // Horizontal movement
const int joystickY = A1;  // Vertical movement

// Threshold to detect when the joystick is moved in a direction
const int threshold = 400;  // Adjust if needed based on joystick sensitivity

void setup() {
  // Set LED pins as outputs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  // Initialize serial communication (optional, for debugging)
  Serial.begin(9600);
} 

void loop() {
  // Read joystick values
  int xValue = analogRead(joystickX);  // X-axis (left/right)
  int yValue = analogRead(joystickY);  // Y-axis (up/down)

  // Debugging output (optional)
  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" | Y: ");
  Serial.println(yValue);

  // Turn off all LEDs first
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);

  // Joystick up (Y-axis is lower than the threshold)
  if (yValue < threshold) {
    digitalWrite(led1, HIGH);  // Turn on the first LED (Up)
  }
  // Joystick down (Y-axis is higher than the threshold)
  else if (yValue > 1023 - threshold) {
    digitalWrite(led2, HIGH);  // Turn on the second LED (Down)
  }

  // Joystick right (X-axis is higher than the threshold)
  if (xValue < threshold) {
    digitalWrite(led3, HIGH);  // Turn on the third LED (Right)
  }
  // Joystick left (X-axis is lower than the threshold)
  else if (xValue > 1023 - threshold) {
    digitalWrite(led4, HIGH);  // Turn on the fourth LED (Left)
  }

  // Small delay to avoid rapid switching
  delay(100);
}
