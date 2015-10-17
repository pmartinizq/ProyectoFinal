


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
extern uint16_t leftWheelVelocity,rightWheelVelocity;


//Motores
extern uint8_t pwmLeftValue,pwmRightValue;

//Tipo de movimiento
extern uint8_t moveBy;


// IDnumber
extern uint8_t IDNumberExtern;


///PASOS
extern uint16_t leftWheelStepValue,rightWheelStepValue;
extern int leftWheelStepValueToSet,rightWheelStepValueToSet; 


/*==================[external functions declaration]=========================*/
extern void initIDNumber(void);
extern uint8_t getIDNumber();

#endif
