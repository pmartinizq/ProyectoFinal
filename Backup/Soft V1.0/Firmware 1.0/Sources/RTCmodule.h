#include "Config.h"
#ifndef _RTCmodule_h
#define _RTCmodeule_h

#endif

interrupt VectorNumber_Vrtc   void RTCInterrupt (void);


uint8_t timeCounter;
uint16_t time;


//Definicion de funciones
void decreaseTimer(FunctionStruct*);