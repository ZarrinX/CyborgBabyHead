/* 
 Cyborg Baby Head controller
 Reacts to HIGH/LOW changes in a simple tilt sensor to trigger vibration motors, servos,
 LEDs, and a winking baby eye. While "idle", there will be random movements from the 
 different components.

 Built on an Arduino Uno

 by Zachary Rice 
 https://github.com/ZarrinX 
 */


/***************************************************************
START GLOBALS
***************************************************************/

#include <Servo.h> 

// Global Variables
int pos = 0;    // variable to store the servo position
int TiltState = 0;         // Stores the HIGH/LOW value of the tilt sensor
int randVal = 0;
long Interval = 5000;           // interval at which to run the HorrorShow (milliseconds)


// Define the RGB LEDs (Uses PWM for full spectrum control)
int rLED = 6;
int gLED = 5;
int bLED = 3;

// Random values for idle events (values chosen at random because why not?)
int randWink = 800;
int randRGB = 333;
int randSpine = 19;
int randLightsOut = 489;

int TiltSen = 12; // Tilt Sensor. Basically an momentary switch
int Motor = 10; // Vibrations
int Eye = 11; // Wink ;). Literally. This is probably the creepiest part.

Servo BabySpine;  // Create servo object to control a servo

/***************************************************************
END GLOBALS
***************************************************************/



/***************************************************************
START SETUP
***************************************************************/

void setup() 
{ 
  randomSeed(analogRead(0)); // Used to trigger randomized events in "Idle" mode (I put a wire on this pin to act as an inductor to generate more truely random values)
  
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

/***************************************************************
END SETUP
***************************************************************/



/***************************************************************
START MAIN LOOP
***************************************************************/

void loop()
{
  randVal = random(0, 4096); // Sets the random seed for this loop
  
  if(digitalRead(TiltSen) != TiltState) // When the tilt sensor is triggered, do this
  {
    delay(400);
    if(digitalRead(TiltSen) != TiltState)
    {
      HorrorShow();
    }
  }
  
  // "Idle" behaviors
  
  // Make the Right Eye wink
  if (randVal == randWink)
  {
    digitalWrite(Eye, HIGH);
    delay(200);
    digitalWrite(Eye, LOW);
  }
  
  // The Eye will rapidly change color for a moment
  if (randVal == randRGB)
  {
    int EyeMode = random(0, 4);
    
    if (EyeMode == 0)
    {
      RGB();
    }
    
    // Dim Blue
    if (EyeMode == 1)
    {
      digitalWrite(gLED, LOW);
      digitalWrite(bLED, LOW);
    } 
    
    // Green
    if (EyeMode == 2)
    {
      digitalWrite(rLED, HIGH);
      digitalWrite(gLED, LOW);
      digitalWrite(bLED, HIGH);

    } 
    
    // Purple
    if (EyeMode == 3)
    {
      digitalWrite(rLED, LOW);
      digitalWrite(gLED, HIGH);
      digitalWrite(bLED, LOW);
    } 
    
    // A Color?
    if (EyeMode == 4)
    {
      digitalWrite(rLED, LOW);
      digitalWrite(gLED, LOW);
      digitalWrite(bLED, LOW);
    } 
  }
  
  // Make the severed spine "twitch"
  if (randVal == randSpine)
  {
    BabySpine.write (random(70, 110));
  }
  
  // Turn off the Left eye
  if (randVal == randLightsOut)
  {
    digitalWrite(rLED, HIGH);
    digitalWrite(gLED, HIGH);
    digitalWrite(bLED, HIGH);
  }
  
  delay(10); //The loop is happening too fast, the random fuction is meh so it needs to  be slower
}

/***************************************************************
END MAIN LOOP
***************************************************************/





//  Kinetic events triggered by the disruption of the tilt sensor
void HorrorShow()
{
  
  // Eye turns Red
  digitalWrite(rLED, LOW);
  digitalWrite(gLED, HIGH);
  digitalWrite(bLED, HIGH);
  
  digitalWrite(Motor, HIGH); // Turn on the vibration motor
  
  int count = 0;
  //int value = random(20, 160);
  while(count <= 28)
  {
    int val = random(0, 180);
    BabySpine.write(val);
    digitalWrite(Eye, HIGH);
    delay(random(100, 550));
    digitalWrite(Eye, LOW);
    count = count +1;
  }
  
  digitalWrite(Motor, LOW); // Turn off the vibration motor
  
  //  Reset RGB values
  digitalWrite(rLED, HIGH);
  digitalWrite(gLED, HIGH);
  digitalWrite(bLED, LOW);
  
  delay(500);
  TiltState = digitalRead(TiltSen); // Last event. Store the current Tilt sensor value (Lets the main loop know the baby head isn't moving anymore)
  
  
}

//Change the eye color for a moment
void RGB()
{
    digitalWrite(gLED, LOW);
    digitalWrite(bLED, HIGH);
    delay(random(40, 350));
    digitalWrite(rLED, LOW);
    digitalWrite(gLED, LOW);
    digitalWrite(bLED, HIGH);
    delay(random(40, 100));
    digitalWrite(rLED, HIGH);
    digitalWrite(gLED, HIGH);
    digitalWrite(bLED, LOW);
    delay(random(40, 350));
}
