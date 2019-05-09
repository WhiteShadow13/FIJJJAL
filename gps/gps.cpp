#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "nmea.h"
#include "serial.h"
#include "gps.h"
#include "struct.h"

using namespace std;

//Constuctor, take nmea and serial object
Gps::Gps() {
    nmea = NMEA();
    serial = Serial();
}

//Init gps on serial port /dev/ttyAMA0(raspberry)
void Gps::gpsInit() {
    serial.serialInit("/dev/ttyAMA0");
}

//Get location 
void Gps::gpsLocation(loc_t *coord) {
    int status = 0;
    while(status != 1) {
        gpgga_t gpgga;
        gprmc_t gprmc;
        char buffer[256];

        //Get message on serial bus
        serial.serialRead(buffer, 256);
        //Parse message
        switch (nmea.getMessageType(buffer)) {
            case 1:
                nmea.parseGPGGA(buffer, &gpgga);

                gpsConvert(&(gpgga.latitude), gpgga.lat, &(gpgga.longitude), gpgga.lon);

                coord->latitude = gpgga.latitude;
                coord->longitude = gpgga.longitude;
                coord->altitude = gpgga.altitude;

                status |= 1;
                break;
            case 2:
                nmea.parseGPRMC(buffer, &gprmc);

                coord->speed = gprmc.speed;
                coord->course = gprmc.course;

                status |= 2;
                break;
        }
    }   
}

//Convert lat and lon to decimals (from deg)
void Gps::gpsConvert(double *latitude, char ns,  double *longitude, char we)
{
    double lat = (ns == 'N') ? *latitude : -1 * (*latitude);
    double lon = (we == 'E') ? *longitude : -1 * (*longitude);

    *latitude = gpsDegToDec(lat);
    *longitude = gpsDegToDec(lon);
}

double Gps::gpsDegToDec(double deg_point)
{
    double ddeg;
    double sec = modf(deg_point, &ddeg)*60;
    int deg = (int)(ddeg/100);
    int min = (int)(deg_point-(deg*100));

    double absdlat = round(deg * 1000000.);
    double absmlat = round(min * 1000000.);
    double absslat = round(sec * 1000000.);

    return round(absdlat + (absmlat/60) + (absslat/3600)) /1000000;
}

void Gps::gpsClose() {
    serial.serialClose();
}