#ifndef _CONFIG_H

  #define MAX_BRIGTHNES 255
  #define MIN_BRIGTHNES 0

  // I/O PINS
  // need to ajust pin numbers
  
  #define DRL_PIN 13
  #define DASHBOARD_PIN 12
  #define INTERIOR_RED_PIN 14
  #define INTERIOR_GREEN_PIN 27
  #define INTERIOR_BLUE_PIN 26
  #define AMP_PIN 25
  #define DVR_PIN 33

  // indicator pins
  #define DRL_IND_PIN 15
  #define INT_IND_PIN 2
  #define AMP_IND_PIN 4
  #define DVR_IND_PIN 16
  
  // REAL PINS
  // need to ajust pin numbers
  #define HALL_PIN_A 1 // to change to 35
  #define HALL_PIN_B 2 // to change to 34
  #define HALL_PIN_C 39
  #define HALL_PIN_D 36
  #define HALL_PIN_E 23
  #define HALL_PIN_F 22

  // EEPROM data address

  #define EEPROM_ADDR_DRL_STATE 1
  #define EEPROM_ADDR_DRL_DELAY 20
  
  #define EEPROM_ADDR_INT_RED_VALUE 60
  #define EEPROM_ADDR_INT_GREEN_VALUE 70
  #define EEPROM_ADDR_INT_BLUE_VALUE 80
  #define EEPROM_ADDR_INT_ANIMATION_SPEED 90
  #define EEPROM_ADDR_INT_STATE 100
  #define EEPROM_ADDR_INT_DEEF_ANIMATION_TYPE 120
  #define EEPROM_ADDR_INT_DELAY 130
  
  #define EEPROM_ADDR_AMP_STATE 140
  #define EEPROM_ADDR_AMP_DELAY 160

  #define EEPROM_ADDR_DVR_STATE 170
  #define EEPROM_ADDR_DVR_DELAY 190

  // animation types
  #define ANIMATION_TYPE_STATIC 1000
  #define ANIMATION_TYPE_PULSE_SIMPLE 1001
  #define ANIMATION_TYPE_PULSE 1002

  #define eeprom 0x50

  // shift numbers
  #define SHIFT_REVERSE 1
  #define SHIFT_NEUTRAL 2
  #define SHIFT_FIRST 3
  #define SHIFT_SECOND 4
  #define SHIFT_TIRTH 5
  #define SHIFT_FOURTH 6
  #define SHIFT_FIFTH 7
  
  
 #endif
