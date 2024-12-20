#include <EncoderButton.h>

EncoderButton eb1(2, 3);

void onEb1Encoder(EncoderButton& eb) {
  Serial.println(eb.position());
}

void setup() {
  Serial.begin(9600);
  eb1.setEncoderHandler(onEb1Encoder);
}

void loop() {
  eb1.update();
}
