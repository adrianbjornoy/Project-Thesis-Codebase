// Pins for vibration motors
int motorPin1 = 4; // North motor
int motorPin2 = 5; // East motor
int motorPin3 = 6; // South motor
int motorPin4 = 7; // West motor

// Pins for input devices
int xAxis = A0;     // Joystick X-axis
int yAxis = A1;     // Joystick Y-axis
int sliderPin = A2; // Slider connected to analog pin A2
int buttonPin = 8;  // Button for switching gamemodes

// Variables for gamemode switching
int gamemode = 0;   // Current gamemode (0 to 3)
int lastButtonState = LOW; // Previous button state
unsigned long lastDebounceTime = 0; // For debouncing
unsigned long debounceDelay = 50;   // Debounce delay
unsigned long lastToggleTime = 0; // For non-blocking delay in frequencyControl
bool motorState = false;          // Track motor ON/OFF state in frequencyControl
int toggleDelay = 1000;           // Default toggle delay

void setup() {
  // Set motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  // Set button pin as input with pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);

  // Start serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Handle button press for gamemode switching
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH && (millis() - lastDebounceTime > debounceDelay)) {
    lastDebounceTime = millis();
    gamemode = (gamemode + 1) % 4; // Cycle through gamemodes (0 to 3)
    indicateGamemode(gamemode);
  }

  lastButtonState = buttonState;

  // Execute behavior based on current gamemode
  switch (gamemode) {
    case 0:
      directionalFeedback();
      break;
    case 1:
      relativeFeedback();
      break;
    case 2:
      frequencyFeedback();
      break;
    case 3:
      intensityFeedback();
      break;
  }
}

// Function to indicate the current gamemode through vibration bursts
void indicateGamemode(int mode) {
  for (int i = 0; i <= mode; i++) {
    setMotors(HIGH);
    delay(200); // Short burst
    setMotors(LOW);
    delay(200); // Pause
    Serial.write("Gamemode switched to:");
    Serial.write(gamemode);
  }
}

// Gamemode 0: Vibration Motor Control with Joystick
void directionalFeedback() {
  int xValue = analogRead(xAxis);
  int yValue = analogRead(yAxis);
  int xVal = xValue - 512; // Center joystick value around 0
  int yVal = yValue - 512;

  int threshold = 100;

  digitalWrite(motorPin1, yVal > threshold ? HIGH : LOW); // North
  digitalWrite(motorPin3, yVal < -threshold ? HIGH : LOW); // South
  digitalWrite(motorPin2, xVal > threshold ? HIGH : LOW); // East
  digitalWrite(motorPin4, xVal < -threshold ? HIGH : LOW); // West

  delay(50); // Small delay for stability
}

// Gamemode 1: Vibration Motor Control with Relative Feedback
void relativeFeedback() {
  int xValue = analogRead(xAxis);
  int xVal = xValue - 512; // Center joystick value around 0
  int threshold = 100;

  if (xVal > threshold) {
    givePositiveFeedback();
  } else if (xVal < -threshold) {
    giveNegativeFeedback();
  }

  delay(100); // Small delay for stability
}

void givePositiveFeedback() {
  for (int i = 0; i < 2; i++) {
    setMotors(HIGH);
    delay(200);
    setMotors(LOW);
    delay(200);
  }
}

void giveNegativeFeedback() {
  for (int i = 0; i < 2; i++) {
    setMotors(HIGH);
    delay(500);
    setMotors(LOW);
    delay(500);
  }
}

// Gamemode 2: Vibration Motor Frequency Control with Slider
void frequencyFeedback() {
  int sliderValue = analogRead(sliderPin);
  int toggleDelay = map(sliderValue, 0, 1023, 2000, 100);

  if (millis() - lastToggleTime >= (toggleDelay / 2)) {
    lastToggleTime = millis();
    motorState = !motorState; // Toggle motor state
    setMotors(motorState ? HIGH : LOW);
  }
}

// Gamemode 3: Vibration Motor Control with Slider and Proximity Feedback
void intensityFeedback() {
  int sliderValue = analogRead(sliderPin);
  int vibrationIntensity = map(sliderValue, 0, 1023, 0, 255);

  analogWrite(motorPin1, vibrationIntensity);
  analogWrite(motorPin2, vibrationIntensity);
  analogWrite(motorPin3, vibrationIntensity);
  analogWrite(motorPin4, vibrationIntensity);

  delay(50); // Small delay for stability
}

// Helper function to set all motors
void setMotors(int state) {
  digitalWrite(motorPin1, state);
  digitalWrite(motorPin2, state);
  digitalWrite(motorPin3, state);
  digitalWrite(motorPin4, state);
}

