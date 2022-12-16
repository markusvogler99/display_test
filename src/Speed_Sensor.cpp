#include "Speed_Sensor.h"
#include "SPI.h"

double temp_variable = 0; 

volatile int buttonState = 0; 
int count_value = 0;
int prestate = 0;
elapsedMillis rpm_counter; 

double oldtime = 0;
double newtime = 0; 
double time = 0;
double rpm = 0;  



void pin_ISR() {
    count_value++;
}

int Speed_Sensor::get_load_cycles(byte DIN)
{
attachInterrupt(DIN,pin_ISR,RISING); 
//newtime = rpm_counter; 
//time=newtime-oldtime;        
//rpm=(count_value/time)*60000;         
//oldtime=rpm_counter;
//count_value=0; 
return count_value;            
}




