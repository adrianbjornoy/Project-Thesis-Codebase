/*
    Vibration Motor Control with Slider and Proximity Feedback
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

  // Map the slider value to PWM range (0 to 255)
  int vibrationIntensity = map(sliderValue, 0, 1023, 0, 255);

  // Update motor intensities
  analogWrite(motorPin1, vibrationIntensity);
  analogWrite(motorPin2, vibrationIntensity);
  analogWrite(motorPin3, vibrationIntensity);
  analogWrite(motorPin4, vibrationIntensity);

  // Print the slider value and vibration intensity
  Serial.print("Slider Value: ");
  Serial.print(sliderValue);
  Serial.print(" | Vibration Intensity: ");
  Serial.println(vibrationIntensity);

  delay(50); // Small delay for stability
}
