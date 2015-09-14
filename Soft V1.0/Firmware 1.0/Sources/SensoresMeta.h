#include "Config.h"

#ifndef _SensoresMeta_h
#define _SensoresMeta_h

static uint8_t sensorNumber=1;

static int varSensorLeft;
static int varSensorRight; 

static int varSensorLeftRef;
static int varSensorRightRef;
static int varSensorLeftRefMargin = 20;
static int varSensorRightRefMargin = 4;
int left;
int right;
int whileFlag;

int goalSensorStatus;

/* 1 si debo leer datos del sensor
   0 si no. */
static int sensorStatus = 1;

interrupt VectorNumber_Vadc void adcInterrupt (void);

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

void initGoalSensor(void);

#endif