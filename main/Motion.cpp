#include "Motion.h"

DRV8834 stepperRight(MOTOR_STEPS, DIR_RIGHT, STEP_RIGHT);
DRV8834 stepperLeft(MOTOR_STEPS, DIR_LEFT, STEP_LEFT);

void initSteppers(void){
  
  stepperLeft.begin(RPM, MICROSTEPS);
  stepperRight.begin(RPM, MICROSTEPS);
  
}

void flipRover(int side)
{
  if (side == LEFT_SIDE)
  {
    Serial.println("Flip Left");
    stepperLeft.move(-7200);
    delay(1000);
    stepperLeft.move(7200);
  }
  else if (side == RIGHT_SIDE)
  {
    Serial.println("Flip Right");
    stepperRight.move(7600);
    delay(1000);
    stepperRight.move(-7600);
  }
  else 
  {
    Serial.println("INVALID FLIPPER");
  }
}
