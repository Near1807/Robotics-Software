#include <Arduino.h>
#include "Motor_Driver.h"


void setup() {
    Motor_Initialise(&motorData);
}

void loop() {
    Motor_Task(&motorData);
    Motor_SetSpeed(&motorData, 50); // Set target speed to 50
    delay(1000); // Wait for 1 second
    Motor_SetSpeed(&motorData, 0); // Set target speed to 0
    delay(1000); // Wait for 1 second
    Motor_SetSpeed(&motorData, -50); // Set target speed to -50
    delay(1000); // Wait for 1 second
}