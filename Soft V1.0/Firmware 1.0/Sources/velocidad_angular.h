#include "Config.h"
#ifndef _VELOCIDAD_ANGULAR_H_
#define _VELOCIDAD_ANGULAR_H_


int robot_speed_to_pwm(
    int tangential_speed,
    int angular_speed,
    uint8_t* left_wheel_pwm,
    uint8_t* right_wheel_pwm);



#endif // _VELOCIDAD_ANGULAR_H_
