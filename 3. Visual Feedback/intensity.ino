// Pin configuration
const int joystickPinX = A0; // Joystick X-axis pin
const int ledPins[] = {2, 3, 4, 5, 6, 7}; // LED pins
const int numLEDs = sizeof(ledPins) / sizeof(ledPins[0]);
const int totalLevels = numLEDs * 2; // Twice as many levels

// Thresholds for joystick movement
const int thresholdRight = 550; // Adjust based on your joystick
const int thresholdLeft = 470;  // Adjust based on your joystick
const int neutralZoneLow = 500; // Neutral range (low)
const int neutralZoneHigh = 540; // Neutral range (high)

// State variables
int currentLevel = 0;
bool joystickReleased = true; // Tracks if joystick is in neutral
unsigned long debounceDelay = 200; // Debounce delay in ms
unsigned long lastActionTime = 0; // Last joystick action timestamp

void setup() {
  Serial.begin(9600); // Debugging output
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
    analogWrite(ledPins[i], 0); // Initialize all LEDs to off
  }
  pinMode(joystickPinX, INPUT);
}

void loop() {
  int joystickX = analogRead(joystickPinX);
  unsigned long currentTime = millis();

  // Print joystick reading for debugging
  Serial.print("Joystick X: ");
  Serial.print(joystickX);
  Serial.print(" | Current Level: ");
  Serial.println(currentLevel);

  // Check joystick movement and apply debounce delay
  if (currentTime - lastActionTime > debounceDelay) {
    if (joystickX > thresholdRight && joystickReleased) {
      joystickReleased = false;
      lastActionTime = currentTime;
      if (currentLevel < totalLevels) {
        currentLevel++;
        updateLEDs();
        Serial.println("Moved Right");
      }
    } else if (joystickX < thresholdLeft && joystickReleased) {
      joystickReleased = false;
      lastActionTime = currentTime;
      if (currentLevel > 0) {
        currentLevel--;
        updateLEDs();
        Serial.println("Moved Left");
      }
    }
  }

  // Reset joystickReleased when in neutral zone
  if (joystickX >= neutralZoneLow && joystickX <= neutralZoneHigh) {
    joystickReleased = true;
  }
}

// Update LEDs based on the current level
void updateLEDs() {
  int fullLEDs = currentLevel / 2;        // Number of LEDs fully lit
  int partialLEDIndex = currentLevel % 2; // 0 for full brightness, 1 for 50% brightness

  for (int i = 0; i < numLEDs; i++) {
    if (i < fullLEDs) {
      analogWrite(ledPins[i], 255); // Full brightness
    } else if (i == fullLEDs && partialLEDIndex == 1) {
      analogWrite(ledPins[i], 128); // 50% brightness
    } else {
      analogWrite(ledPins[i], 0);   // Off
    }
  }

  Serial.print("Updated LEDs: Current Level = ");
  Serial.println(currentLevel);
}
