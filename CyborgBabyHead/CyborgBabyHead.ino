/* 
 Cyborg Baby Head controller
 Reacts to HIGH/LOW changes in a simple tilt sensor to trigger vibration motors, servos,
 LEDs, and a winking baby eye. While "idle", there will be random movements from the 
 different components.

 Built on an Arduino Uno

 by Zachary Rice 
 https://github.com/ZarrinX 
 */

#include <Servo.h> 

// Global Variables
int pos = 0;    // variable to store the servo position
int TiltState = 0;         // Stores the HIGH/LOW value of the tilt sensor
int randVal = 0;
long Interval = 5000;           // interval at which to run the HorrorShow (milliseconds)
long previousMillis = 0;        // will store last time HorrorShow was updated

// Define the RGB LEDs (Uses PWM for full spectrum control)
int rLED = 6;
int gLED = 5;
int bLED = 3;

// Random values for idle events (values chosen at random because why not?)
int randWink = 213;
int randRGB = 61;
int randSpine = 19;

int TiltSen = 12; // Tilt Sensor. Basically an momentary switch
int Motor = 10; // Vibrations
int Eye = 11; // Wink ;). Literally. This is probably the creepiest part.

Servo BabySpine;  // Create servo object to control a servo

void setup() 
{ 
  randomSeed(analogRead(0)); // Used to trigger randomized events in "Idle" and "HorrorShow" mode (I put a wire on this pin to act as an inductor to generate more truely random values)
  
  // \/ Best Servo name
  BabySpine.attach(9);  // attaches the servo on pin 9 to the servo object. Know your servo cable colors http://www.fatlion.com/sailplanes/servos.html
  
  // Define Output pins
  pinMode(rLED, OUTPUT);
  pinMode(gLED, OUTPUT);
  pinMode(bLED, OUTPUT);
  pinMode(Motor, OUTPUT);
  pinMode(Eye, OUTPUT);
  
  //Define Inputs
  pinMode(TiltSen, INPUT);
  
  //Set startup values
  TiltState = digitalRead(TiltSen); // Sets the current sensor value
  
  // Sets the RGB value to Blue. The RGB LED used is a common Anode type. LOW values allow the curreent to flow. This is called current sinking. 
  // Common Cathode would be more intuitive but RadioShack :/
  digitalWrite(rLED, HIGH);
  digitalWrite(gLED, HIGH);
  digitalWrite(bLED, LOW);
  digitalWrite(Eye, LOW);
  
} 

void loop()
{
  randVal = random(256); // Sets the random seed for this loop
  
  if(digitalRead(TiltSen) != TiltState) // When the tilt sensor is triggered, do this
  {
    HorrorShow();
  }
  
  // "Idle" behavior
  if (randVal = randWink)
  {
    digitalWrite(Eye, HIGH);
    delay(200);
    digitalWrite(Eye, LOW);
  }
  
  // The Eye will rapidly change color for a moment
  if (randVal = randRGB)
  {
    RGB();
  }
  
  // Make the severed spine "twitch"
  if (randVal = randSpine)
  {
    BabySpine.write (random(20, 160));
  }
  
  
}

//  Kinetic events triggered by the disruption of the tilt sensor
void HorrorShow()
{
  // Eye turns Red
  digitalWrite(rLED, LOW);
  digitalWrite(gLED, HIGH);
  digitalWrite(bLED, HIGH);
  
  digitalWrite(Motor, HIGH); // Turn on the vibration motor
  
  unsigned long currentMillis = millis(); // Starts the 5 seconds timer for the HorrorShow event (defined in thr global variable "Interval")
  
  
  while(currentMillis - previousMillis > Interval)
  {
    int pos = random(10, 170);
    delay(500);
  }
  
  digitalWrite(rLED, HIGH);
  digitalWrite(gLED, HIGH);
  digitalWrite(bLED, LOW);
  
  TiltState = digitalRead(TiltSen); // Last event. Store the current Tilt sensor value (Lets the main loop know the baby head isn't moving anymore)
}

void RGB()
{
    digitalWrite(gLED, LOW);
    digitalWrite(bLED, HIGH);
    delay(random(40, 350));
    digitalWrite(gLED, HIGH);
    digitalWrite(bLED, LOW);
    delay(random(40, 350));
    digitalWrite(gLED, HIGH);
    digitalWrite(gLED, LOW);
    delay(random(40, 350));
    digitalWrite(gLED, LOW);
    digitalWrite(bLED, HIGH);
    delay(random(40, 350)); 
    digitalWrite(rLED, LOW);
    digitalWrite(gLED, LOW);
    digitalWrite(bLED, LOW);
    delay(random(40, 450)); 
    digitalWrite(rLED, HIGH);
    digitalWrite(gLED, HIGH);
    digitalWrite(bLED, LOW);
}
