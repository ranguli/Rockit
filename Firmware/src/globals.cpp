#include "globals.h"

//Physical magnitudes
int altMaxDig[] = {}; //Max altitude digits
float altOld = 0.0;
float rocketAccel = 0.0;
float temp = 0.0;
float currentPressure = 0.0;
float altitudeDelta = 0.0;
float filteredAltitudeDelta = 0.0;
int altMax = 0;
float altThreshold = 10; //Altitude threshold for launchd detection in meters
float accelThreshold = 2.0; //Acceleration threshold for launch detection in gs.
float startingPressure = 0.0;

//Definition of time and auxiliary integers
int p, r = 0;
long int t1 = 0;
long int t4 = 0, tout = 300000; //Here tout is the timeout variable tout = 300000 equals 5 min of data logging time

char filename[] = "00.CSV"; //Dummy file name to store flight data.

//Config. rotary switch. This configuration is for the real-coded rotary switch
byte switchPins[4] = {15, 13, 14, 16}; //Digital pins assigned to the rotary switch
byte rotValue = B0000; // Variable for printing value over serial debug

//Boolean variables defining the state of the program
bool initVar = true;
bool launchCondition1 = false;
bool launchCondition2 = false;
bool deploy = false;
bool automatic = false;
bool timer = false;
bool overtime = false;
bool piezoEnable = true;

//LEDs
int batLED = 2; //Battery indicator LED
int statusLED = 26; //Status LED

//Servos
int servo1pin = 28;
int servo2pin = 27;

//Piezo
int piezo = 12;