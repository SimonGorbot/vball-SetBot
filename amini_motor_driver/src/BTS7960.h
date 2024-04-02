#ifndef BTS7960_H
#define BTS7960_H

#define MOTOR_SPIN_L 0b10
#define MOTOR_SPIN_R 0b01

class BTS7960 {
    private:
        int rPWMPin1;
        int rENPin1;
        int lPWMPin1;
        int lENPin1;
        int rPWMPin2;
        int rENPin2;
        int lPWMPin2;
        int lENPin2;
    public:
        BTS7960(int rightPWMPin1, int rightEnablePin1, int leftPWMPin1, int leftEnablePin1,
                     int rightPWMPin2, int rightEnablePin2, int leftPWMPin2, int leftEnablePin2);
        
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