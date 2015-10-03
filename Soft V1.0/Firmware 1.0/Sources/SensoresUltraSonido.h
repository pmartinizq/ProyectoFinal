#include "Config.h"


#ifndef _SensoresUltraSonido_h
#define _SensoresUltraSonido_h



//Declaracion de constantes

#define MEF_STATUS_WAIT 0
#define MEF_STATUS_RUNNING 1
#define MEF_STATUS_ERROR 2

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






 
 

//Declaracion de variables para Sensor Frente
uint8_t mefSensorFrontStatus=0;
uint16_t sensorFrontTime,risingEdgeTimeSensorFront,fallingEdgeTimeSensorFront,measureSensorFront16;
FunctionStruct* sensorFrontFunctionStruct;
DataStruct sensorFrontDatos;

//Declaracion de variables para Sensor Izquierdo
uint8_t mefSensorLeftStatus=0;
uint16_t sensorLeftTime,risingEdgeTimeSensorLeft,fallingEdgeTimeSensorLeft,measureSensorLeft16;
FunctionStruct* sensorLeftFunctionStruct;
DataStruct sensorLeftDatos;

//Declaracion de variables para Sensor Derecho
uint8_t mefSensorRightStatus=0;
uint16_t sensorRightTime,risingEdgeTimeSensorRight,fallingEdgeTimeSensorRight,measureSensorRight16;
FunctionStruct* sensorRightFunctionStruct;
DataStruct sensorRightDatos;

//Declaracion de funciones
interrupt VectorNumber_Vtpm1ch0 void interruptSensorFront (void);
interrupt VectorNumber_Vtpm1ch1 void interruptSensorLeft (void);
interrupt VectorNumber_Vtpm1ch2 void interruptSensorRight (void);
void getUltrasonic(FunctionStruct* currentFunction);                       
void triggerDelay(void);

#endif


