#ifndef H_GYRO
#define H_GYRO

#include "struct.h"

using namespace std;

class Gyro {
    public:
        Gyro();

        void initialise();
        XY readXY();
        
    private:
        int file;

        void i2cInitialise(char *bus, char address);
        int readAxis(char lsb_add, char msb_add);    
};

#endif