#ifndef BTS7960_H
#define BTS7960_H

#define MOTOR_SPIN_L 0b10
#define MOTOR_SPIN_R 0b01

class BTS7960 {
    private:
        int rPWMPin;
        int rENPin;
        int lPWMPin;
        int lENPin;
    public:
        BTS7960(int rightPWMPin, int rightEnablePin, int leftPWMPin, int leftEnablePin);
        
        int cmdSpeed;
        int cmdDir;

        void motorCommand(int action, int speed);
        void motorCommandRamp(int action, int speed);
        void driveRight(int speed);
        void driveLeft(int speed);
        void brakeCoast();
        void brakeHard();
};

#endif