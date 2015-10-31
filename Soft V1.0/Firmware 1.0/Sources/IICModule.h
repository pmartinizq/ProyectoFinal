#ifndef IICMODULE_H
#define IICMODULE_H


/*==================[inclusions]=============================================*/
//#include "Linker.h"
#include <stdint.h>
#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

/*==================[macros]=================================================*/


/*==================[typedef]================================================*/


/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/


extern void IICReadByte(byte,byte,byte*);
extern void IICReadNBytes(byte,byte,byte,byte*);
extern void IICWriteRegister(byte,byte,byte);
extern void IICWriteBit(uint8_t,uint8_t,uint8_t,Bool);
extern void IICWriteBits(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);

/*==================[end of file]============================================*/
#endif /* #ifndef TEMPLATE_FILE_H */