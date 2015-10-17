#ifndef RTCMODULE_H
#define RTCMODULE_H
/*==================[inclusions]=============================================*/

#include "Linker.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/**
	@brief decrementa los timer de las funciones que estan en el vector de ejecucion
		y habilita el ADC cuando el contador del ADC llega a cierto valor.
*/
interrupt VectorNumber_Vrtc   void RTCInterrupt (void);

#endif