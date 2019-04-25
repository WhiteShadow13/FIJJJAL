#include <stdio.h>
#include <pigpio.h>

#include "motor.h"

using namespace std;

Motor::Motor(int pin) {
    this->pin = pin; 
}

void Motor::initialize() {
    gpioSetMode(this->pin, PI_OUTPUT);
}

void Motor::start() {
    gpioWrite(this->pin, 1);
}

void Motor::stop() {
    gpioWrite(this->pin, 0);
    gpioTerminate();
}

void Motor::setPWM(int value) {
    gpioServo(pin, value);
}