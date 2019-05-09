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
