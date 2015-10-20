#ifndef GLOBALVARIABLES_H_
#define GLOBALVARIABLES_H_

/*==================[inclusions]=============================================*/

#include "Configuration.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

//ADC

extern Bool adcEnable;
extern Bool isAdcRunning;

//Velocidad

extern uint16_t leftWheelVelocity;
extern uint16_t rightWheelVelocity;

//Motores

extern uint8_t pwmLeftValue;
extern uint8_t pwmRightValue;

//Tipo de movimiento

extern uint8_t moveBy;

//IDnumber

extern uint8_t IDNumberExtern;

//Pasos

extern uint16_t leftWheelStepValue;
extern uint16_t rightWheelStepValue;
extern int leftWheelStepValueToSet;
extern int rightWheelStepValueToSet; 

//Serial Port

extern uint8_t serialErrorType;

/*==================[external functions declaration]=========================*/

/**
  @brief Inicializa la variable que representa el ID de las funciones
  dentro del vector de ejecucion.

  @returns void

  */
extern void initIDNumber(void);

/**
  @brief genera un nuevo ID para ser asignado a las funciones que ingresan
  al vector de ejecucion.

  @returns void

  */
extern uint8_t getIDNumber();

/**
  @brief inicializa las variables globales;

  @returns void

  */
void initGlobalVariables(void);
#endif