#include <Adafruit_MPL3115A2.h>
#include "Sensors.h"
#include <Wire.h>

const int ACCEL_PIN_X = A0;
const int ACCEL_PIN_Y = A1;
const int ACCEL_PIN_Z = A2;

const int SCL_PIN = 18;
const int SDA_PIN = 19;

Adafruit_MPL3115A2 Altimeter = Adafruit_MPL3115A2();


Sensors::Sensors(int SdaPin, int SclPin) 
{
  this->SdaPin = SdaPin;
  this->SclPin = SclPin;
}

float Sensors::XAccel() 
{
  float voltage = Sensors::ADCCountToVoltage(analogRead(ACCEL_PIN_X));
  return VoltageToG(voltage);
}

float Sensors::YAccel() 
{
  float voltage = Sensors::ADCCountToVoltage(analogRead(ACCEL_PIN_Y));
  return VoltageToG(voltage);
}

float Sensors::ZAccel() 
{
  float voltage = Sensors::ADCCountToVoltage(analogRead(ACCEL_PIN_Z));
  return VoltageToG(voltage);
}

float Sensors::Altitude()
{
  return Altimeter.getAltitude();
}

float Sensors::Pressure()
{
  return Altimeter.getPressure();
}

/**
 * Sets the sealevel pressure to the current pressure to give acurate
 * relative altitudes, also initalizes the Altimter object
 * 
 * @param {float} samplesToTake
 */
void Sensors::InitAltimeter(float samplesToTake)
{
  if(!Altimeter.begin())
  {
    Serial.println("fail");
    delay(1000000);
  }

  float totalPressure = 0;
  float finalPressure = 0;
  delay(500);
  
  for(int i = 0; i < samplesToTake; i++)
  {
    totalPressure += Altimeter.getPressure();
    delay(500);
  }

  finalPressure = totalPressure / samplesToTake;

  Serial.println("Calibrated Sea Level Pressure: " + String(finalPressure) + "Pa");

  Altimeter.setSeaPressure(finalPressure); 
}
  
boolean Sensors::up()
{
  //TODO:
  // determine how to find up
  return false;
}

float Sensors::Direction()
{
  // TODO
  // determine direction calculation
  return 0.0;
}

float Sensors::ADCCountToVoltage(float count)
{
  float systemVoltage = 3.3;
  float resolution = 1023;
  float voltage;

  voltage = count * (systemVoltage / resolution);

  return voltage;

}

float Sensors::VoltageToG(float voltage)
{
  float gForces;

  gForces = (1.95 * voltage) - 3.0;

  return gForces;

}














