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
double test_variable = 0; 

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

//Pins definieren für die Hx711, an denen die Kraftsensoren hängen 
const int BEND_DOUT_PIN = 2;
const int BEND_SCK_PIN = 3;

const int AX_DOUT_PIN = 6;
const int AX_SCK_PIN = 20;

const int GAIN = 128; 

//Pin für Speed Sensor 
const int SPEED_DIN_PIN = 5; 

//Definition der Kalibrierdaten für die beiden Kraftsensoren 
const double slope_bend = 0.000111688; 
const double offset_bend = 1.05;

const double slope_ax = 0.0001; 
const double offset_ax = 1;

const int BUTTON = 5;

int counter = 0; 
int column = 0;

int test = 0; 

Tachometer tacho;

int rpms = 0;

//Force_Sensor bending
Force_Sensor bending_sensor;
double reading_bend = 0;

//Force_Sensor axial
Force_Sensor axial_sensor;
double reading_ax = 0;

//Speed_Sensor
Speed_Sensor speed_sensor;
double rpm_value = 0;
int load_cycles = 0;


Display_MCI Display;
elapsedMillis time_test;
elapsedMillis time_test_2;

void attached(){
  load_cycles++;
  tacho.tick();
}


void setup() {
  Serial.begin(9600);
  
   pinMode(1, INPUT_PULLDOWN);
   pinMode(14, OUTPUT);
   digitalWrite(14, LOW);

   bending_sensor.init(BEND_DOUT_PIN,BEND_SCK_PIN,GAIN);
   axial_sensor.init(AX_DOUT_PIN,AX_SCK_PIN,GAIN);
   Display.init_display();
   //speed_sensor.attach_interrupt(BUTTON);

    attachInterrupt(digitalPinToInterrupt(1),attached,RISING);
    
}


void loop(void) {
  if (time_test>1000){
  reading_bend = bending_sensor.get_force_value(slope_bend, offset_bend);
  reading_ax = axial_sensor.get_force_value(slope_ax, offset_ax);
  //Serial.printf("%d\n",load_cycles);
  Serial.println(load_cycles);
  time_test = 0; 
  }

  //load_cycles = speed_sensor.get_load_cycles(); 
  //rpm_value = speed_sensor.get_rpm_value();

  static uint32_t tmr;
  if (millis() - tmr > 100) {
    tmr = millis();
  rpms = tacho.getRPM(); 
  }

  
  if (time_test_2>1000){
    
    test_variable = test_variable + 1000;
    if (test_variable > 5000)
    {
     test_variable = 0;
    } 
      time_test_2 = 0; 
 }

  Display.draw_tacho(test_variable);

 
test = load_cycles; 
//detachInterrupt(37);

 Display.draw_display(reading_bend, reading_ax,rpms,test);
  //Serial.println(load_cycles);
}

