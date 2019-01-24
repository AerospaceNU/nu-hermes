#include <Adafruit_MPL3115A2.h>
#include "Sensors.h"
#include <Wire.h>

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
  digitalWrite(13, HIGH);
  board.InitAltimeter(10);
  digitalWrite(13, LOW);
  
}

void loop() 
{
  Serial.println("TEST");
  delay(3000);
  Serial.println("TEST");
  
  Serial.println("X Accel: " + String(board.XAccel()));
  Serial.println("Y Accel: " + String(board.YAccel()));
  Serial.println("Z Accel: " + String(board.ZAccel()));
  Serial.println("Pressure: " + String(board.Pressure()));
  Serial.println("Altitude: " + String(board.Altitude()));
  delay(1000);
  digitalWrite(13, LOW);
  delay(500);
  digitalWrite(13, HIGH);
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






