using namespace std;

#include "motion.h"


/*Constructor*/
MotionController:: MotionController (Motor upRightMotor , Motor upLeftMotor
                        ,Motor downRightMotor , Motor downLeftMotor , Gyro gyro)
                        {
                            this->upRightMotor = upRightMotor;
                            this->upLeftMotor = upLeftMotor ;
                            this->downRightMotor = downRightMotor ;
                            this->downLeftMotor = downLeftMotor ;
                            this->gyro = gyro ;
                        }

/* PID configuration */

/*PID array ( 4 pids , two for each axis (x,y)) */
PID pids[4];
#define PID_PITCH_X 0
#define PID_ROLL_X 1
#define PID_PITCH_Y 2
#define PID_ROLL_Y 3
//#define PID_YAW_RATE 4
//#define PID_YAW_STAB 5


Motor motors[4];

#define MotorUL 0
#define MotorUR 1
#define MotorDL 2
#define MotorDR 3

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================


void MotionController :: setupPIDS(PID pid1, PID pid2, PID pid3 ,PID pid4){

    /* setting pids on different axis */

    // min and max bound
    pid1.setMinBound(1500);
    pid1.setMaxBound(1900);
    
    //setting kp,ki,kd
    pid1.setKp(0.02);
    pid1.setKp(0.02);
    pid1.setKi(0.01);
    pid1.setKd(0.005);

    
    pid2.setMinBound(1500);
    pid2.setMaxBound(1900);
    pid2.setKp(0.02);
    pid2.setKi(0.01);
    pid2.setKd(0.005);

    pid3.setMinBound(1500);
    pid3.setMaxBound(1900);
    pid3.setKp(0.02);
    pid3.setKi(0.01);
    pid3.setKd(0.005);


    pid4.setMinBound(1500);
    pid4.setMaxBound(1900);
    pid4.setKp(0.02);
    pid4.setKp(0.01);
    pid4.setKp(0.005);

};




/*  Motors configuration */
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
    this->upRightMotor.control(p1, input1);
    this->upLeftMotor.control(p2, input2);
    this->downRightMotor.control(p3, input3);
    this->downLeftMotor.control(p4 , input4);
};
/* get the gyroValue*/
XY MotionController :: getGyroValue(){
    
    XY gyroValue = this->gyro.readXY();

    return gyroValue;
};




/* motion functions */
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




