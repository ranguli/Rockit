#pragma once

#include <Servo.h>
#include <SD.h>

#include "CircularBuffer.h"

//Physical magnitudes
extern float altOld; //Baseline pressure
extern int altMax; //Rounded maximum altitude
extern int altMaxDig[4]; //Max altitude digits
extern int dvsr; //Dummy variable for beeping/flasing the altitude
extern float temp;
extern float currentPressure;
extern float altitudeDelta;
extern float altThreshold; //Altitude threshold for launchd detection in meters
extern float accelThreshold; //Acceleration threshold for launch detection in gs.
extern float filteredAltitudeDelta;
extern float rocketAccel;
extern float startingPressure;

//Definition of time and auxiliary integers
extern int n, p, r;
extern int deltat; //Time step of every loop iteration
extern long int t1; //Time variables
extern long int t4, tout; //Here tout is the timeout variable tout = 300000 equals 5 min of data logging time

extern char filename[]; //Dummy file name to store flight data.

//Config. rotary switch. This configuration is for the real-coded rotary switch
extern byte switchPins[4]; //Digital pins assigned to the rotary switch
extern byte rotValue; // Variable for printing value over serial debug
extern byte switchPos; // Variable for storing the current switch possition

//Boolean variables defining the state of the program
extern bool initVar;
extern bool launchCondition1;
extern bool launchCondition2;
extern bool deploy;
extern bool automatic;
extern bool timer;
extern bool overtime;
extern bool piezoEnable;

//LEDs
extern int batLED; //Battery indicator LED
extern int statusLED; //Status LED

//Servos
extern int servo1pin;
extern int servo2pin;

//Piezo
extern int piezo;
