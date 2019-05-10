#include <iostream>

#include "gyro.h"
#include "struct.h"

using namespace std;

int main()
{
    Gyro gyro;

    gyro.initialise();
    while(1){
        XY xy;
        xy = gyro.readXY();
            
        printf("Rotation in X-Axis : %d \n", xy.x);
	    printf("Rotation in Y-Axis : %d \n", xy.y);
    }
}