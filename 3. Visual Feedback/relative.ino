// Define pin connections
const int redLEDPin = 3;        // Red LED pin
const int greenLEDPin = 4;      // Green LED pin
const int joystickXPin = A0;    // Joystick X-axis pin

// Threshold values for joystick movement
const int neutralX = 516;       // Neutral position for X-axis (adjust as needed)
const int threshold = 100;      // Threshold for detecting left or right movement

void setup() {
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  Serial.begin(9600);  // Optional: For debugging
}

void loop() {
  int xValue = analogRead(joystickXPin);   // Read the X-axis position of the joystick

  // Check if the joystick is moved left or right
  if (xValue < neutralX - threshold) {
    // Joystick moved left, turn on the red LED and turn off the green LED
    digitalWrite(redLEDPin, HIGH);
    digitalWrite(greenLEDPin, LOW);
    Serial.println("Joystick left - Red LED ON");
  } 
  else if (xValue > neutralX + threshold) {
    // Joystick moved right, turn on the green LED and turn off the red LED
    digitalWrite(redLEDPin, LOW);
    digitalWrite(greenLEDPin, HIGH);
    Serial.println("Joystick right - Green LED ON");
  } 
  else {
    // Joystick is in neutral position, turn off both LEDs
    digitalWrite(redLEDPin, LOW);
    digitalWrite(greenLEDPin, LOW);
    Serial.println("Joystick neutral - Both LEDs OFF");
  }

  delay(100); // Optional: Small delay for stability
}
