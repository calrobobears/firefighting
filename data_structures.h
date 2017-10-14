/* This defines the interface between the control and sensors systems
 */

#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES

#include "maths.h"

//NOTE(Kyler): these entries are placeholder until we have a better idea of our sensors/hardware capabilities

//robot inputs
struct sensor_data
{
    real encoder1;
};

//robot outputs
struct motor_data
{
    real left;
    real right;
    bool extinguisher;
};

sensor_data sensors;
motor_data motors;

#endif //DATA_STRUCTURES
