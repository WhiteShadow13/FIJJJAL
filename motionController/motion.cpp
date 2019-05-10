using namespace std;

#include "motion.h"

/*PID array ( 2 pids , 1 for each axis (x,y)) */
PID pids[2];

#define PID_ROLL_X 0
#define PID_PITCH_Y 1
//#define PID_YAW_RATE 3


/*Constructor*/
MotionController:: MotionController (Motor upRightMotor , Motor upLeftMotor
                        ,Motor downRightMotor , Motor downLeftMotor , Gyro gyro,
                        Ultrasound ultrasound[4])          
                        {
                            this->upRightMotor = upRightMotor;
                            this->upLeftMotor = upLeftMotor ;
                            this->downRightMotor = downRightMotor ;
                            this->downLeftMotor = downLeftMotor ;
                            this->gyro = gyro ;
                            this->ultrasound = ultrasound;
                        }


/* PID configuration */
void MotionController :: setupPIDS(){

    /* setting pids on different axis */

    //Axis 1
    // min and max bounds
    //setting kp,ki,kd
    pids[PID_ROLL_X].setMinBound(1500);
    pids[PID_ROLL_X].setMaxBound(1900);
    pids[PID_ROLL_X].setKp(0.02);
    pids[PID_ROLL_X].setKi(0.01);
    pids[PID_ROLL_X].setKd(0.005);


    //axis 2
    pids[PID_PITCH_Y].setMinBound(1500);
    pids[PID_PITCH_Y].setMaxBound(1900);
    pids[PID_PITCH_Y].setKp(0.02);
    pids[PID_PITCH_Y].setKi(0.01);
    pids[PID_PITCH_Y].setKd(0.005);

};

/* setup Motors */
void MotionController :: setupMotors( int pin1, int pin2 , int pin3, int pin4){
    
    //setting pins
    this->upRightMotor.setPin(pin1);
    this->upLeftMotor.setPin(pin2);
    this->downRightMotor.setPin(pin3);
    this->downLeftMotor.setPin(pin4);

    this->upRightMotor.initialize();
    this->upLeftMotor.initialize();
    this->downRightMotor.initialize();
    this->downLeftMotor.initialize();
   
};

/* get the gyroValue*/
XY MotionController :: getGyroValue(){
    
    XY gyroValue = this->gyro.readXY();

    return gyroValue;
};

/* get the distance from ultrasound sensor */
double MotionController :: getDistance(){

    double distance = this->ultrasound.getDistance();

    return distance;
}


void MotionController :: move(string direction , float p1 ,float input1 ,
                                 float p2,float input2, float p3 , float input3,float p4 ,float input4){
                                
                                //if forward 
                                if (direction == "forward") {
                                    //detect obstacle with front ultrasound sensor 
                                    double distance = getDistance();

                                    if (distance > 1000){ 
                                    
                                    //stabilized movevement
                                    this->upRightMotor.control(p1, input1); //lower
                                    this->upLeftMotor.control(p2, input2); //lower
                                    this->downRightMotor.control(p3, input3); // faster 
                                    this->downLeftMotor.control(p4 , input4); // faster

                                    }

                                    else {
                                        // distance to short so ==>change the direction
                                        // when distance is > 1000
                                        // recalculate path
                                        // movement
                                    }
                                    
                                    } 
                                if (direction == "backward"){
                                    this->upRightMotor.control(p1, input1);
                                    this->upLeftMotor.control(p2, input2);
                                    this->downRightMotor.control(p3, input3);
                                    this->downLeftMotor.control(p4 , input4);
                                }
                                };


void MotionController :: takeOFf(float p1 ,float input1 ,
                                 float p2,float input2, float p3 , float input3,float p4 ,float input4){
    this->upRightMotor.control(p1, input1); //increase
    this->upLeftMotor.control(p2, input2); // increase
    this->downRightMotor.control(p3, input3);//increase
    this->downLeftMotor.control(p4 , input4);// increase
};

void MotionController :: landing(float p1 ,float input1 ,
                                 float p2,float input2, float p3 , float input3,float p4 ,float input4){
    
    this->upRightMotor.control(p1, input1);//decrease
    this->upLeftMotor.control(p2, input2);//decrease
    this->downRightMotor.control(p3, input3);//decrease
    this->downLeftMotor.control(p4 , input4);//decrease
};

/* motion functions 

void MotionController :: ascend(float p1 ,float input1 ,
                                 float p2,float input2, float p3 , float input3,float p4 ,float input4){
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

*/


