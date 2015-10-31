#ifndef VELOCIDADANGULAR_H_
#define VELOCIDADANGULAR_H_

/*==================[inclusions]=============================================*/

#include "Linker.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

int robot_speed_to_pwm(
    int16_t tangential_speed,
    int16_t angular_speed,
    uint8_t* left_wheel_pwm,
    uint8_t* right_wheel_pwm );
    
void _robot_speed_to_wheel_speed(
    /* parametros */
    int16_t tangential_speed,
    int16_t angular_speed,
    int32_t *left_wheel_angular_speed,
    int32_t *right_wheel_angular_speed );

#endif // _VELOCIDAD_ANGULAR_H_
