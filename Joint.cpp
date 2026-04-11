#include "Joint.h"

Joint::Joint(int attachPin, int minVal, int maxVal, int startPos) {
  pin = attachPin;
  minAngle = minVal;
  maxAngle = maxVal;
  currentAngle = startPos;
}

void Joint::begin() {
  myServo.attach(pin);
  setAngle(currentAngle);
}

void Joint::setAngle(int targetAngle) {
  if (targetAngle > maxAngle) {
    targetAngle = maxAngle;
  } else if (targetAngle < minAngle) {
    targetAngle = minAngle;
  }
  myServo.write(targetAngle);
  currentAngle = targetAngle;
}

void Joint::setPercentage(int percent) {
  if(percent < 0) percent = 0;
  if(percent > 100) percent = 100;
  
  int targetAngle = map(percent, 0, 100, minAngle, maxAngle);
  setAngle(targetAngle);
}