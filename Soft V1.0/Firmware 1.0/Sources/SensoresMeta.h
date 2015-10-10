#include "Config.h"

#ifndef _SensoresMeta_h
#define _SensoresMeta_h

//------------------DEFINICIONES---------------------------------

#define SENSOR_META_1 1
#define SENSOR_META_2 2
#define SENSOR_RUEDA_1 3
#define SENSOR_RUEDA_2 4




// -------------------VARIABLES-------------------------------------


static uint8_t sensorNumber=1;

static int varSensorLeft;
static int varSensorRight;
static int varSensorStepADC; 

static int varSensorLeftRef;
static int varSensorRightRef;
static int varSensorLeftRefMargin = 20;
static int varSensorRightRefMargin = 4;
int left;
int right;
int whileFlag;

int goalSensorStatus;

static int sensorStatus = 1;

static uint8_t lastStepValue=255;
static uint8_t stepsWheelADC;
static uint8_t diferencia;
static uint8_t signoPendiente,ultimoSigno=0,first=0;
FunctionStruct *adcFunctionStruct;

// -----------------FUNCIONES---------------------------------------

interrupt VectorNumber_Vadc void adcInterrupt (void);

void initSample(void);
void getAdcSample(FunctionStruct *);
void switchSensor(void);

/**
  @brief setea la reaccion al encontrar la meta. 

  @param mode es el modo de reaccionar al encontrar la meta.

  @returns void.

  */
void setGoalMode(int parameter, FunctionStruct* currentFunction);

void setSensorStatus(int parameter);

uint8_t getGoalRightStatus(void);

uint8_t getGoalLeftStatus(void);
uint8_t min=255,max=0,maximos[100],minimos[100],indice=0,indiceM=0,ultimoValor=0,pendientes[120],indice2=0;

void initGoalSensor(void);

#endif