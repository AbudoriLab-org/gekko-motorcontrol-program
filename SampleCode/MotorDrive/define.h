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
* @file motor.h
* @author Masashi Mishima
* @brief Definition parameter control motor for project gekko
* @date 24 July 2021
*/

/** sampling rate[ms] */
#define DT 10 


/* GM25-370 Reduction ratio */
float GEAR_RATIO = 21.f;
/** Encoder Resolution */
float ENCODER_RESOLUTION = 44.f; 
/** set target speed rotation for test (mode:1)*/
boolean setVelocity = 1; // テスト用の回転数をセット

/**
 * 
 * @detail Define parameter for motor1
 */
/** */
/**Pin number of encoder A-terminal */
int motor1_PinEncoderA = 18;
/**Pin number of encoder B-terminal*/
int motor1_PinEncoderB = 19; 
/**Pin number of motorDirver A-terminal */
int motor1_PinDriverA = 5;
/**Pin number of motorDriver B-terminal */
int motor1_PinDriverB = 23;
/**set ChannelA for output PWM */
int motor1_ChannelA = 0; 
/**set ChannelB for output PWM */
int motor1_ChannelB = 1;  //PWMを出力するチャンネル
int motor1_DebugMode = 0; //デバックモード（1がON）
pcnt_unit_t motor1_PcntUnit = PCNT_UNIT_2;
/**set reverse motor(0: normal,1:reverse) */
boolean motor1_reverse = 1;
/**P-gain */
float motor1_Kp = 1.9f;
/**D-gain */
float motor1_Ki = 1.26f;
/**D-gain */
float motor1_Kd = 0.0f;
/**cutoff constant for low-pass fileter */
float motor1_K = 0.1f;
