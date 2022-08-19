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
* @brief control motor class for project gekko
* @date 24 July 2021
* @details DCモータ(GM25-370) control to adjust target motor speed
* @details output PWM to the motor from PID calculations
* @details Microcomputer:ESP32, Motor Driver:TB6643KQ
*/

/*!
* @class Motor
* @brief Calculate the PWM from PID control to adust the motor speed
*/
class Motor{
  public:
    int PinEncoderA, PinEncoderB; /** @brief Pin number connected to the encoder*/
    int PinDriverA, PinDriverB; /** @brief Pin number connected to the motor driver*/
    int ChannelA, ChannelB; /** @brief low,high channel to output PWM*/
    int DebugMode; /** @brief debugmode (0:OFF,1:ON)*/
    pcnt_unit_t PcntUnit;
    boolean reverse; /** @brief motor reverse status(1: reverse)*/
    float Kp, Kd, Ki, K; /** @brief gain for PID*/
  private:
    float Velocity; /** @brief Rotation speec*/
    float VelocityTarget; /** @brief Rotation speec on target*/
    float PWM; /** @brief Pulse width modulation*/
    float P_Old, I_Old, Velocity_Old; /** @brief recorder*/
  
  public:
    /** default constructor*/
    Motor(){}
    /** 
     * constructor
     * @param PinEncoderA Pin number connected to encoderA
     * @param PinEncoderB  Pin number connected to encoderB
     * @param PinDriverA  Pin number connected to  driverA
     * @param PinDriverB  Pin number connected to  driverB
     * @param ChannelA low or high to output PWM
     * @param ChannelB low or high to output PWM
     * @param Debugmode  0:OFF,1:ON
     * @param PcntUnit
     * @param reverse 0:normal, 1:reverse
     * @param Kp gain for P
     * @param Ki gain for I
     * @param Kd gain for D
     * @param K weight for weighted average
    */
    Motor(int PinEncoderA, int PinEncoderB, int PinDriverA, int PinDriverB, int ChannelA, int ChannelB, int DebugMode, pcnt_unit_t PcntUnit, boolean reverse, float Kp, float Ki, float Kd, float K)
    {
        this->PinEncoderA = PinEncoderA;
        this->PinEncoderB = PinEncoderB;
        this->PinDriverA = PinDriverA;
        this->PinDriverB = PinDriverB;
        this->ChannelA = ChannelA;
        this->ChannelB = ChannelB;
        this->DebugMode = DebugMode;
        this->PcntUnit = PcntUnit;
        this->reverse = reverse;
        this->Kp = Kp;
        this->Ki = Ki;
        this->Kd = Kd;
        this->K = K;
        this->Velocity = 0.0f;
        this->VelocityTarget = 0.0f;
        this->PWM = 0.0f;
        this->P_Old = 0.0f;
        this->I_Old = 0.0f;
        this->Velocity_Old = 0.0f;
    }
    
    /**
     * Set to input, output
     * @details set the destination for obtaining the motor speed and for PWM output, preparing to vonvert the analog signal of the motor speed to digital 
    */
    void SetupMotor();
    /**
     * PID control
     * @brief Calculate the PWM from PID control to adust the motor speed
     * @details adjust the motor speed by calculating the PWM to be target volocity for the current motor speed 
    */
    void DriveMotor();
    
  
  private:
    /**
     * Get Volocity(rpm)
     * @details Calculate motor speed from encoder output  
    */
    void GetVelocity();
    /**
     * Get target Volocity(rpm)
     * @details set target velocity for verification  
    */
    void GetTargetVelocity();
    /**
     * recode current P,I,Velocity valus as old
     * @details update P_Old,I_Old,Velocity_Old
    */
    void Update(float P, float I);
};
