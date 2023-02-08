
#define pinMotorDir_A 2
#define pinMotorPWM_A 3
#define pinMotorDir_B 8
#define pinMotorPWM_B 9

void init_motorAB();

void motorA_setDir(int dir);

void motorA_setPWM(int pwm);

void motorB_setDir(int dir);

void motorB_setPWM(int pwm);

void cmd_motors(int pwmD, int pwmG);

void cmd_robot(int lineaire, int angulaire);