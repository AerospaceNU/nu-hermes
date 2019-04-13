#include "Data.h"
#include <arduino.h>

int processSignal(int state)
{
  int readLoop = 1;
  int inputData = 0;
  int startTime = millis();

  if (state == 4 || state == 0 || state == 3)
  {
    while (readLoop == 1)
    {

    Serial.println(Serial3.available());
      if(Serial3.available() > 0)
      { // Checks whether data is comming from the serial port
        inputData = Serial3.read(); // Reads the data from the serial port
        Serial.println("Data Recieved");
        Serial.println(inputData);
      }
  
      if (inputData == 109)
      {
        // Enter flipping state
        
      }
      else if (inputData == 99)
      {
        // enter nicrome state
        
      }
      else if (inputData == 118)
      {
        // verify rover state / functionality
      }
      else if ((millis() - startTime) > 1000)
      {
        readLoop = 0;
      }
  
      delay(100);
    }
  }
  else
  {
    Serial3.print("State: ");
    Serial3.println(state);
    return state;
  }

  
}


