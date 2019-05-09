# GPS
The GPS code is the module to mesure the GPS coordonate. This module is based on [Adafruit Ultimate GPS](https://www.adafruit.com/product/746). </br>
It communicate with the raspberry on a serial bus.  </br>

**Example in main.cpp**

## Why we need this ?
The GPS allows to know where is the drone. With this coordonate and a end point, we create a path to go to there destination. 

## NMEA coordonates
The [NMEA coordonates](https://en.wikipedia.org/wiki/NMEA_0183) is a standar specification format for the gps data. 

## Code and functions
1. ***Serial***
* `serialInit(char *bus)` Init serial communication 
* `serialConfig()` Config serial communication
* `serialPrint(const char *line, int len)` Write data on serial bus
* `serialRead(char *buffer, int len)` Read data on serial bus
* `serialClose()` Close comm

2. ***NMEA***
* `parseGPGGA(char *nmea, gpgga_t *loc)` parse nmea gpagga format
* `parseGPRMC(char *nmea, gprmc_t *loc)` parse nmea gparmc format

3. ***Gps***
* `gpsInit()` Init Gps on rasberry (for now hardcode on serial port "/dev/ttyAMA0")
* `gpsLocation(loc_t *coord)` Get coordonates location on serial bus and parse nmea format
* `gpsConvert(double *latitude, char ns,  double *longitude, char we)` Convert degrees cordonates on decimals coordonates

3. ***Struct***
All struct (gpgpa, gprmc and loc) are in **struct.h**


## Use and Output of main.cpp
```shell
$ g++ -o gps *.cpp
$ ./gps
```
You will see your data directly in console:

50.850417, 4.454593</br>
50.850417, 4.454593</br>
50.850417, 4.454593</br>
50.850417, 4.454593</br>
...


## Tested components
This library is tested with:

 * Adafruit Ultimate GPS Breakout - 66 channel w/10 Hz updates - Version 3
 * Raspberry V3