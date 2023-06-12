// setup pin_mode
#include "Arduino.h"
#include "setup.h"
#include "config.h"
#include <Wire.h>

initialize::initialize(){
}

void initialize::BEGIN(){
  // setup pin modes

  Wire.begin();
  pinMode(HALL_PIN_A,INPUT_PULLUP);
  pinMode(HALL_PIN_B,INPUT_PULLUP);
  pinMode(HALL_PIN_C,INPUT_PULLUP);
  pinMode(HALL_PIN_D,INPUT_PULLUP);
  pinMode(HALL_PIN_E,INPUT_PULLUP);
  pinMode(HALL_PIN_F,INPUT_PULLUP);


  pinMode(DRL_PIN,OUTPUT);
  pinMode(DASHBOARD_PIN,OUTPUT);
  pinMode(INTERIOR_RED_PIN,OUTPUT);
  pinMode(INTERIOR_GREEN_PIN,OUTPUT);
  pinMode(INTERIOR_BLUE_PIN,OUTPUT);
  pinMode(AMP_PIN,OUTPUT);
  pinMode(DVR_PIN,OUTPUT);

  pinMode(DVR_IND_PIN,OUTPUT);
  pinMode(DVR_IND_PIN,OUTPUT);
  pinMode(DVR_IND_PIN,OUTPUT);
  pinMode(DVR_IND_PIN,OUTPUT);
  
}

initialize INITIALIZE = initialize();
