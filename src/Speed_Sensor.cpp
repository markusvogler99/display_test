#include "Speed_Sensor.h"

 
 

void Speed_Sensor::pin_ISR() {
   tacho.tick();
   count_value++;
}

//void Speed_Sensor::attach_interrupt(byte DIN) {
  //attachInterrupt(DIN, pin_ISR, RISING);
//}


int Speed_Sensor::get_rpm_value()
{
//attachInterrupt(5,pin_ISR,RISING); 
static uint32_t tmr;
  if (millis() - tmr > 100) {
    tmr = millis();
  rpms = tacho.getRPM(); 
  }
return rpms;            
}

int Speed_Sensor::get_load_cycles()
{
  return count_value;            
}




