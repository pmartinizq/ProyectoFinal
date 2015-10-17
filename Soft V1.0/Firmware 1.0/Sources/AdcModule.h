#ifndef ADCMODULE_H
#define ADCMODULE_H

/*==================[inclusions]=============================================*/

#include "Linker.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/**
  @brief rutina de interrupcion de ADC. Toma la medicion de los sensores infrarrojos 
 	(sensores de meta y sensores de ruedas).
  
  @return void
  */
interrupt VectorNumber_Vadc void adcInterrupt (void);

/**
  @brief intercambia los canales del ADC para realizar las diferentes medidas de los sensores.
  
  @return void
  */
extern void switchSensor(void);

/**
  @brief setea la reaccion al encontrar la meta. 

  @param mode es el modo de reaccionar al encontrar la meta.

  @returns void.

  */
extern void setGoalMode(int parameter, FunctionStruct* currentFunction);

/**
  @brief inicializa la variable global 'goalSensor' que persiste el ultimo valor medido
  del estado del sensor de meta. 

  @returns void.

  */
extern void initGoalSensor(void);

#endif