#ifndef VELOCIDADANGULAR_H_
#define VELOCIDADANGULAR_H_

/*==================[inclusions]=============================================*/

#include "Linker.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

int robot_speed_to_pwm(
    int tangential_speed,
    int angular_speed,
    uint8_t* left_wheel_pwm,
    uint8_t* right_wheel_pwm );

#endif // _VELOCIDAD_ANGULAR_H_
