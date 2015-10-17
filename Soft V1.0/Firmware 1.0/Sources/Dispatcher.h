#ifndef DISPACHER_H
#define DISPACHER_H

/*==================[inclusions]=============================================*/

#include "Linker.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/**
	@brief Atiende al vector de ejecucion y envia al buffer de salida las funciones que 
	esten listas para ser enviadas. Realiza control de error.
	@param executingVector puntero al vector de ejecucion.
	@param functionBuffer buffer en donde envia la funcion a ser enviada.
	@return void
*/
extern void dispatcher(ExecutingStruct* executingVector, BufferStruct* functionBuffer);

#endif