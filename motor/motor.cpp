#include <stdio.h>
#include <pigpio.h>

#include "motor.h"

using namespace std;

//Constuctor
Motor::Motor(int pin, PID pid) {
    this->pin = pin; 
    this->pid = pid;
}

//Motor Initilise 
void Motor::initialize() {
    gpioSetMode(this->pin, PI_OUTPUT);
    gpioSleep(PI_TIME_RELATIVE, 0.5, 0);
    gpioWrite(this->pin, 1);
}

//Motor stop
void Motor::stop() {
    gpioWrite(this->pin, 0);
    gpioTerminate();
}

//Control motor with PID
void Motor::control(float setPoint, float input) {
    //Get output from PID
    float ctrl = this->pid.calcPID(setPoint, input);
    //Set PWM with output PID
    this->setPWM(ctrl);
}

//Set PWM
void Motor::setPWM(float value) {
    gpioServo(this->pin, value);
}

void Motor::setPin(float value) {
    this->pin = value;
}

void Motor::setPid(PID value) {
    this->pid = value;
}

}