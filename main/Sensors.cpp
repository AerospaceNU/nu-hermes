#include <Adafruit_MPL3115A2.h>
#include "Sensors.h"
#include <Wire.h>

const int ACCEL_PIN_X = A0;
const int ACCEL_PIN_Y = A1;
const int ACCEL_PIN_Z = A2;

const int SCL_PIN = 19;
const int SDA_PIN = 18;

Adafruit_MPL3115A2 Altimeter = Adafruit_MPL3115A2();


Sensors::Sensors(int SdaPin, int SclPin) 
{
  this->SdaPin = SdaPin;
  this->SclPin = SclPin;
}

int Sensors::XAccel() 
{
  return analogRead(ACCEL_PIN_X);
}

int Sensors::YAccel() 
{
  return analogRead(ACCEL_PIN_Y);
}

int Sensors::ZAccel() 
{
  return analogRead(ACCEL_PIN_Z);
}

int Sensors::Altitude()
{
  return Altimeter.getAltitude();
}

int Sensors::Pressure()
{
  return Altimeter.getPressure();
}

/**
 * @param {float} samplesToTake
 */
void Sensors::InitAltimeter(float samplesToTake)
{
  float totalPressure = 0;
  float finalPressure = 0;
  
  for(int i = 0; i < samplesToTake; i++)
  {
    totalPressure += Altimeter.getPressure();
  }

  finalPressure = totalPressure / samplesToTake;

  Serial.println("Calibrated Sea Level Pressure: " + finalPressure + "Pa");

  Altimeter.setSeaPressure(finalPressure); 
}
  
boolean Sensors::up()
{
  //TODO:
  // determine how to find up
}















