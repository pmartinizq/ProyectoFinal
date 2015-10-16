#include "RTCmodule.h"


interrupt VectorNumber_Vrtc   void RTCInterrupt (void){
unsigned long long velocidadAux=0,velocidadAux1=0;
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

  
  velocidadAux=diferencia;
  velocidadAux1=(diferencia*58)/10;
  velocidadAux1=(velocidadAux1*10);
  velocidad=velocidadAux1;
  /*
  velocidadAux=9*diferencia;
  velocidadAux=10000*velocidadAux;
  velocidad=velocidadAux/3125;*/
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
 
 
 

if((adcTime>=adcSampleFreq)&&isAdcRunning!=1){
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
