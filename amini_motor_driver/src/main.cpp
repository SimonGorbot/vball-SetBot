#include <Arduino.h>
#include "string.h"
#include "Wire.h"
#include "BTS7960.h"

const int LEFT_CONTROL_PWM_SIG = 5;
const int RIGHT_CONTROL_PWM_SIG = 3;
const int RIGHT_CONTROL_EN = 12;
const int LEFT_CONTROL_EN = 10;

const byte numChars = 32;
char receivedChars[numChars];
String receivedString;
boolean newCommand = false;

BTS7960 testMotorL (RIGHT_CONTROL_PWM_SIG, RIGHT_CONTROL_EN, LEFT_CONTROL_PWM_SIG, LEFT_CONTROL_EN);
BTS7960 testMotorR (1, 2, 6, 8);

String mot_com_str = "\t10101000000010000000\n";

void motorRamp();
bool receiveMotorCommand();
bool showMotorCommand();
void parseMotorCommmand(String Command, BTS7960 &leftMotorDriver, BTS7960 &rightMotorDriver);
void ledBlink(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(200);
}

void setup() {
  Serial.begin(9600);

  //set up PWM output pins for motor drivers
  pinMode(LEFT_CONTROL_PWM_SIG, OUTPUT);
  pinMode(RIGHT_CONTROL_PWM_SIG, OUTPUT);
  pinMode(LEFT_CONTROL_EN, OUTPUT);
  pinMode(RIGHT_CONTROL_EN, OUTPUT);

  testMotorL.brakeCoast();
}

// the loop function runs over and over again forever
void loop() {
  receiveMotorCommand();
  if (newCommand == true){
    parseMotorCommmand(receivedChars, testMotorL, testMotorR);
    if (testMotorL.cmdSpeed >= 200){
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
  showMotorCommand();
}

void motorRamp() {
  Serial.println("======RAMPING UP======");
  for (int i = 0; i < 200; i++) {
    //testMotor.driveRight(i);
    Serial.println(i);
    delay(1500);
  }

  Serial.println("======RAMPING DOWN======");

  for (int i = 200; i > 0; i--) {
    //testMotor.driveRight(i);
    Serial.println(i);
    delay(1500);
  }

  //testMotor.brakeCoast();

  Serial.println("======FINISHED TEST======");
}

bool receiveMotorCommand() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '\t';
  char endMarker = '\n';
  char currentChar;

  while (Serial.available() > 0 && newCommand == false) {
      currentChar = Serial.read();

      if (currentChar == startMarker){
        recvInProgress = true;
      }

      else if (recvInProgress == true) {
          if (currentChar != endMarker) {
              receivedChars[ndx] = currentChar;
              ndx++;
              if (ndx >= numChars) {
                  ndx = numChars - 1;
              }
              // digitalWrite(LED_BUILTIN, HIGH);
              // delay(200);
              // digitalWrite(LED_BUILTIN, LOW);
              // delay(200);
          }
          else {
              receivedChars[ndx] = '\0'; // terminate the string
              recvInProgress = false;    // set that we are done receiving
              ndx = 0;                   // reset char array tracker
              newCommand = true;         // set that we have a new complete command
          }
      }
  }

  return newCommand;
}

bool showMotorCommand() {
    if (newCommand == true) {
        Serial.print("This just in ... ");
        Serial.println(receivedChars);
        //newCommand = false;
        return true;
    }

    else{
      return false;
    }
}

void parseMotorCommmand(String commandStr, BTS7960 &leftMotorDriver, BTS7960 &rightMotorDriver) {
  
  uint32_t mot_com_bint = strtol(commandStr.c_str(), NULL, 2); //convert binary command string into binary int

  leftMotorDriver.cmdDir = mot_com_bint >> (20-2); //isolates bits 19 and 18 for motor 1 direction
  leftMotorDriver.cmdSpeed = mot_com_bint >> 8 & 0b11111111; //isolates bits 15 to 7 for motor 1 speed
  rightMotorDriver.cmdDir = mot_com_bint >> (20-4) & 0b11; //isolates bits 17 and 16 for motor 2 direction
  rightMotorDriver.cmdSpeed = mot_com_bint & 0b11111111; //isolates bits 7 to 0 for motor 2 speed

  newCommand = false;

  // Serial.println(leftMotorDriver.cmdDir);
  // Serial.println(leftMotorDriver.cmdSpeed);
  // Serial.println(rightMotorDriver.cmdDir);
  // Serial.println(rightMotorDriver.cmdSpeed);

}