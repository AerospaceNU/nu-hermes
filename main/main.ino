#include <Adafruit_MPL3115A2.h>
#include "Sensors.h"
#include <Wire.h>

// this is the setup
void setup() {
  Wire.begin();
  Serial.begin(9600);
  analogReference(EXTERNAL); // Sets the refrence for the ADC to the external source on pin AREF (on the inside of pin 23)
  InitAltimeter();
}

void loop() {
  // put your main code here, to run repeatedly:

}



// Needed abstractions
// Data
// Sensors
// Motion
// INIT
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

// Init
// starts the software and prepares the device for function

// Collect
// controlls the mechanism for collecting the soil sample

// Photograph
// controlls the phtograph taking part of the mission
// including calls to the Motion Class






