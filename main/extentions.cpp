
#include "Arduino.h"
#include "extentions.h"
#include "config.h"
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
modules::modules(){
}

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 
char* letter_one="";
char* mid_letter="";
char* last_letter="";
void modules::EEPROM_WRITE(int deviceaddress,unsigned int eeaddress,byte data){
  // save data to eeprom
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));      //writes the MSB
  Wire.write((int)(eeaddress & 0xFF));    //writes the LSB
  Wire.write(data);
  Wire.endTransmission();

}

int modules::EEPROM_GET(int deviceaddress, unsigned int eeaddress){
  Wire.begin();
  int rdata = 0;
  Wire.beginTransmission(eeprom);
  Wire.write((int)(eeaddress >> 8));      //writes the MSB
  Wire.write((int)(eeaddress & 0xFF));    //writes the LSB
  Wire.endTransmission();
  Wire.requestFrom(deviceaddress,1);
  if (Wire.available()) 
    rdata = Wire.read();
  return rdata;
}

void process_value(int val){
  switch(val){
    case 1:
      letter_one = "   ";
      mid_letter = "[R]";
      last_letter = " N ";
      break;
    case 2:
      letter_one = " R ";
      mid_letter = "[N]";
      last_letter = " 1 ";
      break;
    case 3:
      letter_one = " N ";
      mid_letter = "[1]";
      last_letter = " 2 ";
      break;  
    case 4:
      letter_one = " 1 ";
      mid_letter = "[2]";
      last_letter = " 3 ";
      break;
    case 5:
      letter_one = " 2 ";
      mid_letter = "[3]";
      last_letter = " 4 ";
      break;
    case 6:
      letter_one = " 3 ";
      mid_letter = "[4]";
      last_letter = " 5 ";
      break;
    case 7:
      letter_one = " 4 ";
      mid_letter = "[5]";
      last_letter = "   ";
      break;
  }
}

void modules::DISPLAY_SET_TEXT(int text){
  u8g2.begin();
  process_value(text);
  u8g2.clearBuffer();          
  u8g2.setFont(u8g2_font_t0_22b_mf  );  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
  u8g2.drawStr(25,30,letter_one); 
  u8g2.setFont(u8g2_font_crox4hb_tn  );  
  u8g2.drawStr(50,30,mid_letter);  
  u8g2.setFont(u8g2_font_t0_22b_mf  ); 
  u8g2.drawStr(75,30,last_letter);  
  u8g2.sendBuffer();        
  delay(3000);
}

modules MODULE = modules();
