#include "BTS7960.h" // header in local directory
#include <Arduino.h>
#include "string.h"

BTS7960::BTS7960(int rightPWMPin1, int rightEnablePin1, int leftPWMPin1, int leftEnablePin1,
                     int rightPWMPin2, int rightEnablePin2, int leftPWMPin2, int leftEnablePin2){
    rPWMPin1 = rightPWMPin1;
    rENPin1 = rightEnablePin1;
    lPWMPin1 = leftPWMPin1;
    lENPin1 = leftEnablePin1;
    rPWMPin2 = rightPWMPin2;
    rENPin2 = rightEnablePin2;
    lPWMPin2 = leftPWMPin2;
    lENPin2 = leftEnablePin2;
}

void BTS7960::motorCommand(int action, int speed){
    if (action == 0b00){    //coast
        digitalWrite(rENPin1, LOW);
        digitalWrite(lENPin1, LOW);
        analogWrite(rPWMPin1, 0);
        analogWrite(lPWMPin1, 0);
        digitalWrite(rENPin2, LOW);
        digitalWrite(lENPin2, LOW);
        analogWrite(rPWMPin2, 0);
        analogWrite(lPWMPin2, 0);
        cmdSpeed = 0;
    }
    
    else if (action == 0b11){   //hard brake
        digitalWrite(rENPin1, LOW);
        digitalWrite(lENPin1, LOW);
        analogWrite(rPWMPin1, 0);
        analogWrite(lPWMPin1, 0);

        digitalWrite(rENPin2, LOW);
        digitalWrite(lENPin2, LOW);
        analogWrite(rPWMPin2, 0);
        analogWrite(lPWMPin2, 0);

        cmdSpeed = 0;
    }

    else if (action == 0b01){   //spin right
        digitalWrite(rENPin1, HIGH);
        digitalWrite(lENPin1, HIGH);
        analogWrite(rPWMPin1, speed);
        analogWrite(lPWMPin1, 0);

        digitalWrite(rENPin2, HIGH);
        digitalWrite(lENPin2, HIGH);
        analogWrite(rPWMPin2, speed);
        analogWrite(lPWMPin2, 0);

        cmdSpeed = speed;        
    }

    else if (action == 0b10){   //spin left
        digitalWrite(rENPin1, HIGH);
        digitalWrite(lENPin1, HIGH);
        analogWrite(rPWMPin1, 0);
        analogWrite(lPWMPin1, speed);

        digitalWrite(rENPin2, HIGH);
        digitalWrite(lENPin2, HIGH);
        analogWrite(rPWMPin2, 0);
        analogWrite(lPWMPin2, speed);

        cmdSpeed = speed; 
    }
}

void BTS7960::motorCommandRamp(int action, int speed){
    if (action == 0b00){    //coast
        digitalWrite(rENPin1, LOW);
        digitalWrite(lENPin1, LOW);
        analogWrite(rPWMPin1, 0);
        analogWrite(lPWMPin1, 0);

        digitalWrite(rENPin2, LOW);
        digitalWrite(lENPin2, LOW);
        analogWrite(rPWMPin2, 0);
        analogWrite(lPWMPin2, 0);

        cmdSpeed = 0;
    }
    
    else if (action == 0b11){   //hard brake
        digitalWrite(rENPin1, LOW);
        digitalWrite(lENPin1, LOW);
        analogWrite(rPWMPin1, 0);
        analogWrite(lPWMPin1, 0);

        digitalWrite(rENPin2, LOW);
        digitalWrite(lENPin2, LOW);
        analogWrite(rPWMPin2, 0);
        analogWrite(lPWMPin2, 0);

        cmdSpeed = 0;
    }

    else if (action == 0b01){   //spin right
        digitalWrite(rENPin1, HIGH);
        digitalWrite(lENPin1, HIGH);
        analogWrite(lPWMPin1, 0);

        digitalWrite(rENPin2, HIGH);
        digitalWrite(lENPin2, HIGH);
        analogWrite(lPWMPin2, 0);

        for (int i = 0; i <= speed; i++){
            analogWrite(rPWMPin1, i);
            analogWrite(rPWMPin2, i);
            delay(50);
        }

        cmdSpeed = speed;        
    }

    else if (action == 0b10){   //spin left
        digitalWrite(rENPin1, HIGH);
        digitalWrite(lENPin1, HIGH);
        analogWrite(rPWMPin1, 0);

        digitalWrite(rENPin2, HIGH);
        digitalWrite(lENPin2, HIGH);
        analogWrite(rPWMPin2, 0);

        for (int i = 0; i <= speed; i++){
            analogWrite(lPWMPin1, i);
            analogWrite(lPWMPin2, i);
            delay(50);
        }
        
        cmdSpeed = speed;
    }
}


void BTS7960::driveRight(int speed){
    digitalWrite(rENPin1, HIGH);
    digitalWrite(lENPin1, HIGH);
    analogWrite(rPWMPin1, speed);
    analogWrite(lPWMPin1, 0);
    digitalWrite(rENPin2, HIGH);
    digitalWrite(lENPin2, HIGH);
    analogWrite(rPWMPin2, speed);
    analogWrite(lPWMPin2, 0);
}

void BTS7960::driveLeft(int speed){
    digitalWrite(rENPin1, HIGH);
    digitalWrite(lENPin1, HIGH);
    analogWrite(rPWMPin1, 0);
    analogWrite(lPWMPin1, speed);
    digitalWrite(rENPin2, HIGH);
    digitalWrite(lENPin2, HIGH);
    analogWrite(rPWMPin2, 0);
    analogWrite(lPWMPin2, speed);
}

void BTS7960::brakeCoast() {
    digitalWrite(rENPin1, LOW);
    digitalWrite(lENPin1, LOW);
    analogWrite(rPWMPin1, 0);
    analogWrite(lPWMPin1, 0);
    digitalWrite(rENPin2, LOW);
    digitalWrite(lENPin2, LOW);
    analogWrite(rPWMPin2, 0);
    analogWrite(lPWMPin2, 0);
}

void BTS7960::brakeHard(){
    //not sure yet have to figure it out
    digitalWrite(rENPin1, LOW);
    digitalWrite(lENPin1, LOW);
    analogWrite(rPWMPin1, 0);
    analogWrite(lPWMPin1, 0);
    digitalWrite(rENPin2, LOW);
    digitalWrite(lENPin2, LOW);
    analogWrite(rPWMPin2, 0);
    analogWrite(lPWMPin2, 0);
}