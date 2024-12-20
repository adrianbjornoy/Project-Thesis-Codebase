// Define the number of rows and columns in the matrix
const int numRows = 6;
const int numCols = 6; 

// Define the pin numbers for rows and columns
const int rowPins[numRows] = {A0, A1, A2, A3, A4, A5};  // Analog pins connected to rows
const int colPins[numCols] = {2, 3, 4, 5, 6, 7};        // Digital pins connected to columns

// 2D array to hold sensor values
float sensorMatrix[numRows][numCols];

// Known resistor value in ohms
const float R_known = 1000.0; 

void setup() {
  // Initialize row pins as inputs
  for (int row = 0; row < numRows; row++) {
    pinMode(rowPins[row], INPUT);
  }
  
  // Initialize column pins as outputs
  for (int col = 0; col < numCols; col++) {
    pinMode(colPins[col], OUTPUT);
    digitalWrite(colPins[col], LOW); // Ensure columns are initially LOW
  }
  
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  // Collect sensor values into the matrix
  for (int col = 0; col < numCols; col++) {
    // Activate the current column
    digitalWrite(colPins[col], HIGH);
    delayMicroseconds(10); // Short delay to stabilize the signal

    // Read values for all rows
    for (int row = 0; row < numRows; row++) {
      int adcValue = analogRead(rowPins[row]);

      // // Prevent division by zero
      // if (adcValue == 0) {
      //   adcValue = 0.001;
      // }

      // Calculate the resistance of the sensor
      // float resistance = R_known * (1023.0 / adcValue - 1.0) / 1000;

      // Store the resistance value
      sensorMatrix[row][col] = adcValue;
    }

    // Deactivate the current column
    digitalWrite(colPins[col], LOW);
  }

  // Output the matrix over the serial interface
  sendMatrixOverSerial();

  delay(100);  // Small delay before next reading
}

// Function to send the matrix data over serial
void sendMatrixOverSerial() {
  for (int row = 0; row < numRows; row++) {
    for (int col = 0; col < numCols; col++) {
      Serial.print(sensorMatrix[row][col], 2); // Two decimal places
      if (col < numCols - 1) {
        Serial.print(",");  // Column separator
      }
    }
    Serial.println();  // Row separator
  }
  Serial.println();  // Matrix separator
}
