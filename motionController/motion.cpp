using namespace std;

# include "motion.h"

MotionController:: MotionController (Motor upRightMotor , Motor upLeftMotor
                        ,Motor downRightMotor , Motor downLeftMotor , Gyro gyro)
                        {
                            this->upRightMotor = upRightMotor;
                            this->upLeftMotor = upLeftMotor ;
                            this->downRightMotor = downRightMotor ;
                            this->downLeftMotor = downLeftMotor ;

                            this-> gyro = gyro ;
                        }
void MotionController :: setupMotors( int pin1, int pin2 , int pin3, int pin4
 ,PID pid1, PID pid2, PID pid3, PID pid4){
    //setting pins
    this->upRightMotor.setPin(pin1);
    this->upLeftMotor.setPin(pin2);
    this->downRightMotor.setPin(pin3);
    this->downLeftMotor.setPin(pin4);

    //setting pids
    this->upRightMotor.setPid(pid1);
    this->upLeftMotor.setPid(pid2);
    this->downRightMotor.setPid(pid3);
    this->downLeftMotor.setPid(pid4);

    // initialize motors

    this->upRightMotor.initialize();
    this->upLeftMotor.initialize();
    this->downRightMotor.initialize();
    this->downLeftMotor.initialize();

};


void MotionController :: ascend(float p1 ,float input1 ,
                                 float p2,float input2, float p3 , float input3,float p4 ,float input4){
    this->gyro.readXY();
    this->upRightMotor.control(p1, input1);
    this->upLeftMotor.control(p2, input2);
    this->downRightMotor.control(p3, input3);
    this->downLeftMotor.control(p4 , input4);
};

void MotionController :: descend(float p1 ,float input1 ,
                                 float p2,float input2, float p3 , float input3,float p4 ,float input4){
    
    this->upRightMotor.control(p1, input1);
    this->upLeftMotor.control(p2, input2);
    this->downRightMotor.control(p3, input3);
    this->downLeftMotor.control(p4 , input4);
};


void MotionController :: forward(float p1 ,float input1 ,
                                 float p2,float input2, float p3 , float input3,float p4 ,float input4){
    
    this->upRightMotor.control(p1, input1);
    this->upLeftMotor.control(p2, input2);
    this->downRightMotor.control(p3, input3);
    this->downLeftMotor.control(p4 , input4);
};

void MotionController :: turnLeft(float p1 ,float input1 ,
                                 float p2,float input2, float p3 , float input3,float p4 ,float input4){
    
    this->upRightMotor.control(p1, input1);
    this->upLeftMotor.control(p2, input2);
    this->downRightMotor.control(p3, input3);
    this->downLeftMotor.control(p4 , input4);

};

void MotionController ::turnRight(float p1 ,float input1 ,
                                 float p2,float input2, float p3 , float input3,float p4 ,float input4){
    this->upRightMotor.control(p1, input1);
    this->upLeftMotor.control(p2, input2);
    this->downRightMotor.control(p3, input3);
    this->downLeftMotor.control(p4 , input4);

}; 

void MotionController ::backward(float p1 ,float input1 ,
                                 float p2,float input2, float p3 , float input3,float p4 ,float input4){
    this->upRightMotor.control(p1, input1);
    this->upLeftMotor.control(p2, input2);
    this->downRightMotor.control(p3, input3);
    this->downLeftMotor.control(p4 , input4);

};
