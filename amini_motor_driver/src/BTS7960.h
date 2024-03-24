#ifndef BTS7960_H
#define BTS7960_H

class BTS7960 {
    private:
        int rPWMPin;
        int rENPin;
        int lPWMPin;
        int lENPin;
    public:
        BTS7960(int RIGHT_PWM_PIN, int RIGHT_ENABLE_PIN, int LEFT_PWM_PIN, int LEFT_ENABLE_PIN);
        
        int cmdSpeed;
        int cmdDir;

        void driveRight(int speed);
        void driveLeft(int speed);
        void brakeCoast();
        void brakeHard();
};

#endif