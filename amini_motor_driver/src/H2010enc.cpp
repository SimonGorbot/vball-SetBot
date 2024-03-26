#include "H2010enc.h"
#include <Arduino.h>

#define GET_RPM_TIMEOUT 5000
#define NUM_SLITS_PER_DISK 2


H2010enc::H2010enc(int digitalInPin) {
    outPin = digitalInPin;
}

float H2010enc::getRPM(){
    bool prevState = HIGH;
    int pulseTimeFound = 0;
    unsigned long firstPulseTime = 0;
    unsigned long secondPulseTime = 0;
    unsigned long startTime = millis();
    unsigned long currentTime = 0;

    while(pulseTimeFound < 2 && (startTime-currentTime) < GET_RPM_TIMEOUT) {    //haven't gotten two pulses need for calc and haven't spent more than X seconds
       
        if (digitalRead(outPin) == LOW && prevState != LOW && pulseTimeFound == 0){ //if beam is not broken FOR FIRST TIME
            firstPulseTime = millis(); 
            pulseTimeFound++;
            prevState = digitalRead(outPin);
        }

        else if (digitalRead(outPin) == LOW && prevState != LOW && pulseTimeFound == 1){ //if beam is not broken FOR SECOND TIME
            secondPulseTime = millis();
            pulseTimeFound++;
            prevState = digitalRead(outPin);
        } 

        currentTime = millis();
        prevState = digitalRead(outPin);

    }

    int timeBetweenPulses = secondPulseTime - firstPulseTime;

    float rpm = (timeBetweenPulses * NUM_SLITS_PER_DISK) * 1000 * 60;
    return rpm;
}