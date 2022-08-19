/**file:///home/masashi/gekko-software-simple/src/main.cpp

* @file MotorDrive.ino
* @brief control motor for project gekko
* @author Yuta nakamura, Masashi Mishima
* @date 11 July 2021
* @details construct class Motor & initialization & call PID calculation to modulate motors
*/
#include "motor.hpp"

Motor motor1; 
/**
     * setup
     * @brief construct , set parameter for PID , map pin configuration
*/
void setup() {
  Serial.begin(115200);
  motor1 = Motor(motor1_PinEncoderA,motor1_PinEncoderB,motor1_PinDriverA,motor1_PinDriverB,motor1_ChannelA,motor1_ChannelB,motor1_DebugMode,motor1_PcntUnit,motor1_reverse,motor1_Kp,motor1_Ki,motor1_Kd,motor1_K);
  
  motor1.SetupMotor(); 
}
/**
     * setup
     * @brief call PID calculation
*/
void loop() {
  float TimeLoopStart = millis();
  
  motor1.DriveMotor();
    
  float TimeLoopEnd = millis();
  delay(DT - (TimeLoopEnd - TimeLoopStart)); //time control
}
