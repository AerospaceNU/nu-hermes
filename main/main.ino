#include <Arduino.h>
#include <Wire.h>
#include "Sensors.h"
#include "Motion.h"

#define DEBUG 1

#define NICROME 9
#define NICROME_DELAY 10000

#define TEST_PIN_ONE 20
#define TEST_PIN_TWO 21

#define ANALOG_TEST_ONE A10
#define ANALOG_TEST_TWO A11

#define LEFT  1
#define RIGHT 2

Sensors board(19, 18);

int state = 0;
int launchTime = 0;
float previousAltitude = 0;
float launchAltitude = 0;


// this is the setup
void setup() 
{

  #if DEBUG
  Serial.begin(9600);
  Serial.println("Begining");
  #endif

  initSteppers();
  pinModeInitAll();
  analogReference(EXTERNAL); // Sets the refrence for the ADC to the external source on pin AREF (on the inside of pin 23)

  #if DEBUG
  Serial.println("Running");
  #endif
  
  delay(100);
  board.init();

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

  #if DEBUG
  Serial.println(analogRead(ANALOG_TEST_ONE));
  #endif

  if (analogRead(ANALOG_TEST_ONE) < 30)
  {
    #if DEBUG
    Serial.println("Running Flip");
    #endif
    
    flipRover(LEFT);
    delay(500);
    flipRover(RIGHT);
    
  }

  #if DEBUG
  Serial.println(board.Altitude());
  Serial.println(board.XAccel());
  Serial.println(board.YAccel());
  Serial.println(board.ZAccel());
  Serial.println("TEST");
  #endif
  
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
