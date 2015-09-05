

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */


#ifndef _ConfigJM16_h
#define _ConfigJM16_h

//Declaraciones

#define serialData SCI1D
#define clockRegister(x,y) (y=SCI1BDL,x=SCI1BDH)
#define enableTxInterrupt (SCI1C2_TCIE=1)
#define enableRxInterrupt (SCI1C2_RIE=1)
#define disableTxInterrupt (SCI1C2_TCIE=0)
#define disableRxInterrupt (SCI1C2_RIE=0)
#define statusSerialRegister1 SCI1S1
#define statusSerialRegister2 SCI1S2

//Funciones
void InitComunication(void);
void InitClock(void);
void InitReg(void);
void InitInputCompare(void);
void InitPorts(void);
void InitRtc(void);


#endif