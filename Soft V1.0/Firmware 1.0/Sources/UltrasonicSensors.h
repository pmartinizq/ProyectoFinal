


#ifndef ULTRASONICSENSORS_H
#define ULTRASONICSENSORS_H

/*==================[inclusions]=============================================*/

#include "Linker.h"

/*==================[macros]=================================================*/




/*==================[typedef]================================================*/


/*==================[external data declaration]==============================*/



/*==================[external functions declaration]=========================*/

interrupt VectorNumber_Vtpm1ch0 void interruptSensorFront (void);
interrupt VectorNumber_Vtpm1ch1 void interruptSensorLeft (void);
interrupt VectorNumber_Vtpm1ch2 void interruptSensorRight (void);
extern void getUltrasonic(FunctionStruct* currentFunction);

                      


#endif


