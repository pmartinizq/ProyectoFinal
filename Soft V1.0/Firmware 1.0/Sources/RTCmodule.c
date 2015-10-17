
/*==================[inclusions]=============================================*/
#include "RTCmodule.h"

/*==================[macros and definitions]=================================*/

#define VELOCITY_MEASSURE_FREQ 12000


/*==================[internal data declaration]==============================*/

uint8_t timeCounter;
uint16_t kbiTime,adcTime;
uint16_t velocityMeassureTimer;
uint16_t diferencia; 
uint8_t lastStatus;
uint16_t lastPasos=0;

/*==================[internal functions declaration]=========================*/


void decreaseTimer(FunctionStruct*);


/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/


/*==================[external functions definition]==========================*/



/*==================[internal functions definition]==========================*/

interrupt VectorNumber_Vrtc   void RTCInterrupt (void){
unsigned long long leftWheelVelocityAux=0,leftWheelVelocityAux1=0;
uint8_t i=0;

static calibrar,apagar=0;
RTCSC_RTIF=1;
RTCMOD=0x00;
//tickTime++;
adcTime++;
velocityMeassureTimer++;


 
if(velocityMeassureTimer==VELOCITY_MEASSURE_FREQ){
  
  
  velocityMeassureTimer=0;
  diferencia=(leftWheelStepValue-lastPasos);
 /* 
  calibrar++;
  if(calibrar==10){
    calibrar=0;
    if(apagar==1){
      setPwmValue(0,0);
    }else{
      
      setPwmValue(pwmRightValue,pwmLeftValue);
      apagar=1;
    }
  }*/

  
  leftWheelVelocityAux=diferencia;
  leftWheelVelocityAux1=(diferencia*58)/10;
  leftWheelVelocityAux1=(leftWheelVelocityAux1*10);
  leftWheelVelocity=leftWheelVelocityAux1;
  /*
  leftWheelVelocityAux=9*diferencia;
  leftWheelVelocityAux=10000*leftWheelVelocityAux;
  leftWheelVelocity=leftWheelVelocityAux/3125;*/
  lastPasos=leftWheelStepValue;
  
  
}
 



/*
if(STATUS_MEF==lastStatus){
   STATUS_MEF=MEF_WAIT; 
  
}
lastStatus=STATUS_MEF;*/


for(i=0;i<=getExecutingVectorPointer();i++){
  decreaseTimer(getFromExecutingVectorOnIndex(i));
     
      
 }
 
 
 

if((adcTime>=ADC_SAMPLE_FREQUENCY)&&isAdcRunning!=1){
  adcEnable=TRUE;
  adcTime=0;
  isAdcRunning=0;
} 
  
}

void decreaseTimer(FunctionStruct* currentFunction){
  
  if(currentFunction->timerCount!=NO_TIMER){
    
    if((currentFunction->status==RUNNING)&&(currentFunction->timerCount==0)){
          currentFunction->status=TIMEOUT;
          
    } 
   if((currentFunction->status==READY)&&(currentFunction->timerCount==0)){
         currentFunction->status=INACCESSIBLE_DEVICE;
    }
    if((currentFunction->status==RUNNING)||(currentFunction->status==READY&&currentFunction->timerCount>0)){
          currentFunction->timerCount--;
     } 
  }
   
}
