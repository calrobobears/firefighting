/* This is the main control systems code
 */
#ifndef CONTROLS
#define CONTROLS

#include "data_structures.h"

//update control outputs
void update_controls()
{
    
}

//This is a simple example on how to use the update functions
void example_procedure(real target)
{
    sensors.encoder1 = 0;

    real K_p = 0.13;
    
    while(abs(sensors.encoder1-target) > 0.1)
    {
        update_sensors();
        motors.left = motors.right = K_p*(sensors.encoder1-target);
        update_controls();
    }
    
    motors.left = motors.right = 0;
    update_controls();
}

#endif //CONTROLS
