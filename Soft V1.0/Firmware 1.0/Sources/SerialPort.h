#ifndef SERIALPORT_H_
#define SERIALPORT_H_

/*==================[inclusions]=============================================*/

#include "Linker.h"

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

extern uint8_t STATUS_MEF;

/*==================[external functions declaration]=========================*/

/**
  @brief Rutina de interrupcion que envia los datos.
*/
interrupt VectorNumber_Vsci1rx  void RxInterrupt (void);

/**
  @brief Rutina de interrupcion que recibe los datos.
*/
interrupt VectorNumber_Vsci1tx  void TxInterrupt (void);

/**
  @brief Borra los flags de interrupcion.
*/
interrupt VectorNumber_Vsci1err  void ErrorInterrupt (void);

/**
  @brief Envia una trama de datos por el puerto serial obtenida por el buffer de salida
  @param dato byte a ser enviado
*/
extern void frameGenerator(void);

#endif

