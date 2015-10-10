
#ifndef _Motores_h
#define _Motores_h

#include "Config.h"

#define PENDIENTE 10
#define robotAdelante 0x00
#define robotAtras 0x03
#define robotGiroDerecha 0x01
#define robotGiroIzquierda 0x02

uint16_t calculateValueRight=0,calculateValueLeft=0;
 uint16_t actualValueRight=0,actualValueLeft=0,lastValueRight=0,lastValueLeft=0;
 uint8_t lowValue=0;

void setPwmValue(int,int);
void calcularSentido(int);


#endif