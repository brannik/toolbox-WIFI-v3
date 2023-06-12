#include "Arduino.h"
#include "setup.h"
#include "extentions.h"
#include "serverClas.h"
#include "shift.h"
#include "animation.h"
void setup() {
  Serial.begin(9600);
  //Wire.begin();
  INITIALIZE.BEGIN();
  SERVER_CLAS.SETUP();
  ANIMATION.GET_COLORS();
}

void loop() {
  SERVER_CLAS.LISTEN();
  SHIFT.READ();
  SERVER_CLAS.ANIMATE();
  delay(50);
}
