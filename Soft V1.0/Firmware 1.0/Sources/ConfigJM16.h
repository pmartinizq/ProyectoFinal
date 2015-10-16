



#ifndef CONFIGJM16_H
#define CONFIGJM16_H

/*==================[inclusions]=============================================*/

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */



/*==================[macros]=================================================*/

//COMUNICACION
#define serialData SCI1D
#define clockRegister(x,y) (y=SCI1BDL,x=SCI1BDH)
#define enableTxInterrupt (SCI1C2_TCIE=1)
#define enableRxInterrupt (SCI1C2_RIE=1)
#define disableTxInterrupt (SCI1C2_TCIE=0)
#define disableRxInterrupt (SCI1C2_RIE=0)
#define statusSerialRegister1 SCI1S1
#define statusSerialRegister2 SCI1S2

//VALORES DE PWM

#define PWM_FREQ_HIGH 0x09
#define PWM_FREQ_LOW 0xC4
#define PWM_CH0_CONFIG 0B00111000
#define PWM_CH1_CONFIG 0B00111000


//MOTORES

#define SENTIDO_M1_1  PTGD_PTGD4
#define SENTIDO_M1_2  PTGD_PTGD5 
#define SENTIDO_M2_1  PTBD_PTBD4
#define SENTIDO_M2_2  PTBD_PTBD5


//SENSOR DE META

#define SENSOR_DE_META_ON PTBD_PTBD2=1
#define SENSOR_DE_META_OFF PTBD_PTBD2=0


/*==================[typedef]================================================*/


/*==================[external data declaration]==============================*/



/*==================[external functions declaration]=========================*/


void InitDevice(void);






#endif