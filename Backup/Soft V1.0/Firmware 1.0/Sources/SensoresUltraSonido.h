#include "Config.h"


#ifndef _SensoresUltraSonido_h
#define _SensoresUltraSonido_h
#endif



//Declaracion de constantes

#define MEF_STATUS_WAIT 0
#define MEF_STATUS_RUNNING 1
#define MEF_STATUS_ERROR 2

#define MEASURE_STATUS_DONE 3
#define MEASURE_STATUS_RUNNING 4
#define MEASURE_STATUS_WAIT 5
#define MEASURE_STATUS_ERROR 6

#define TIMER1_CH0_VALUE TPM1C0V
#define TIME1_CH0_ENABLE_INTERRUPT (TPM1C0SC_CH0IE=1)
#define TIME1_CH0_DISABLE_INTERRUPT (TPM1C0SC_CH0IE=0)
#define SENSOR_FRONT_TRIGGER PTED_PTED4

 
 //Declaracion de variables
uint8_t firstTimeInterruptCh0;
uint8_t mefStatus=0;
uint8_t measureCh0Status=0;
uint16_t ch0Time,risingEdgeTime,fallingEdgeTime;
FunctionStruct* ch0FunctionStruct;
DataStruct ch0Datos;

//Declaracion de funciones
void Sensor1(FunctionStruct* currentFunction);
interrupt VectorNumber_Vtpm1ch0 void InterruptChannel0 (void);

