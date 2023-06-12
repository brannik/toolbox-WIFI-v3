#include "Arduino.h"
#include "shift.h"
#include "config.h"
#include "extentions.h"
getShift::getShift(){
}
boolean hasChanged = true;
int sft = SHIFT_NEUTRAL;
char str[100];
void getShift::READ(){
  long mes_a = 0;
  long mes_b = 0;
  long mes_c = 0;
  long mes_d = 0;
  long mes_e = 0;
  long mes_f = 0;
  // read all 6 hall sensors and compare
  for(int i = 0; i < 10; i++){
      int value_a = 
      mes_a += analogRead(HALL_PIN_A);
      int value_b = 
      mes_b += analogRead(HALL_PIN_B);
      int value_c = 
      mes_c += analogRead(HALL_PIN_C);
      int value_d = 
      mes_d += analogRead(HALL_PIN_D);
      int value_e = 
      mes_e += analogRead(HALL_PIN_E);
      int value_f = 
      mes_f += analogRead(HALL_PIN_F);
  }
  mes_a /= 10;
  mes_b /= 10;
  mes_c /= 10;
  mes_d /= 10;
  mes_e /= 10;
  mes_f /= 10;
  sprintf(str,"VALUES [ %ld | %ld | %ld | %ld | %ld | %ld ]",mes_a,mes_b,mes_c,mes_d,mes_e,mes_f);
  Serial.println(str);
  delay(200);
  // check for changes and process display change
  if(hasChanged){
    MODULE.DISPLAY_SET_TEXT(sft);
    hasChanged = false;
  }
}

getShift SHIFT = getShift();
