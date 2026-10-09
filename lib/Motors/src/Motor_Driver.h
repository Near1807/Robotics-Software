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


extern Motor_Data motorData;



void Motor_Initialise(Motor_Data *motorData);
void Motor_Task(Motor_Data *motorData);
int Speed_to_pwm(int speed);
void Motor_SetSpeed(Motor_Data *motorData, int speed);


