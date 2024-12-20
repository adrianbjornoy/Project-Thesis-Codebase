// Define pins for joystick and LED
const int joystickXPin = A0;       // Joystick X-axis pin
const int ledPin = 4;              // LED pin (must be a PWM-capable pin for analogWrite)

// Variables for level and debounce
int level = 4;                     // Initial LED level (1 to 10)
const int maxLevel = 10;
const int minLevel = 1;

// Joystick neutral and threshold values
const int neutralX = 516;          // Neutral position for X-axis (adjust as needed)
const int threshold = 100;         // Threshold for detecting left or right movement

// Debounce delay for joystick movements
const unsigned long debounceDelay = 300;
unsigned long previousJoystickMillis = 0;  // Tracks time for debouncing joystick movements

// Timing for LED blinking at level 10
unsigned long previousBlinkMillis = 0;
bool ledState = LOW;                    // Tracks current LED state

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);  // Optional: For debugging level changes
}

void loop() {
  unsigned long currentMillis = millis();  // Track current time

  // Read the joystick X-axis position
  int xValue = analogRead(joystickXPin);

  // Check if the joystick is moved left or right with debounce timing
  if (xValue < neutralX - threshold && (currentMillis - previousJoystickMillis >= debounceDelay)) {
    if (level > minLevel) level--;
    Serial.println("Level decreased to: " + String(level));
    previousJoystickMillis = currentMillis;
  }
  else if (xValue > neutralX + threshold && (currentMillis - previousJoystickMillis >= debounceDelay)) {
    if (level < maxLevel) level++;
    Serial.println("Level increased to: " + String(level));
    previousJoystickMillis = currentMillis;
  }

  // Set brightness or blinking behavior based on the current level
  int brightness;
  if (level == 1) {
    brightness = 0;    // LED off
    analogWrite(ledPin, brightness);
  } 
  else if (level == 10) {
    // Blinking pattern for level 10 with very fast blink
    int blinkDelay = 20;  // Set a very short delay for fast blinking
    if (currentMillis - previousBlinkMillis >= blinkDelay) {
      previousBlinkMillis = currentMillis;
      ledState = !ledState;  // Toggle LED state
      analogWrite(ledPin, ledState ? 255 : 0);  // Full brightness or off
    }
  } 
  else {
    brightness = map(level, 2, 9, 30, 230);  // Map levels 2-9 to brightness values
    analogWrite(ledPin, brightness);
  }
}
