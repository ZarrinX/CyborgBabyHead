// Cyborg Baby Head controller
// Reacts to HIGH/LOW changes in a simple tilt sensor to trigger vibration motors, servos,
// LEDs, and a winking baby eye. While "idle", there will be random movements from the 
// different components.

// Built on an Arduino Uno

// by Zachary Rice <https://github.com/ZarrinX> 

#include <Servo.h> 

// Global Variables
int pos = 0;    // variable to store the servo position
int TiltState = 0;         // Stores the HIGH/LOW value of the tilt sensor

// Define the RGB LEDs (Uses PWM for full spectrum control)
int rLED = 6;
int gLED = 5;
int bLED = 3;

int TiltSen = 12; // Tilt Sensor. Basically an momentary switch
int Motor = 10; // Vibrations
int Eye = 11; // Wink ;). Literally. This is probably the creepiest part.

Servo BabySpine;  // Create servo object to control a servo

void setup() 
{ 
  BabySpine.attach(9);  // attaches the servo on pin 9 to the servo object 
  
  // Define Output pins
  pinMode(rLED, OUTPUT);
  pinMode(gLED, OUTPUT);
  pinMode(bLED, OUTPUT);
  pinMode(Motor, OUTPUT);
  pinMode(Eye, OUTPUT);
  
  //Define Inputs
  pinMode(TiltSen, INPUT);
  
  //Set startup values
  TiltState = digitalRead(TiltSen);
  
} 
