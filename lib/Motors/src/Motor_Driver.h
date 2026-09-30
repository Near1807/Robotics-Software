typedef enum {
    Init = 0,
    Idle = 1,
    Moving = 2,
    Moving_Forward = 3,
    Moving_Backward = 4,
    Breaking = 5,
} Motor_State;

typedef struct {
    Motor_State state;
    int currentSpeed;
    int targetSpeed;
} Motor_Data;


extern Motor_Data motor1Data;
extern Motor_Data motor2Data;


void Motor_Initialise(Motor_Data *motorData, int initialSpeed, int targetSpeed);
void Motor_Task(Motor_Data *motorData);
void Motor_ChangeSpeed(Motor_Data *motorData);


