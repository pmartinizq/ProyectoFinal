#include "RTCmodule.h"

interrupt VectorNumber_Vrtc   void RTCInterrupt (void){
uint8_t i=0;
RTCSC=RTCSC|0x80;
kbiTime++;
adcTime++; /*
if(kbiTime==kbiSampleFreq){      //5000 para bajas velocidades
  KBIPE_KBIPE2=1;  
  kbiTime=0;
}

if(adcTime==adcSampleFreq){      //5000 para bajas velocidades
  ADCSC1=11100000;
  adcTime=0;
}  */
for(i=0;i<=getExecutingVectorPointer();i++){
  decreaseTimer(getFromExecutingVectorOnIndex(i));
     
      
 }
  
}

void decreaseTimer(FunctionStruct* currentFunction){
  if((currentFunction->status==RUNNING)&&(currentFunction->timerCount==0)){
        currentFunction->status=TIMEOUT;
        
  } 
 if((currentFunction->status==READY)&&(currentFunction->timerCount==0)){
       currentFunction->status=INACCESSIBLE_DEVICE;
  }
  if((currentFunction->status==RUNNING&&currentFunction->timerCount>5)||(currentFunction->status==READY&&currentFunction->timerCount>0)){
        currentFunction->timerCount=currentFunction->timerCount-1;
   }  
   
}
