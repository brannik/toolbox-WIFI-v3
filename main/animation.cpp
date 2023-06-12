#include "Arduino.h"
#include "animation.h"
#include "config.h"
#include "extentions.h"

int R,G,B;
int R_C=0;
int G_C=0;
int B_C=0;
int SPEED = MODULE.EEPROM_GET(eeprom,EEPROM_ADDR_INT_ANIMATION_SPEED);

Animation::Animation(){
}
unsigned long time_now = 0;

void WriteToPins(int RED_C,int GREEN_C,int BLUE_C){
  analogWrite(INTERIOR_RED_PIN,RED_C);
  analogWrite(INTERIOR_GREEN_PIN,GREEN_C);
  analogWrite(INTERIOR_BLUE_PIN,BLUE_C);
}
void Animation::GET_COLORS(){
  R = MODULE.EEPROM_GET(eeprom,EEPROM_ADDR_INT_RED_VALUE);
  G = MODULE.EEPROM_GET(eeprom,EEPROM_ADDR_INT_GREEN_VALUE);
  B = MODULE.EEPROM_GET(eeprom,EEPROM_ADDR_INT_BLUE_VALUE);
}
void Animation::STATIC_COLOR(){
  
  WriteToPins(R,G,B);
}

void Animation::PULSE_COLOR(){
  unsigned long now = millis();
  if(R_C < R){
    if(millis() > now + SPEED){
      R_C = R_C + 1;
      WriteToPins(R_C,0,0);
      now = millis();
    }  
  }else if(G_C < G){
    if(millis() > now + SPEED){
      G_C = G_C + 1;
      if(R_C > 0){
        R_C = R_C - 1;  
      }
      WriteToPins(R_C,G_C,0);
      now = millis();
    }  
  }else if(B_C < B){
    if(millis() > now + SPEED){
      B_C = B_C + 1;
      if(G_C > 0){
        G_C = G_C - 1;  
      }  
      WriteToPins(0,G_C,B_C);
      now = millis();
    }  
  }else if(B_C > 0){
    if(millis() > now + SPEED){
      B_C = B_C - 1;
      R_C = R_C + 1;
      WriteToPins(R_C,0,B_C);
      now = millis();    
    }  
  }
}

void Animation::PULSE_MULTIPLE_COLORS(){
  // transitions R -> G -> B -> R
}
Animation ANIMATION = Animation();
