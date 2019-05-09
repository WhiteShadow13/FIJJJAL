#ifndef H_MOTION
#define H_MOTION

#include "../pid/pid.h"
#include "../motor/motor.h"
#include "../gyro/gyro.h"

using namespace std;

class MotionController {
    public:
        MotionController();
        MotionController(Motor upRightMotor , Motor upLeftMotor
                        ,Motor downRightMotor , Motor downLeftMotor , Gyro gyro);

        void forward();
        void turnLeft();
        void turnRight(); 
        void backward();
        void setupMotors(int pin1, int pin2, int pin3 , int pin4);
     
    private:

        Motor upRightMotor ;
        Motor upLeftMotor ;
        Motor downRightMotor ; 
        Motor downLeftMotor ;
        Gyro gyro ;
        
};

#endif