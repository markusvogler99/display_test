#include <Arduino.h>
#include "SPI.h"
#include "HX711.h"
#include "SD.h"
#include "Force_Sensor.h"
#include "Speed_Sensor.h"
#include "string.h"
#include "Display_MCI.h"
#include "elapsedMillis.h"
#include "Tachometer.h"
#include "TouchScreen.h"


// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

#define YP 24  // must be an analog pin, use "An" notation!
#define XM 27  // must be an analog pin, use "An" notation!
#define YM 26   // can be a digital pin
#define XP 25   // can be a digital pin

//Pins definieren für die Hx711, an denen die Kraftsensoren hängen 
const int BEND_DOUT_PIN = 2;
const int BEND_SCK_PIN = 3;

const int AX_DOUT_PIN = 6;
const int AX_SCK_PIN = 20;

const int GAIN = 128; 

//Pin für Speed Sensor 

const int SPEED_SENSOR = 5;

// Pin für MOTOR_AUS
const int MOTOR_AUS = 14;
const int MOTOR_EIN = 8;


//Force_Sensor bending
Force_Sensor bending_sensor;
double reading_bend = 0;
const double slope_bend = 0.000111688; 
const double offset_bend = 1.05;

//Force_Sensor axial
Force_Sensor axial_sensor;
double reading_ax = 0;
const double slope_ax = 0.0001; 
const double offset_ax = 1;

//Speed_Sensor
Speed_Sensor speed_sensor;
double rpm_value = 0;
int load_cycles = 0;

//Touch
bool motor_continue= false;
bool motor_stop= false;

//State Machine
int state = 0; 
bool motor_aus = false; 
bool motor_ein = false; 



Display_MCI Display;
elapsedMillis time_force_sensors;
elapsedMillis time_test_2;
TouchScreen ts = TouchScreen(YP, XP, YM, XM, 300);


void setup() {
  Serial.begin(9600);
  
   pinMode(SPEED_SENSOR, INPUT_PULLDOWN);
   pinMode(MOTOR_AUS, OUTPUT);
   

   bending_sensor.init(BEND_DOUT_PIN,BEND_SCK_PIN,GAIN);
   axial_sensor.init(AX_DOUT_PIN,AX_SCK_PIN,GAIN);
   Display.init_display();
   speed_sensor.attach_interrupt(SPEED_SENSOR);
    
}


void loop(void) {

switch (state)
{
  case 0:
  load_cycles = 0;
  digitalWrite(MOTOR_AUS,LOW);
 
  if (digitalRead(MOTOR_EIN) == HIGH)
  {
    state = 1; 
  }
  break; 



  case 1:



  
  break; 




  case 2:
  break; 

  case 3:
  break; 

  

  case 4:
  break; 



}








  if (time_force_sensors>100){
  reading_bend = bending_sensor.get_force_value(slope_bend, offset_bend);
  reading_ax = axial_sensor.get_force_value(slope_ax, offset_ax);
  time_force_sensors = 0; 
  }

  load_cycles = speed_sensor.get_load_cycles(); 
  rpm_value = speed_sensor.get_rpm_value();




  //Serial.println(rpm_value);

  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  if (p.z > ts.pressureThreshhold and p.x < 325 and p.y > 760) {
    motor_continue = true;
     Serial.print("\tWeiter = "); Serial.println(motor_continue);}
  else if (p.z > ts.pressureThreshhold and p.x > 677 and p.y > 760) {
    motor_stop = true;
     Serial.print("\tStop = "); Serial.println(motor_stop);
  }
  else {
  motor_continue = false;
  motor_stop = false; 
  }

  delay(100);

  

 //Display.draw_tacho(rpm_value);

 Display.draw_display(reading_bend, reading_ax,rpm_value,load_cycles);
 
}
