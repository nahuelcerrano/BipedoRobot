#ifndef JOINT_H
#define JOINT_H

#include <Servo.h>
#include <Arduino.h>

class Joint {
    private:
        Servo myServo;
        int pin;
        int minAngle;
        int maxAngle;
        int currentAngle;
    
    public:
        Joint(int attachPin, int minVal, int maxVal, int startPos);
        void begin();
        void setAngle(int targetAngle);
        void setPercentage(int percent);
};

#endif