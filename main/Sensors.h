#ifndef SENSORS_H
#define SENSORS_H

class Sensors {
  public: 
  Sensors(int SdaPin, int SclPin);
  float XAccel();
  float YAccel();
  float ZAccel();
  float Altitude();
  float Pressure();
  float Direction();
  boolean up();
  void InitAltimeter(float samplesToTake);
  
  private:
  int SdaPin;
  int SclPin;
  float ADCCountToVoltage(float count);
  float VoltageToG(float voltage);
};

#endif SENSORS_H
