const int joystickPinX = A0;  // Joystick x-axis connected to A0
const int ledPin = 4;         // LED connected to pin 9
const int neutralX = 508;     // Neutral x-axis value (joystick center)
const int threshold = 50;     // Threshold to detect significant movement
int level = 4;                // Initial level
unsigned long previousMillis = 0; // For non-blocking LED blink
unsigned long lastLevelChangeMillis = 0; // For non-blocking delay after level change
int blinkInterval = 1000;     // Initial blink interval (in ms)
const int debounceDelay = 200; // Short delay between level changes (in ms)

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); // For debugging levels only
}

void loop() {
  int xValue = analogRead(joystickPinX); // Read joystick x-axis value

  // Detect joystick movement to the right or left
  unsigned long currentMillis = millis();
  if (currentMillis - lastLevelChangeMillis >= debounceDelay) {
    if (xValue > neutralX + threshold) {
      increaseLevel();
      lastLevelChangeMillis = currentMillis; // Update the last change time
    } else if (xValue < neutralX - threshold) {
      decreaseLevel();
      lastLevelChangeMillis = currentMillis; // Update the last change time
    }
  }

  // Control LED based on the level
  handleLED();
}

void increaseLevel() {
  if (level < 10) {
    level++;
    Serial.print("Level increased to: ");
    Serial.println(level);
    updateBlinkInterval();
  }
}

void decreaseLevel() {
  if (level > 1) {
    level--;
    Serial.print("Level decreased to: ");
    Serial.println(level);
    updateBlinkInterval();
  }
}

void updateBlinkInterval() {
  // Update blink interval for levels 2-9
  if (level > 1 && level < 10) {
    blinkInterval = map(level, 2, 9, 500, 100); // Faster blinking as level increases
  }
}

void handleLED() {
  unsigned long currentMillis = millis();

  if (level == 1) {
    digitalWrite(ledPin, LOW); // LED off
  } else if (level == 10) {
    digitalWrite(ledPin, HIGH); // Continuous light
  } else {
    // Blinking (non-blocking)
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      int ledState = digitalRead(ledPin); // Toggle LED state
      digitalWrite(ledPin, !ledState);
    }
  }
}
