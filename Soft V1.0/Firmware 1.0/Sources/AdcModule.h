

#ifndef ADCMODULE_H
#define ADCMODULE_H


/*==================[inclusions]=============================================*/

#include "Linker.h"

/*==================[macros]=================================================*/




/*==================[typedef]================================================*/


/*==================[external data declaration]==============================*/



/*==================[external functions declaration]=========================*/




interrupt VectorNumber_Vadc void adcInterrupt (void);


extern void switchSensor(void);

/**
  @brief setea la reaccion al encontrar la meta. 

  @param mode es el modo de reaccionar al encontrar la meta.

  @returns void.

  */
extern void setGoalMode(int parameter, FunctionStruct* currentFunction);

extern void initGoalSensor(void);



#endif