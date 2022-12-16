#include <Arduino.h>
#include "SPI.h"
#include "HX711.h"
#include "SD.h"
#include "Force_Sensor.h"
#include "Speed_Sensor.h"
#include "string.h"
#include "Display_MCI.h"
#include "elapsedMillis.h"


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



//File myFile;
 
//HX711 bending_force;
//HX711 axial_force;

Force_Sensor test_bending;
Force_Sensor test_axial;

Speed_Sensor speed_sensor;


 
//Force_Sensor
double reading_bend = 0;
double reading_ax = 0;

//Speed_Sensor

double rpm_value = 0;
double load_cycles = 0; 



Display_MCI Display;
elapsedMillis time_test;


void setup() {
  Serial.begin(9600);
  
   pinMode(BUTTON, INPUT);

   test_bending.init(BEND_DOUT_PIN,BEND_SCK_PIN,GAIN);
   test_axial.init(AX_DOUT_PIN,AX_SCK_PIN,GAIN);

    Display.init_display();

}


void loop(void) {
  if (time_test>100){
  reading_bend = test_bending.get_force_value(slope_bend, offset_bend);
  reading_ax = test_axial.get_force_value(slope_ax, offset_ax);
  time_test = 0; 
  }

 rpm_value = speed_sensor.get_load_cycles(SPEED_DIN_PIN);
 //rpm_value = speed_sensor.get_rpm_value();

 
 
 Display.draw_display(reading_bend, reading_ax,rpm_value);

 

  
}

