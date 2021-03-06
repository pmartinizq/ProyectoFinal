#ifndef CONFIGMICRO_H
#define CONFIGMICRO_H

/*==================[inclusions]=============================================*/

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "stdint.h"
/*==================[macros]=================================================*/

//VALORES DE PWM

#define PWM_FREQ_HIGH 0x09
#define PWM_FREQ_LOW 0xC4
#define PWM_CH0_CONFIG 0B00111000
#define PWM_CH1_CONFIG 0B00111000

//SENSOR DE META

#define SENSOR_DE_META_ON PTBD_PTBD2=1
#define SENSOR_DE_META_OFF PTBD_PTBD2=0


//-------------------FUSES-------------//

#define PARITY_CHECK
#define FRAMMING_CHECK


/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/

/**
  @brief ejecuta todas las rutinas de inicializacion necesarias. 

  @returns void.

  */
void InitDevice(void);

#endif