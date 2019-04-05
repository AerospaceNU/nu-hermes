#include <BasicStepperDriver.h>
#include <DRV8834.h>
#include <Arduino.h>
#include <Wire.h>
#include "Sensors.h"

#define MOTOR_STEPS 200
#define RPM 240

#define MICROSTEPS 1

#define DIR_LEFT 4
#define STEP_LEFT 5

#define DIR_RIGHT 6
#define STEP_RIGHT 22

#define NICROME 9
#define NICROME_DELAY 10000

#define TEST_PIN_ONE 20
#define TEST_PIN_TWO 21

#define ANALOG_TEST_ONE A10
#define ANALOG_TEST_TWO A11

#define LEFT_SIDE 1
#define RIGHT_SIDE 2

DRV8834 stepperRight(MOTOR_STEPS, DIR_RIGHT, STEP_RIGHT);
DRV8834 stepperLeft(MOTOR_STEPS, DIR_LEFT, STEP_LEFT);

Sensors board(19, 18);

int state = 0;
int launchTime = 0;
float previousAltitude = 0;
float launchAltitude = 0;

// this is the setup
void setup() 
{
  Serial.begin(9600);
  Serial.println("Begining");
  pinModeInitAll();
  analogReference(EXTERNAL); // Sets the refrence for the ADC to the external source on pin AREF (on the inside of pin 23)
  Serial.println("Running");
  delay(1000);
  digitalWrite(13, HIGH);
  // Starts up the altimiter and sets the current altitude as ground level
  board.InitAltimeter(10);
  digitalWrite(13, LOW);
  stepperLeft.begin(RPM, MICROSTEPS);
  stepperRight.begin(RPM, MICROSTEPS);

  digitalWrite(TEST_PIN_ONE, HIGH);
}

void pinModeInitAll()
{
  pinMode(13, OUTPUT);
  pinMode(NICROME, OUTPUT);
  pinMode(TEST_PIN_ONE, OUTPUT);
  pinMode(TEST_PIN_TWO, OUTPUT);
}

void loop() 
{

//  switch (state)
//  {
//    case 0:
//      detectLaunch();
//      break;
//    
//    case 1:
//      detectGround();
//      break;
//
//    case 2:
//      breakNicrome();
//      break;
//
//    case 3:
//      roverMotion();
//      break;
//
//    default:
//      break;
//  }

  Serial.println(analogRead(ANALOG_TEST_ONE));

  if (analogRead(ANALOG_TEST_ONE) < 30)
  {
    Serial.println("Running Flip");
    flipRover(1);
    flipRover(2);
  }
  
  Serial.println(board.Altitude());
  Serial.println(board.XAccel());
  Serial.println(board.YAccel());
  Serial.println(board.ZAccel());
  Serial.println("TEST");
  delay(500);
}

// Setperate Rover using nicrome
void breakNicrome()
{
  digitalWrite(NICROME, HIGH);
  Serial.println("Nicrome set to release");
  delay(NICROME_DELAY / 2);
  Serial.println("Nicrome in progress");
  delay(NICROME_DELAY / 2);
  Serial.println("Nicrome Completed");  
  digitalWrite(NICROME, LOW);
  delay(5000);
  state = 3;
}

void detectLaunch()
{
  float currentAltitude = board.Altitude();

  if ((currentAltitude > (previousAltitude + 30)) || currentAltitude > 300)
  {
    launchTime = millis();
    state = 1;
  }

  previousAltitude = currentAltitude;
  return;
}

void roverMotion()
{
  float x, y, z;
  x = board.XAccel();
  y = board.YAccel();
  z = board.ZAccel();
  // 1 = x, 2 = y, 3 = z
  int controlAccel = 0;

  // two should be close to 0 and 1 close to 1
  // this will determine which orentation the rover is in

  if (x > 0.75 || x < -0.75)
  {
    controlAccel = x;
  } 
  else if (y > 0.75 || y < -0.75)
  {
    controlAccel = y;
  } 
  else if (z > 0.75 || z < -0.75)
  {
    controlAccel = z;
  }
 
}

void flipRover(int side)
{
  if (side == 1)
  {
    Serial.println("Flip Left");
    stepperLeft.move(400);
    delay(2000);
    stepperLeft.move(-400);
  }
  else if (side == 2)
  {
    Serial.println("Flip Right");
    stepperRight.move(400);
    delay(2000);
    stepperRight.move(-400);
  }
  else 
  {
    Serial.println("INVALID FLIPPER");
  }
}

void detectGround()
{
  int currentTime = millis();
  while ((currentTime - launchTime) < 120000)
  {
    delay(1000);
    currentTime = millis();
  }

  float currentAltitude = board.Altitude();

  if (currentAltitude < 80)
  {
    delay(8000);
    state = 2;
  }
  return;
}



// Data
// Used to communicate with the outside world, through radio,
// or other serial connections
