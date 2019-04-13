#include <Arduino.h>
#include <Wire.h>
#include "Sensors.h"
#include "Motion.h"
#include "Data.h"

#define DEBUG

#define NICROME 20
#define NICROME_DELAY 30000

#define TEST_PIN_TWO 21
#define TEST_PIN_ONE 12

#define ANALOG_TEST_ONE A10
#define ANALOG_TEST_TWO A11

#define LEFT  1
#define RIGHT 2

Sensors board(19, 18);

int state = 0;
unsigned long launchTime = 0;
float previousAltitude = 0;
float launchAltitude = 0;


// Setperate Rover using nicrome
void breakNicrome()
{
  digitalWrite(NICROME, HIGH);
  Serial3.println("Nicrome set to release");
  delay(NICROME_DELAY / 2);
  Serial3.println("Nicrome in progress");
  delay(NICROME_DELAY / 2);
  Serial3.println("Nicrome Completed");  
  digitalWrite(NICROME, LOW);
  delay(5000);
  state = 3;
}

void roverMotion()
{
  Serial3.println("Flipping Rover");
  for (int i = 0; i < 24; i++)
  {
    Serial3.print("Flip:");
    Serial3.println(i);
    if ( i % 2)
    {
      turnToPoint(LEFT, 200, 180);
      delay(1000);
      turnToPoint(LEFT, 200, 0);
    }
    else
    {
      turnToPoint(RIGHT, 200, 180);
      delay(1000);
      turnToPoint(RIGHT, 200, 0);
    }

    delay(3500);
  }
}

void detectLaunch()
{
  float currentAltitude = board.Altitude();

  float accelMag = sqrt(sq(board.XAccel()) + sq(board.YAccel()) + sq(board.ZAccel()));

  if ((currentAltitude > (previousAltitude + 30)) || (currentAltitude > 300) || (accelMag > 2.75))
  {
    launchTime = millis();
    state = 1;
  }

  previousAltitude = currentAltitude;
  return;
}


void detectGround()
{
  int loopCount = 0;
  while (loopCount < 180)
  {
    loopCount++;
    delay(1000);
    Serial3.println("Ground detection");
  }

  delay(8000);
  state = 2;
  return;
}

// this is the setup
void setup() 
{

  Serial3.begin(9600);
  Serial3.println("Rover Power up");

  #ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Begining");
  #endif

  pinModeInitAll();
  analogReference(EXTERNAL); // Sets the refrence for the ADC to the external source on pin AREF (on the inside of pin 23)

  #ifdef DEBUG
  Serial.println("Running");
  state = 4;
  #endif
  
  delay(100);
  board.init();

  digitalWrite(TEST_PIN_TWO, LOW);
  Serial3.println("Rover Initalized");
}

void pinModeInitAll()
{
  pinMode(13, OUTPUT);
  pinMode(NICROME, OUTPUT);
  digitalWrite(NICROME, LOW);
  pinMode(TEST_PIN_TWO, OUTPUT);
  pinMode(TEST_PIN_ONE, INPUT);
}

void loop() 
{
  switch (state)
  {
    case 0:
      detectLaunch();
      break;
    
    case 1:
      detectGround();
      break;

    case 2:
      breakNicrome();
      break;

    case 3:
      roverMotion();
      break;

    case 4:
      Serial3.println("in startup mode");

      if (digitalRead(TEST_PIN_ONE));
      {
        Serial3.println("Entering manual override mode");
      }
      break;
     
    default:
      break;
      Serial3.print("Current Rover state: ");
      Serial3.println(state);
  }

  #ifdef DEBUG
  Serial3.println(digitalRead(TEST_PIN_ONE));
  #endif

  if (digitalRead(TEST_PIN_ONE))
  {
    #ifdef DEBUG
    Serial3.println("Running Flip");
    #endif

    turnToPoint(LEFT, 175, 180);
    turnToPoint(LEFT, 200, 0);
    delay(500);
    turnToPoint(RIGHT, 175, 180);
    turnToPoint(RIGHT, 200, 0);
    
  }

  #ifdef DEBUG
  Serial3.println(board.Altitude());
  Serial3.println(board.XAccel());
  Serial3.println(board.YAccel());
  Serial3.println(board.ZAccel());
  Serial3.println("TEST");
  #endif

  state = processSignal(state);
  delay(500);

}




// Data
// Used to communicate with the outside world, through radio,
// or other serial connections
