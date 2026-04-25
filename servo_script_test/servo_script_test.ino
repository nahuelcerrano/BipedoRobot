#include <Servo.h>

#define servo_pin D3

Servo servo;

void setup() {
  Serial.begin(115200);

  servo.attach(servo_pin);
}

void loop() {
  servo.write(0);
  delay(1000);

  servo.write(90);
  delay(1000);

  servo.write(180);
  delay(1000);
}
