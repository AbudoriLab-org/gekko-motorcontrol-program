// Copyright 2021 Abudori Lab.
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
/**
* @file motor.hpp
* @author Masashi Mishima
* @brief control motor for project gekko
* @version 0.1
* @date 2021-7-24
* @details DC motor(GM25-370) control to adjust target motor speed
* @details output PWM to the motor from PID calculations
* @details Microcomputer:ESP32, Motor Driver:TB6643KQ
*
* @copyright Copyright (c) 2021 Abudori Lab.
*
*/
#include "qei.hpp" // counter function of ESP32
#include "motor.h"
#include "define.h"

/**
 * @brief Set PIN Configuration
 *
 */
void Motor::SetupMotor(){
  /** Frequency of PWM [Hz] */
  int LedcBaseFreq = 490;
  /** Range of PWM (8bit:0〜255、10bit:0〜1023) */
  int LedcTimerBit = 8;

  /**  */
  pinMode(PinEncoderA, INPUT_PULLUP); 
  pinMode(PinEncoderB, INPUT_PULLUP);
  pinMode(PinDriverA, OUTPUT); 
  pinMode(PinDriverB, OUTPUT);
  ledcSetup(ChannelA, LedcBaseFreq, LedcTimerBit); 
  ledcSetup(ChannelB, LedcBaseFreq, LedcTimerBit);
  ledcAttachPin(PinDriverA, ChannelA); 
  ledcAttachPin(PinDriverB, ChannelB);
  qei_setup_x4(PcntUnit, PinEncoderA, PinEncoderB); 
}

/**
 * @brief motor control 
 *
 * @param PWM_MAX
 * @param PWM_MIN
 * @param P
 * @param I
 * @param D
 */
void Motor::DriveMotor(){
  const int PWM_MAX = 256, PWM_MIN = 0; 
  float P, I, D; 

  /**  Get motor speed of rotation*/
  this->GetVelocity();

  if(setVelocity == 1){
    this->GetTargetVelocity();  
  }else{
    this->VelocityTarget = 100;
  }

  /** calculate factor of P,I,D*/
  P = VelocityTarget - Velocity; 
  I = I_Old + P; 
  D = P - P_Old; 

  /** calculate PWM form PID calculation*/
  //PWM = Kp * P;
  PWM = Kp * P + Ki * I; 
  //PWM = Kp * P + Ki * I + Kd * D; 
  //PWM = Kp * P + Ki * I + + Kd * D + Kf * F; 

  /** output PWM to motor driver*/
  if (PWM >= 0) {        
    if (PWM > PWM_MAX) PWM = PWM_MAX; //If PWM exceed PWM_MAX then set to PWM_MAX
    ledcWrite(ChannelA, int(PWM));  
    ledcWrite(ChannelB, PWM_MIN);
  } else {
    PWM *= -1;
    if (PWM > PWM_MAX) PWM = PWM_MAX; 
    ledcWrite(ChannelA, PWM_MIN);
    ledcWrite(ChannelB, int(PWM));
  }
  
  /** Update P,I value*/
  this->Update(P,I);
  
  if(DebugMode == 1){
  }
  //Serial.print("Velocity: ");
  Serial.println(Velocity);
  //Serial.print(" VelocityTarget: ");
  Serial.print(",");
  Serial.println(VelocityTarget);
  //Serial.print(" PWM: ");
  //Serial.println(PWM);
}

/**
 * @brief speed of rotation converter
 *
 * @param CountEncoder
 * @param EncoderVariation
 */
void Motor::GetVelocity(){
  int16_t CountEncoder = 0;
  /** Get pulse count*/
  pcnt_get_counter_value(PcntUnit, &CountEncoder); 
  int EncoderVariation = CountEncoder;

  /** convert to speed of rotation */
  Velocity = (EncoderVariation / (GEAR_RATIO * ENCODER_RESOLUTION)) * ((1000*60) / DT);
  Velocity = K * Velocity_Old + (1.f - K) * Velocity;
  
  /** overflow processing*/
  pcnt_counter_clear(PcntUnit); 
  }

//目標角速度を算出する関数
void Motor::GetTargetVelocity(){ // 3秒おきに回転数を変える
 
  int vel_mode;
  vel_mode = (millis() / 6000) % 3;
  switch(vel_mode){
    case 0:
      VelocityTarget = 80;
      break;
    case 1:
      VelocityTarget = 120;
      break;
    case 2:
      VelocityTarget = 160;
      break;
    default:
      VelocityTarget=80;
      break;  
  }
   if(reverse == 1){ // 逆転設定を反映
    VelocityTarget = -VelocityTarget;
  }
}

/**
 * @brief parameter update
 *
 */
void Motor::Update(float P, float I){
    this->Velocity_Old = this->Velocity;
    this->P_Old = P;
    this->I_Old = I;

}
