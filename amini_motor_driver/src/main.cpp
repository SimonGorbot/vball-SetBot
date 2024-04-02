#include <Arduino.h>
#include "string.h"
#include "Wire.h"
#include "BTS7960.h"

//Pin Constant Definitions for Motor 1
const int LEFT_CONTROL_PWM_SIG = 11;
const int RIGHT_CONTROL_PWM_SIG = 10;
const int RIGHT_CONTROL_EN = 3;
const int LEFT_CONTROL_EN = 5;

//variable definitions for UART Comms. with Pi
const byte numChars = 32;
char receivedChars[numChars];
String receivedString;
boolean newCommand = false;

//Motor Object Construct
BTS7960 motorBlack (RIGHT_CONTROL_PWM_SIG, RIGHT_CONTROL_EN, LEFT_CONTROL_PWM_SIG, LEFT_CONTROL_EN); //BLACK MOTOR
BTS7960 motorWhite (RIGHT_CONTROL_PWM_SIG, RIGHT_CONTROL_EN, LEFT_CONTROL_PWM_SIG, LEFT_CONTROL_EN); //WHITE MOTOR
#define MOTOR_BLACK 1  //consider motor 1 
#define MOTOR_WHITE 2  //consider motor 2

//Function prototypes
void motorRamp();
void receiveMotorCommand();
void showMotorCommand();
void parseMotorCommmand(String commandStr, BTS7960 &motorDriver, int motor);
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

//Debug Stuff
String test_motor_command_str = "\t10101001000000010000\n"; 


void setup() {
  //initialize serial
  Serial.begin(9600);

  //set up PWM and EN output pins for motor drivers
  pinMode(LEFT_CONTROL_PWM_SIG, OUTPUT);
  pinMode(RIGHT_CONTROL_PWM_SIG, OUTPUT);
  pinMode(LEFT_CONTROL_EN, OUTPUT);
  pinMode(RIGHT_CONTROL_EN, OUTPUT);

  //set motors to coast
  motorWhite.brakeCoast();
  // motor1.motorCommandRamp(0b10, 50);
  // delay(5000);
  // motor1.brakeCoast();
}

// the loop function runs over and over again forever
void loop() {
  receiveMotorCommand();
  if (newCommand == true){
    parseMotorCommmand(receivedChars, motorWhite, MOTOR_WHITE);
    motorWhite.motorCommandRamp(motorWhite.cmdDir, motorWhite.cmdSpeed);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  } 
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

void receiveMotorCommand() {
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
}

void showMotorCommand() {
    if (newCommand == true) {
        Serial.print("This just in ... ");
        Serial.println(receivedChars);
        newCommand = false;
    }
}

void parseMotorCommmand(String commandStr, BTS7960 &motorDriver, int motor) {
  uint32_t mot_com_bint = strtol(commandStr.c_str(), NULL, 2); //convert binary command string into binary int

  if (motor == 1){
    motorDriver.cmdDir = mot_com_bint >> (20-2); //isolates bits 19 and 18 for motor 1 direction
    motorDriver.cmdSpeed = mot_com_bint >> 8 & 0b11111111; //isolates bits 15 to 7 for motor 1 speed
  }

  else if (motor == 2){
    motorDriver.cmdDir = mot_com_bint >> (20-4) & 0b11; //isolates bits 17 and 16 for motor 2 direction
    motorDriver.cmdSpeed = mot_com_bint & 0b11111111; //isolates bits 7 to 0 for motor 2 speed
  }

  newCommand = false;

  // Serial.println(motorDriver.cmdDir);
  // Serial.println(motorDriver.cmdSpeed);
}