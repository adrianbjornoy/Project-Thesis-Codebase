/*
    Vibration Motor Frequency Control with Slider
*/

int motorPin1 = 4; // North motor
int motorPin2 = 5; // East motor
int motorPin3 = 6; // South motor
int motorPin4 = 7; // West motor

int sliderPin = A2; // Slider connected to analog pin A2

void setup()
{
  // Set motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  // Start the serial communication for debugging
  Serial.begin(9600);
}

void loop()
{
  // Read the slider value (0 to 1023)
  int sliderValue = analogRead(sliderPin);

  // Map the slider value to a delay range (50ms to 500ms)
  // Smaller delay = higher frequency vibration
  int toggleDelay = map(sliderValue, 0, 1023, 2000, 100);

  // Print the slider value and calculated delay
  Serial.print("Slider Value: ");
  Serial.print(sliderValue);
  Serial.print(" | Toggle Delay (ms): ");
  Serial.println(toggleDelay);

  // Turn all motors ON
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, HIGH);

  // Wait for half the delay time
  delay(toggleDelay / 2);

  // Turn all motors OFF
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);

  // Wait for the other half of the delay time
  delay(toggleDelay / 2);
}
