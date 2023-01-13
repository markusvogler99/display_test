#include "Speed_Sensor.h"

 volatile int count_value = 0;
    int rpms = 0;
    Tachometer tacho;
    int oldtime = 0; 
    int rpm = 0; 
    unsigned long tmr= 0;
    int time = 0;
    int temp = 0; 
    int old_count_value = 0;

   unsigned long RPM_T1 = 0;                                       // Setzen der Zeitvariable T1

    unsigned long RPM_T2 = 0;                                       // Setzen der Zeitvariable T2

    unsigned long RPM_Count = 0;    
    unsigned long RPM = 0; 

    elapsedMillis timer; 
 

void pin_ISR() {
   //tacho.tick();
   RPM_Count++;
   RPM_T2 = timer;
}

void Speed_Sensor::attach_interrupt(byte DIN) {
  attachInterrupt(DIN, pin_ISR, RISING);
}


 unsigned long  Speed_Sensor::get_rpm_value()
{
  
  if (RPM_T2 > RPM_T1) {
    RPM = (unsigned)(long)((60/1000) *(RPM_T2 - RPM_T1));
     return RPM;
    RPM_T1 = RPM_T2;
    RPM_Count = 0;

    }

  else {                                            // Abfangen von Drehzahl = 0 

      RPM = 0;
      return RPM ; 

    }

 


              
}

int Speed_Sensor::get_load_cycles()
{
  return RPM_Count;            
}




