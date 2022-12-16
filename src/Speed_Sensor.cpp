#include "Speed_Sensor.h"
#include "SPI.h"


int count_value = 0;
int rpms = 0;  

Tachometer tacho;

void pin_ISR() {
   tacho.tick();
   count_value++;
}

int Speed_Sensor::get_rpm_value(byte DIN)
{
attachInterrupt(DIN,pin_ISR,RISING); 
static uint32_t tmr;
  if (millis() - tmr > 100) {
    tmr = millis();
  rpms = tacho.getRPM(); 
  }
return rpms;            
}

int Speed_Sensor::get_load_cycles()
{
//attachInterrupt(DIN,pin_ISR,RISING); 
return count_value;            
}




