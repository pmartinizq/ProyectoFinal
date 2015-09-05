#include "Config.h"


#ifndef _SensoresMeta_h
#define _SensoresMeta_h

static uint8_t varSensor1; 
static uint8_t varSensor2;
interrupt VectorNumber_Vadc void adcInterrupt (void);

void switchSensor(void);

#endif