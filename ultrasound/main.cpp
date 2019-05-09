#include <iostream>
#include <pigpio.h>

#include "ultrasound.h"

using namespace std;

int main()
{
    while (gpioInitialise() < 0)
    {
      fprintf(stderr, "pigpio initialisation failed\n");
    }

    Ultrasound ultra1 = Ultrasound(16, 19);
    Ultrasound ultra2 = Ultrasound(23, 4);
    Ultrasound ultra3 = Ultrasound(13, 12);
    Ultrasound ultra4 = Ultrasound(6, 5);

    while(1){
		    gpioSleep(PI_TIME_RELATIVE, 0, 500000);
        cout << "Distance1 is " << ultra1.getDistance() << " cm." << endl;
        gpioSleep(PI_TIME_RELATIVE, 0, 500000);
        cout << "Distance2 is " << ultra2.getDistance() << " cm." << endl;  
    }
}