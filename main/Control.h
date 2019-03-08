#ifndef CONTROL_H
#define CONTROL_H

#include <BasicStepperDriver.h>
#include <DRV8834.h>
#include <Arduino.h>

#define MOTOR_STEPS 200
#define RPM 120

#define MICROSTEPS 1

#define DIR_LEFT 8
#define STEP_LEFT 9

#define DIR_RIGHT 10
#define STEP_RIGHT 11


void InitMotors();

#endif
