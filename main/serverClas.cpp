#include <WebServer.h>

#include <Wifi.h>
#include "Arduino.h"
#include "serverClas.h"
#include "extentions.h"
#include "config.h"
#include "animation.h"
#include <WiFiClient.h>

boolean f_run = true;

#define APSSID "ANONYMOUS"
#define APPSK  "11235813"

const char* ssid = APSSID;
const char* password = APPSK;

/*
  CAUTION MINIMUM DELAY 6 SEC !!!!!! IN ANDROID APP
*/
serverClas::serverClas(){
}

WebServer server(80);

int def_animation = 0;
int curr_animation = 0;
int def_drl_state = 0;
int drl_state = 0;
int drl_delay = 0;
int last_drl_state = 0;
int def_int_state = 0;
int int_state = 0;
int last_int_state = 0;
int int_delay = 0;
int def_amp_state = 0;
int amp_state = 0;
int last_amp_state = 0;
int amp_delay = 0;
int def_dvr_state = 0;
int dvr_state = 0;
int last_dvr_state = 0;
int dvr_delay = 0;

int deff_r = 0;
int deff_g = 0;
int deff_b = 0;
int deff_anim_speed = 0;

boolean animation_changed = true;

int convertValue(String val) {
    if (val.equals("on")) return 1;
    if (val.equals("off")) return 0;
}
void handleDefault() {
    server.send(200, "text/html", "<h1>If you see this message, it's likely that your computer is infected with a virus  :) :) :)</h1>");
}
void handleColors(){
  server.send(200, "text/html", "<table><tr><td>DRL</td><td>ON</td></tr><tr><td>INT</td><td>ON</td></tr><tr><td>AMP</td><td>OFF</td></tr><tr><td>DVR</td><td>OFF</td></tr></table>");
  int red = server.arg("red").toInt();
  int green = server.arg("green").toInt();
  int blue = server.arg("blue").toInt();
  int speedAnim = server.arg("animation_speed").toInt();

  MODULE.EEPROM_WRITE(eeprom,EEPROM_ADDR_INT_ANIMATION_SPEED,speedAnim);
  MODULE.EEPROM_WRITE(eeprom,EEPROM_ADDR_INT_RED_VALUE,red);
  MODULE.EEPROM_WRITE(eeprom,EEPROM_ADDR_INT_GREEN_VALUE,green);
  MODULE.EEPROM_WRITE(eeprom,EEPROM_ADDR_INT_BLUE_VALUE,blue);

  animation_changed = true;
}

void handleRoot() {
    server.send(200, "text/html", "<table><tr><td>DRL</td><td>ON</td></tr><tr><td>INT</td><td>ON</td></tr><tr><td>AMP</td><td>OFF</td></tr><tr><td>DVR</td><td>OFF</td></tr></table>");

    def_animation = server.arg("animation_type").toInt();
    def_drl_state = convertValue(server.arg("drl"));
    def_int_state = convertValue(server.arg("int"));
    def_amp_state = convertValue(server.arg("amp"));
    def_dvr_state = convertValue(server.arg("dvr"));

    drl_delay = server.arg("drlDelay").toInt();
    int_delay = server.arg("intDelay").toInt();
    amp_delay = server.arg("ampDelay").toInt();
    dvr_delay = server.arg("dvrDelay").toInt();

    deff_r = server.arg("RED").toInt();
    deff_g = server.arg("GREEN").toInt();
    deff_b = server.arg("BLUE").toInt();
    deff_anim_speed = server.arg("ANIM_SPEED").toInt();

    MODULE.EEPROM_WRITE(eeprom,EEPROM_ADDR_INT_DEEF_ANIMATION_TYPE,def_animation);
    MODULE.EEPROM_WRITE(eeprom,EEPROM_ADDR_DRL_STATE,def_drl_state);
    MODULE.EEPROM_WRITE(eeprom,EEPROM_ADDR_INT_STATE,def_int_state);
    MODULE.EEPROM_WRITE(eeprom,EEPROM_ADDR_AMP_STATE,def_amp_state);
    MODULE.EEPROM_WRITE(eeprom,EEPROM_ADDR_DVR_STATE,def_dvr_state);
    MODULE.EEPROM_WRITE(eeprom,EEPROM_ADDR_DRL_DELAY,drl_delay);
    MODULE.EEPROM_WRITE(eeprom,EEPROM_ADDR_INT_DELAY,int_delay);
    MODULE.EEPROM_WRITE(eeprom,EEPROM_ADDR_AMP_DELAY,amp_delay);
    MODULE.EEPROM_WRITE(eeprom,EEPROM_ADDR_DVR_DELAY,dvr_delay);
    MODULE.EEPROM_WRITE(eeprom,EEPROM_ADDR_INT_RED_VALUE,deff_r);
    MODULE.EEPROM_WRITE(eeprom,EEPROM_ADDR_INT_GREEN_VALUE,deff_g);
    MODULE.EEPROM_WRITE(eeprom,EEPROM_ADDR_INT_BLUE_VALUE,deff_b);
    MODULE.EEPROM_WRITE(eeprom,EEPROM_ADDR_INT_ANIMATION_SPEED,deff_anim_speed);
}
void handleSwitches() {
    if (server.arg("element") == "drl") {
        if (server.arg("val") == "on") {
            Serial.println("DRL switch to ON");
            drl_state = 1;
        }
        else if (server.arg("val") == "off") {
            Serial.println("DRL switch to OFF");
            drl_state = 0;
        }

        server.send(200, "text/html", "true");
    }
    if (server.arg("element") == "int") {
        if (server.arg("val") == "on") {
            Serial.println("INTERIOR switch to ON");
            int_state = 1;
        }
        else if (server.arg("val") == "off") {
            Serial.println("INTERIOR switch to OFF");
            int_state = 0;
        }
        server.send(200, "text/html", "true");
    }
    if (server.arg("element") == "amp") {
        if (server.arg("val") == "on") {
            Serial.println("AMP switch to ON");
            amp_state = 1;
        }
        else if (server.arg("val") == "off") {
            Serial.println("AMP switch to  OFF");
            amp_state = 0;
        }
        server.send(200, "text/html", "true");
    }
    if (server.arg("element") == "dvr") {
        if (server.arg("val") == "on") {
            Serial.println("DVR switch to ON");
            dvr_state = 1;
        }
        else if (server.arg("val") == "off") {
            Serial.println("DVR switch to OFF");
            dvr_state = 0;
        }
        server.send(200, "text/html", "true");
    }
    if(server.arg("element") == "animation"){
        curr_animation = server.arg("val").toInt();
        animation_changed = true;
    }
}
void serverClas::SETUP(){
   WiFi.softAP(ssid, password);
   IPAddress myIP = WiFi.softAPIP();
   Serial.print("AP IP address: ");
   Serial.println(myIP);
   server.on("/defaults", handleRoot);
   server.on("/switch", handleSwitches);
   server.on("/animation_setup",handleColors);
   //server.on("/get_current",handleCurrent);
   server.onNotFound(handleDefault);
   server.begin();
}

int f_run_period = 5000;
unsigned long time_now = 0;
void switch_pins(int pin_id,int indicator_id,int pin_state){
  digitalWrite(pin_id,pin_state);
  digitalWrite(indicator_id,pin_state);
}

// config delays
int drl_timer = (drl_delay * 1000 ) - 5000;
//drl_timer = drl_timer - 5000;
unsigned long drl_timer_now = 0;
int int_timer = (int_delay * 1000) - 5000;
//int_timer = int_timer - 5000;
unsigned long int_timer_now = 0;
int amp_timer = (amp_delay * 1000) - 5000;
//amp_timer = amp_timer - 5000;
unsigned long amp_timer_now = 0;
int dvr_timer = (dvr_delay * 1000) - 5000;
//dvr_timer = dvr_timer - 5000;
unsigned long dvr_timer_now = 0;

void delayedStart(){
  drl_timer_now = millis();
  int_timer_now = millis();
  amp_timer_now = millis();
  dvr_timer_now = millis();

  if(def_drl_state == 1){
    if(millis() < drl_timer_now + drl_timer){
      switch_pins(DRL_PIN,DRL_IND_PIN,1);
      last_drl_state = 1;
      drl_state = 1;
    }
  }

  if(def_int_state == 1){
    if(millis() < int_timer_now + int_timer){
      switch_pins(DASHBOARD_PIN,INT_IND_PIN,1);
      last_int_state = 1;
      int_state = 1;  
    }  
  }

  if(def_amp_state == 1){
    if(millis() < amp_timer_now + amp_timer){
      switch_pins(AMP_PIN,AMP_IND_PIN,1);
      last_amp_state = 1;
      amp_state = 1;  
    }  
  }

  if(def_dvr_state == 1){
    if(millis() < dvr_timer_now + dvr_timer){
      switch_pins(DVR_PIN,DVR_IND_PIN,1);
      last_dvr_state = 1;
      dvr_state = 1;
    }  
  }
}

void serverClas::LISTEN(){
  server.handleClient();
  if(f_run){
    time_now = millis();
    if(WiFi.status() == WL_CONNECTED){
      delayedStart();
      f_run = false;
    }else{
      if(millis() < time_now + f_run_period){
        // get states from eeprom
        def_animation = MODULE.EEPROM_GET(eeprom,EEPROM_ADDR_INT_DEEF_ANIMATION_TYPE);
        def_drl_state = MODULE.EEPROM_GET(eeprom,EEPROM_ADDR_DRL_STATE);
        def_int_state = MODULE.EEPROM_GET(eeprom,EEPROM_ADDR_INT_STATE);
        def_amp_state = MODULE.EEPROM_GET(eeprom,EEPROM_ADDR_AMP_STATE);
        def_dvr_state = MODULE.EEPROM_GET(eeprom,EEPROM_ADDR_DVR_STATE);
        // get delays
        drl_delay = MODULE.EEPROM_GET(eeprom,EEPROM_ADDR_DRL_DELAY);
        int_delay = MODULE.EEPROM_GET(eeprom,EEPROM_ADDR_INT_DELAY);
        amp_delay = MODULE.EEPROM_GET(eeprom,EEPROM_ADDR_AMP_DELAY);
        dvr_delay = MODULE.EEPROM_GET(eeprom,EEPROM_ADDR_DVR_DELAY);
        delayedStart();
        f_run = false;
      }  
    }  
  }
  // process changes here
  if(drl_state != last_drl_state){
    switch_pins(DRL_PIN,DRL_IND_PIN,drl_state);
    last_drl_state = drl_state;
  }
  if(int_state != last_int_state){
    switch_pins(DASHBOARD_PIN,INT_IND_PIN,int_state);
    last_int_state = int_state;  
  }
  if(amp_state != last_amp_state){
    switch_pins(AMP_PIN,AMP_IND_PIN,amp_state);
    last_amp_state = amp_state;  
  }
  if(dvr_state != last_dvr_state){
    switch_pins(DVR_PIN,DVR_IND_PIN,dvr_state);
    last_dvr_state = dvr_state;  
  }
  delay(100);
}


void serverClas::ANIMATE(){
  // get animation type
  // get eeprom data
  // call animation function
  if(int_state == 1 && animation_changed == true){
    // do animation here  
    int animation_type = MODULE.EEPROM_GET(eeprom,EEPROM_ADDR_INT_DEEF_ANIMATION_TYPE);
    switch(animation_type){
      case ANIMATION_TYPE_STATIC:
        ANIMATION.STATIC_COLOR();
      break;
      case ANIMATION_TYPE_PULSE_SIMPLE:
        ANIMATION.PULSE_COLOR();
      break;
      case ANIMATION_TYPE_PULSE:
        ANIMATION.PULSE_MULTIPLE_COLORS();
      break;
    }
    animation_changed = false;
  }
}
serverClas SERVER_CLAS = serverClas();
