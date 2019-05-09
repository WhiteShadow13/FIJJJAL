#ifndef H_MOTOR
#define H_MOTOR

#include "../pid/pid.h"

using namespace std;

class Motor {
    public:

        Motor()
        Motor(int pin, PID pid);

        void initialize();
        void stop();

        void control(float setPoint, float input);
        void setPin(int pin);
        
    private:
        int pin;
        PID pid;

        void setPWM(float value);
};

#endif