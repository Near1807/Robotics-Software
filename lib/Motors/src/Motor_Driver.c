#include "Motor_Driver.h"

Motor_Data motor1Data;
Motor_Data motor2Data;

void Motor_Initialise(Motor_Data *motorData, int initialSpeed, int targetSpeed) {
    motorData->state = Init;
    motorData->currentSpeed = initialSpeed;
    motorData->targetSpeed = targetSpeed;

    const int M1A = 26;
    const int M1B = 27;
    const int M2A = 16;
    const int M2B = 17;
}


void Motor_Task(Motor_Data *motorData, int M1A, int M1B, int M2A, int M2B) {
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