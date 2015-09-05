#include "Config.h"


#ifndef _SensoresUltraSonido_h
#define _SensoresUltraSonido_h



//Declaracion de constantes

#define MEF_STATUS_WAIT 0
#define MEF_STATUS_RUNNING 1
#define MEF_STATUS_ERROR 2








 
 

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


