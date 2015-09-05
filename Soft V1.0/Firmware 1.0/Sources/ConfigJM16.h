

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


//SENSORES
#define SENSOR_FRONT_TIMER_VALUE TPM1C0V
#define SENSOR_LEFT_TIMER_VALUE TPM1C1V
#define SENSOR_RIGHT_TIMER_VALUE TPM1C2V
#define SENSOR_BACK_TIMER_VALUE TPM1C3V

#define SENSOR_FRONT_ENABLE_INTERRUPT (TPM1C0SC_CH0IE=1)
#define SENSOR_FRONT_DISABLE_INTERRUPT (TPM1C0SC_CH0IE=0)

#define SENSOR_LEFT_ENABLE_INTERRUPT (TPM1C1SC_CH1IE=1)
#define SENSOR_LEFT_DISABLE_INTERRUPT (TPM1C1SC_CH1IE=0)

#define SENSOR_RIGHT_ENABLE_INTERRUPT (TPM1C2SC_CH2IE=1)
#define SENSOR_RIGHT_DISABLE_INTERRUPT (TPM1C2SC_CH2IE=0)

#define SENSOR_BACK_ENABLE_INTERRUPT (TPM1C3SC_CH3IE=1)
#define SENSOR_BACK_DISABLE_INTERRUPT (TPM1C3SC_CH3IE=0)


#define SENSOR_FRONT_TRIGGER PTGD_PTGD0
#define SENSOR_LEFT_TRIGGER PTGD_PTGD1
#define SENSOR_RIGHT_TRIGGER PTGD_PTGD2
#define SENSOR_BACK_TRIGGER PTGD_PTGD3

#define TIMER1_STATUS TPM1SC;

//MOTORES

#define SENTIDO_M1_1  PTGD_PTGD4
#define SENTIDO_M1_2  PTGD_PTGD5 
#define SENTIDO_M2_1  PTBD_PTBD4
#define SENTIDO_M2_2  PTBD_PTBD5
#define PWM_M1 PTFD_PTFD4
#define PWM_M2 PTFD_PTFD5

//SENSOR DE META

#define SENSOR_DE_META_ON PTBD_PTBD2=1
#define SENSOR_DE_META_OFF PTBD_PTBD2=0



#endif