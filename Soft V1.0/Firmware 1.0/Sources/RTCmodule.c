#include "RTCmodule.h"


interrupt VectorNumber_Vrtc   void RTCInterrupt (void){
long velocidad=0;
uint8_t i=0;
uint8_t lastStatus;
RTCSC=RTCSC|0x80;
tickTime++;
adcTime++;
velocityMeassureTimer++;



 /*
if(velocityMeassureTimer==VELOCITY_MEASSURE_FREQ){
  velocityMeassureTimer=0;
  velocidad=(3125*(9*stepsWheelADC));
  
  
}
  */

/*
if(adcTime==adcSampleFreq){      //5000 para bajas velocidades
  ADCSC1=11101001;
  adcTime=0;
} 
/*
if(STATUS_MEF==lastStatus){
   STATUS_MEF=MEF_WAIT; 
  
}
lastStatus=STATUS_MEF;*/


for(i=0;i<=getExecutingVectorPointer();i++){
  decreaseTimer(getFromExecutingVectorOnIndex(i));
     
      
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
          currentFunction->timerCount=currentFunction->timerCount-1;
     } 
  }
   
}
