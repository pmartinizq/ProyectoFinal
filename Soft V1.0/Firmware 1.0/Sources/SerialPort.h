
#ifndef SERIALPORT_H_
#define SERIALPORT_H_

/*==================[inclusions]=============================================*/

#include "Linker.h"




/*==================[macros]=================================================*/

/*==================[typedef]================================================*/


/*==================[external data declaration]==============================*/

extern uint8_t STATUS_MEF;

/*==================[external functions declaration]=========================*/


interrupt VectorNumber_Vsci1rx  void RxInterrupt (void);
interrupt VectorNumber_Vsci1tx  void TxInterrupt (void);
interrupt VectorNumber_Vsci1err  void ErrorInterrupt (void);


extern void frameGenerator(void);

#endif

