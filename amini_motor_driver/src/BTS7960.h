#ifndef BTS7960_H
#define BTS7960_H

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

        void driveRight(int speed);
        void driveLeft(int speed);
        void brakeCoast();
        void brakeHard();
};

#endif