/********** TCC-Motor class **********/
/* This class regroup all the functions needed to control the motors.
 */

#ifndef MOTOR_H
#define MOTOR_H

class TCC_Motor {
    private:
        int pinMotorDir_A = 2;
        int pinMotorPWM_A = 3;
        int pinMotorDir_B = 8;
        int pinMotorPWM_B = 9;

    public:
        long last_millis;

        TCC_Motor();
        void setup();
        void motorA_setDir(bool dir);
        void motorA_setPWM(int pwm);
        void motorB_setDir(bool dir);
        void motorB_setPWM(int pwm);
        void cmd_motors(int pwmD, int pwmG);
        void cmd_robot(int lineaire, int angulaire);
        
        // To delete if not used
        //bool delayMove(int delaytime);


};

#endif

