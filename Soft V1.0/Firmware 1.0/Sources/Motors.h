#ifndef MOTORS_H
#define MOTORS_H

/*==================[inclusions]=============================================*/

#include "Linker.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/**
	@brief establece el valor del PWM calculando el duty cicle del mismo. 
	@param valueToSetRight representa un valor entre 0 y 255 estableciendo el duty de
	la rueda derecha.
	@param valueToSetLeft representa un valor entre 0 y 255 estableciendo el duty de
	la rueda izquierda.
	@return void
*/
void setPwmValue(int,int);

/**
	@brief calcula el sentido del giro de la rueda.
	@param parametro que representa el sentido de las ruedas.
	@return void
*/
void calcularSentido(int);

/**
	@brief establece valor 0 en la velocidad de la rueda izquierda,
	haciendo que la misma se detenga.
*/
void stopLeftWheel(void);

/**
	@brief establece valor 0 en la velocidad de la rueda derecha,
	haciendo que la misma se detenga.
*/
void stopRightWheel(void);

#endif