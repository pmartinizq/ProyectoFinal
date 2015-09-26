#include "Config.h"
#ifndef _Motores_h
#define _Motores_h

#define PENDIENTE 30

uint16_t calculateValueRight=0,calculateValueLeft=0;
 uint16_t actualValueRight=0,actualValueLeft=0,lastValueRight=0,lastValueLeft=0;
 uint8_t lowValue=0;

void setPwmValue(int,int);


#endif