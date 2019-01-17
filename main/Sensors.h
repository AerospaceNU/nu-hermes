class Sensors {
  public: 
  Sensors(int SdaPin, int SclPin);
  int XAccel();
  int YAccel();
  int ZAccel();
  int Altitude();
  int Pressure();
  boolean up();
  void InitAltimeter(int samplesToTake);
  
  private:
  int SdaPin;
  int SclPin;
};

