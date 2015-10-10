
#ifndef _RTCmodule_h_
#define _RTCmodeule_h_
#include "Config.h"



interrupt VectorNumber_Vrtc   void RTCInterrupt (void);

#define VELOCITY_MEASSURE_FREQ 10000

uint8_t timeCounter;
uint16_t kbiTime,adcTime;
uint16_t velocityMeassureTimer; 


//Definicion de funciones
void decreaseTimer(FunctionStruct*);

#endif