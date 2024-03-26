#include "BTS7960.h" // header in local directory
#include <Arduino.h>
#include "string.h"

BTS7960::BTS7960(int rightPWMPin, int rightEnablePin, int leftPWMPin, int leftEnablePin){
    rPWMPin = rightPWMPin;
    rENPin = rightEnablePin;
    lPWMPin = leftPWMPin;
    lENPin = leftEnablePin;
}

void BTS7960::driveRight(int speed){
    digitalWrite(rENPin, HIGH);
    digitalWrite(lENPin, HIGH);
    analogWrite(rPWMPin, speed);
    analogWrite(lPWMPin, 0);
}

void BTS7960::driveLeft(int speed){
    digitalWrite(rENPin, HIGH);
    digitalWrite(lENPin, HIGH);
    analogWrite(rPWMPin, 0);
    analogWrite(lPWMPin, speed);
}

void BTS7960::brakeCoast() {
    digitalWrite(rENPin, LOW);
    digitalWrite(lENPin, LOW);
    analogWrite(rPWMPin, 0);
    analogWrite(lPWMPin, 0);
}

void BTS7960::brakeHard(){
    //not sure yet have to figure it out
}