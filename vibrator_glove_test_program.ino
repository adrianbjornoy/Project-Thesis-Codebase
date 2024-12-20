/*
    Vibration Motor with Arduino
    For more details, visit: https://techzeero.com/arduino-tutorials/vibration-motor-with-arduino/

    FUNCTION TO TEST THAT THE VIBRATORS ARE WORKING
*/

int motorPin1 = 4; //NORTH
int motorPin2 = 5; //EAST
int motorPin3 = 6; //SOUTH
int motorPin4 = 7; //WEST

void setup()
{
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}

void loop()
{
  digitalWrite(motorPin1, HIGH); //vibrate
  delay(250);  // delay one second
  digitalWrite(motorPin1, LOW);  //stop vibrating
  delay(250); //wait one second.

  digitalWrite(motorPin2, HIGH); //vibrate
  delay(250);  // delay one second
  digitalWrite(motorPin2, LOW);  //stop vibrating
  delay(250); //wait one second.

  digitalWrite(motorPin3, HIGH); //vibrate
  delay(250);  // delay one second
  digitalWrite(motorPin3, LOW);  //stop vibrating
  delay(250); //wait one second.

  digitalWrite(motorPin4, HIGH); //vibrate
  delay(250);  // delay one second
  digitalWrite(motorPin4, LOW);  //stop vibrating
  delay(250); //wait one second.
}
