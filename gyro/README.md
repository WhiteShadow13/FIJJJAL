# Gyroscope

A commun gyrscope is a device used for measuring or maintaining orientation and angular velocity.It is a spinning wheel or disc in which the axis of rotation (spin axis) is free to assume any orientation by itself. When rotating, the orientation of this axis is unaffected by tilting or rotation of the mounting, according to the conservation of angular momentum. </br>

![picture alt](https://commons.wikimedia.org/wiki/File:3D_Gyroscope.png#/media/File:3D_Gyroscope.png "Title is optional")

In electronic we use gyro sensors, also known as angular rate sensors or angular velocity sensors, are devices that sense angular velocity.

![picture alt](gyro/gyro.png)

Vibration gyro sensors sense angular velocity from the Coriolis force applied to a vibrating object.
Here an example Epson 's double-T structure crystal element.

![picture alt](gyro/gyro2.png)

## L3G4200D

The L3G4200D is a triple axis gyroscope. Our module  don’t has a spinning wheel, it has a microelectromechanical system that uses similar technics.

## Datasheet

 - Supply : 2,7 à 6,5 Vcc
 - Communication protocol : I2C (until 400 kHz) or SPI (10 MHz)
 - Dimensions : 21,6 x 20,3 mm

 For more informations the complete datasheet here (https://www.generationrobots.com/media/ModuleGyroscope27911/27911-L3G4200D-Gyroscope-Manufacturer-Datasheet.pdf)

## Code

to run : 

- g++ -o gyro *.cpp

- ./gyro