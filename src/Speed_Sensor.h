#ifndef Speed_Sensor_h
#define Speed_Sensor_h

#include "string.h"
#include <Arduino.h>
#include "Tachometer.h"



class Speed_Sensor
{
private: 

    volatile int count_value = 0;
    int rpms = 0;
    Tachometer tacho;

public:

    //void attach_interrupt(byte DIN);

    int get_rpm_value();

    int get_load_cycles();

    void pin_ISR();

};




#endif