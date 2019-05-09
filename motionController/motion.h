#ifndef H_MOTION
#define H_MOTION

#include "../pid/pid.h"
#include "../motor/motor.h"
#include "../gyro/gyro.h"
#include "../gyro/struct.h"

using namespace std;

class MotionController {

    public:
        MotionController();
        MotionController(Motor upRightMotor , Motor upLeftMotor
                        ,Motor downRightMotor , Motor downLeftMotor , Gyro gyro);

        void setupMotors(int pin1 , int pin2 , int pin3, int pin4 , PID pid1, PID pid2, PID pid3, PID pid4); 
        void setupPIDS(PID pid1, PID pid2, PID pid3 ,PID pid4){

        };


        void forward(float p1 ,float input1 ,
                                 float p2,float input2, float p3 , float input3,float p4 ,float input4);
        void turnLeft(float p1 ,float input1 ,
                                 float p2,float input2, float p3 , float input3,float p4 ,float input4);
        void turnRight(float p1 ,float input1 ,
                                 float p2,float input2, float p3 , float input3,float p4 ,float input4); 
        void backward(float p1 ,float input1 ,
                                 float p2,float input2, float p3 , float input3,float p4 ,float input4);

        void descend(float p1 ,float input1 ,
                                 float p2,float input2, float p3 , float input3,float p4 ,float input4);

        void ascend(float p1 ,float input1 ,
                                 float p2,float input2, float p3 , float input3,float p4 ,float input4);
        
    
    
        XY getGyroValue();

    
    private:

        Motor upRightMotor ;
        Motor upLeftMotor ;
        Motor downRightMotor ; 
        Motor downLeftMotor ;
        Gyro gyro ;
        
};

#endif