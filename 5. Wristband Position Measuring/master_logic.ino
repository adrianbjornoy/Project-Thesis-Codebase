const float dia = 23.3;
const int steps = 20;
const float pi = 3.14;
const float b = 300; // Distance between the two encoder mounts

struct Pos {
  float x;
  float y;
};

Pos position;

int inBytex = 0;
int inBytey = 0;

float rot2len(int pos){
  // Convert encoder count to length of pulled wire
  // L = (dia * pi * pos) / steps
  return (dia * pi * float(pos) / float(steps));
}

Pos calcPos(float L1, float L2){
  Pos pos;
  // From the derived equations:
  pos.x = ((L1*L1) - (L2*L2) + (b*b)) / (2*b);
  pos.y = sqrt((L1*L1) - (pos.x*pos.x));
  return pos;
}

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
}

void loop() {
  // Read encoder values from Serial1 and Serial2
  if (Serial1.available()) {
    inBytex = Serial1.parseInt();  
  }
  if (Serial2.available()) {
    inBytey = Serial2.parseInt();  
  }

  // Only calculate position if both encoder counts are valid

  if (inBytex > 0 && inBytey > 0) {
    float L1 = rot2len(inBytex);
    float L2 = rot2len(inBytey);
    position = calcPos(L1, L2);
    Serial.print("x: ");
    Serial.print(position.x);
    Serial.print(" | y: ");
    Serial.println(position.y);

  }
}
