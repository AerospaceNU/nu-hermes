#include "Control.h"

void InitMotors()
{
  DRV8834 stepperRight(MOTOR_STEPS, DIR_RIGHT, STEP_RIGHT);
  DRV8834 stepperLeft(MOTOR_STEPS, DIR_LEFT, STEP_LEFT);

  stepperRight.begin(RPM, MICROSTEPS);
  delay(200);
  stepperLeft.begin(RPM, MICROSTEPS);
  delay(200);
  stepperRight.enable();
  setpperLeft.enable();
}

void RotateStepper(bool right, int degrees_to_move)
{
  if(right)
  {
    stepperRight.rotate(degrees_to_move);
  }
  else
  {
    stepperLeft.rotate(degrees_to_move);
  }
}

