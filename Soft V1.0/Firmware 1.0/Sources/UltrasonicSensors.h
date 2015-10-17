#ifndef ULTRASONICSENSORS_H
#define ULTRASONICSENSORS_H

/*==================[inclusions]=============================================*/

#include "Linker.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/**
  @brief Rutina de interrupcion que calcula la distancia del
   sensor ultrasonico frontal.

  */
interrupt VectorNumber_Vtpm1ch0 void interruptSensorFront (void);

/**
  @brief Rutina de interrupcion que calcula la distancia del
   sensor ultrasonico izquierdo.

  */
interrupt VectorNumber_Vtpm1ch1 void interruptSensorLeft (void);

/**
  @brief Rutina de interrupcion que calcula la distancia del
   sensor ultrasonico derecho.

  */
interrupt VectorNumber_Vtpm1ch2 void interruptSensorRight (void);

/**
  @brief determina a partir de la funcion que se pasa por parametro, 
  que interrupcion debe llamar.
	
  @param currentFunction es un puntero a la funcion en el vector de ejecucion.

  @return void
  */
extern void getUltrasonic(FunctionStruct* currentFunction);

#endif


