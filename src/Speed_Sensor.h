#ifndef Speed_Sensor_h
#define Speed_Sensor_h

#include "string.h"
#include <Arduino.h>


class Speed_Sensor
{
private: 

public:

    

    int get_load_cycles(byte DIN);

    int get_rpm_value();

};




#endif