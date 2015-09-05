#include "RTCmodule.h"

interrupt VectorNumber_Vrtc   void RTCInterrupt (void){
uint8_t i=0;
RTCSC=RTCSC|0x80;
/*time++;
if(time==100){
  setToBuffer(0x04,&bufferOut);
  setToBuffer(time,&bufferOut);
  time=0;
} */
  
for(i=0;i<=getExecutingVectorPointer();i++){
  decreaseTimer(getFromExecutingVectorOnIndex(i));
     
      
 }
  
}

void decreaseTimer(FunctionStruct* currentFunction){
  if((currentFunction->status==RUNNING)&&(currentFunction->timerCount==0)){
        currentFunction->status=TIMEOUT;
        
      }
      if(currentFunction->status==RUNNING&&currentFunction->timerCount>0){
        currentFunction->timerCount=currentFunction->timerCount-1;
      }
}
