#ifndef Speed_Sensor_h
#define Speed_Sensor_h

#include "string.h"
#include <Arduino.h>
#include "Tachometer.h"



class Speed_Sensor
{
private: 

public:

    

    int get_rpm_value(byte DIN);

    int get_load_cycles();

};




#endif