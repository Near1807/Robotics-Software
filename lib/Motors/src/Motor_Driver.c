#include "Motor_Driver.h"
#include "Arduino.h"

#define M1A 26
#define M1B 27
#define M2A 16
#define M2B 17

Motor_Data motorData;


/*
@brief Initializes the motor data structure with the specified initial and target speeds, and sets the motor state to Init.
Also defines the motor control pins for two motors (M1A, M1B, M2A, M2B).

@param motorData Pointer to the Motor_Data structure for the motor.
@note The motor control pins are defined as constants within this function. Adjust the pin numbers as needed for your specific hardware setup.
*/
void Motor_Initialise(Motor_Data *motorData) {
    motorData->state = Init;
    motorData->currentSpeed = 0;
    motorData->targetSpeed = 0;

    pinMode(M1A, OUTPUT);
    pinMode(M1B, OUTPUT);
    pinMode(M2A, OUTPUT);
    pinMode(M2B, OUTPUT);
}

/*
@brief Converts a speed value to a PWM value.

@param speed The speed value to convert.
@return The corresponding PWM value.
@note The speed ratio is calculated based on the maximum and minimum speed values, which must be modified with the min and max values the robot can reach, and the PWM value is scaled accordingly.
*/
int Speed_to_pwm(int speed) {
    int maxSpeed = 100;
    int minSpeed = 0;
    int ratio = 255 / (maxSpeed - minSpeed);
    int pmwValue = speed * ratio;
    return pmwValue;
}

/*
@brief Sets the target speed for the motor.

@param motorData Pointer to the Motor_Data structure for the motor.
@param speed The desired target speed for the motor.
*/
void Motor_SetSpeed(Motor_Data *motorData, int speed) {
    motorData->targetSpeed = Speed_to_pwm(speed);
}


/*
@brief Performs the motor control tasks based on the current state of the motor.

@param motorData Pointer to the Motor_Data structure for the motor.
@param M1A The pin number for Motor 1 control A.
@param M1B The pin number for Motor 1 control B.
@param M2A The pin number for Motor 2 control A.
@param M2B The pin number for Motor 2 control B.
*/
void Motor_Task(Motor_Data *motorData) {
    switch (motorData->state) {
        case Init:
            // Perform initialization tasks
            motorData->state = Idle;
            break;
        case Idle:
            // Check if we need to start moving
            if (motorData->targetSpeed == 0) {
                motorData->state = Breaking;
            }
            else if (motorData->currentSpeed != motorData->targetSpeed) {
                motorData->state = Moving;
            }
            break;
        case Moving:
            if (motorData->targetSpeed > 0) {
                motorData->state = Moving_Forward;
            }
            else if (motorData->targetSpeed < 0) {
                motorData->state = Moving_Backward;
            }
            motorData->state = Idle;
            break;

        case Moving_Forward:
            analogWrite(M1A, motorData->targetSpeed);
            analogWrite(M1B, 0);

            analogWrite(M2A, motorData->targetSpeed);
            analogWrite(M2B, 0);
            motorData->targetSpeed = motorData->currentSpeed;
            motorData->state = Idle;
            break;
        case Moving_Backward:
            analogWrite(M1A, 0);
            analogWrite(M1B, motorData->targetSpeed);

            analogWrite(M2A, 0);
            analogWrite(M2B, motorData->targetSpeed);
            motorData->targetSpeed = motorData->currentSpeed;
            motorData->state = Idle;
            break;    

            
        case Breaking:
            analogWrite(M1A, 0);
            analogWrite(M1B, 0);

            analogWrite(M2A, 0);
            analogWrite(M2B, 0);
            motorData->targetSpeed = motorData->currentSpeed;
            motorData->state = Idle;
            break;
            
    }
}