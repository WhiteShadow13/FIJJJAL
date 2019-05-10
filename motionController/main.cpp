using namespace std;

#include "motion.h"
#include "gyro.h"
#include "gps.h"


/* 4 motors */
Motor motorUpRight;
Motor motorUpLeft;
Motor motorDownRight;
Motor motorDownLeft;

/* gyro */
Gyro gyro;

/* gps */
Gps gps;

/*ultrasound array */

Ultrasound ultrasounds[4] ; 

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup(){
    
    //initialisation
    gps.gpsInit(); 
    gyro.initialise(); 
    

    //motion controller 
    MotionController motionController = MotionController(motorUpLeft, motorUpRight,motorDownLeft,motorDownRight, gyro); 

    //setup PIDS
    motionController.setupPIDS();

    // setup motors 
    motionController.setupMotors(18,22,17,23); // pins for the motors to be accord to the wireing 


}