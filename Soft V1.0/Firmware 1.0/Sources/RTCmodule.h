#include "Config.h"
#ifndef _RTCmodule_h
#define _RTCmodeule_h



interrupt VectorNumber_Vrtc   void RTCInterrupt (void);


uint8_t timeCounter;
uint16_t kbiTime,adcTime;


//Definicion de funciones
void decreaseTimer(FunctionStruct*);

#endif