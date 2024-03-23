#include <Arduino.h>
#include "string.h"
#include "Wire.h"
#include "BTS7960.h"

const int LEFT_CONTROL_PWM_SIG = 5;
const int RIGHT_CONTROL_PWM_SIG = 3;
const int RIGHT_CONTROL_EN = 12;
const int LEFT_CONTROL_EN = 10;

BTS7960 testMotor {RIGHT_CONTROL_PWM_SIG, RIGHT_CONTROL_EN, LEFT_CONTROL_PWM_SIG, LEFT_CONTROL_EN};

String mot_com_str = "\t10101000000010000000\n";

uint32_t mot_com_bint = strtol(mot_com_str.c_str(), NULL, 2); //convert binary command string into binary int 

uint32_t dir1 = mot_com_bint >> (20-2); //isolates bits 19 and 18 for motor 1 direction
uint32_t dir2 = mot_com_bint >> (20-4) & 0b11; //isolates bits 17 and 16 for motor 2 direction 
uint32_t speed1 = mot_com_bint >> 8 & 0b11111111; //isolates bits 15 to 7 for motor 1 speed
uint32_t speed2 = mot_com_bint & 0b11111111; //isolates bits 7 to 0 for motor 2 speed

void motorRamp();

void setup() {
  Serial.begin(115200);

  //set up PWM output pins for motor drivers
  pinMode(LEFT_CONTROL_PWM_SIG, OUTPUT);
  pinMode(RIGHT_CONTROL_PWM_SIG, OUTPUT);
  pinMode(LEFT_CONTROL_EN, OUTPUT);
  pinMode(RIGHT_CONTROL_EN, OUTPUT);

  Serial.print("Motor1 - \t");
  Serial.print(dir1);
  Serial.print("\t");
  Serial.println(speed1);

  Serial.print("Motor2 - \t");
  Serial.print(dir2);
  Serial.print("\t");
  Serial.println(speed2);

  testMotor.brakeCoast();
}

// the loop function runs over and over again forever
void loop() {
  if (Serial.available() > 0){
    char input = Serial.read();
    Serial.println(input);
  }

  // digitalWrite(LED_BUILTIN,HIGH);
  // delay(1000);
  // digitalWrite(LED_BUILTIN, LOW);
  // delay(1000);
}

void motorRamp(){
  Serial.println("======RAMPING UP======");
  for (int i = 0; i < 200; i++) {
    testMotor.driveRight(i);
    Serial.println(i);
    delay(1500);
  }

  Serial.println("======RAMPING DOWN======");

  for (int i = 200; i > 0; i--) {
    testMotor.driveRight(i);
    Serial.println(i);
    delay(1500);
  }

  testMotor.brakeCoast();

  Serial.println("======FINISHED TEST======");
}