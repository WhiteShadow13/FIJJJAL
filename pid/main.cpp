#include <iostream>
#include <fstream>

using namespace std;

#include "pid.h"

int main() {
    PID pid = PID();
    float value = 25.0;
    float setPoint = 0.0;

    ofstream fichier("./log.txt", ios::out);

    if(fichier) { 
        while (value >= 0.01 || value <= -0.01) {
            float pidOutput = pid.calcPID(setPoint, value);
            
            fichier << "error:" << setPoint-value << "; Action:" << pidOutput << endl;
            value -= 0.5;
        }

        fichier.close();
    }
    else {
        cout << "Error open file: log.txt"<< endl;
    }

    return 0;
}

