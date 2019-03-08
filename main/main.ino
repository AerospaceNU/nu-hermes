#include <Adafruit_MPL3115A2.h>
#include "Sensors.h"
#include <Wire.h>

#include <BasicStepperDriver.h>
#include <DRV8834.h>

#define MOTOR_STEPS 200
#define RPM 240

#define MICROSTEPS 1

#define DIR_LEFT 8
#define STEP_LEFT 9

#define DIR_RIGHT 6
#define STEP_RIGHT 7

#define NICROME 5

int state = 0;
int launchTime = 0;
float previousAltitude = 0;
float launchAltitude = 0;

DRV8834 stepperRight(MOTOR_STEPS, DIR_RIGHT, STEP_RIGHT);
DRV8834 stepperLeft(MOTOR_STEPS, DIR_LEFT, STEP_LEFT);

Sensors board(19, 18);

// this is the setup
void setup() 
{
  pinMode(13, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
  delay(3000);
  Serial.println("Serial Init");
  //analogReference(); // Sets the refrence for the ADC to the external source on pin AREF (on the inside of pin 23)
  Serial.println("Running");
  delay(1000);
  digitalWrite(13, HIGH);
  //board.InitAltimeter(10);
  digitalWrite(13, LOW);

  //stepperRight.begin(RPM);
  stepperLeft.begin(RPM);

  stepperLeft.setMicrostep(1); 
  //stepperRight.setMicrostep(1); 
}

void detectLaunch()
{
  float currentAltitude = board.Altitude();

  if ((currentAltitude > (previousAltitude + 30)) || currentAltitude > 300)
  {
    launchTime = millis();
    state = 1;
  }

  previousAltitude = currentAltitude;
  return;
}

void flipRover()
{
  stepperLeft.move(7600);
  delay(1000);
  stepperLeft.move(-7600);
  delay(1000);

  stepperRight.move(7600);
  delay(1000);
  stepperRight.move(-7600);
  state = 3;
  return;
}

void detectGround()
{
  int currentTime = millis();
  while ((currentTime - launchTime) < 87000)
  {
    delay(1000);
    currentTime = millis();
  }

  float currentAltitude = board.Altitude();

  if (currentAltitude < 40)
  {
    delay(8000);
    state = 2;
  }
  
  
  return;
}

void loop() 
{
  if (state == 1)
  {
    detectGround();
  }
  else if (state == 0)
  {
    detectLaunch();
  }
  else if (state == 2)
  {
    setNicrome();
    delay (1000);
    flipRover();
    delay (1000);
    flipRover();
  }
  else if (state == 3)
  {
    stepperLeft.move(7600);
    while (true)
    {
      
    }
  }

  

  Serial.println("TEST");
  delay(500);
  Serial.println("TEST");

  
  
//  Serial.println("X Accel: " + String(board.XAccel()));
//  Serial.println("Y Accel: " + String(board.YAccel()));
//  Serial.println("Z Accel: " + String(board.ZAccel()));
//  Serial.println("Pressure: " + String(board.Pressure()));
//  Serial.println("Altitude: " + String(board.Altitude()));
//  delay(1000);
//  stepperLeft.enable();
//  //stepperRight.enable();
//  digitalWrite(13, LOW);
//  stepperLeft.move(20000);
//  //stepperRight.move(10000);
//  stepperLeft.disable();
//  //stepperRight.disable();
//  delay(10000);
//  stepperLeft.enable();
//  //stepperRight.enable();
//  digitalWrite(13, HIGH);
//  stepperLeft.move(20000);
//  //stepperRight.move(10000);
//  stepperLeft.disable();
//  //stepperRight.disable();
}





// Needed abstractions
// Data
// Sensors
// Motion
// collect
// photograph

// Data
// Used to communicate with the outside world, through radio,
// or other serial connections

// Sensors
// reads from accel, baro, and voltages from desired locations
// produces ints for each desired value
// will have functions to produce different requirements such as XAccel, or Battery voltage

// Motion
// routines for the movement of the rover, mainly flipping
// will involve calls to the Sensor Class

// Collect
// controlls the mechanism for collecting the soil sample

// Photograph
// controlls the phtograph taking part of the mission
// including calls to the Motion Class






