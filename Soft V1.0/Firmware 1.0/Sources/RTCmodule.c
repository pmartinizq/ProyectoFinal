/*==================[inclusions]=============================================*/

#include "RTCmodule.h"

/*==================[macros and definitions]=================================*/

#define VELOCITY_MEASSURE_FREQ 3 //36857 ->1seg   18428->0.5seg
#define VELOCITY_TIME 500
/*==================[internal data declaration]==============================*/

uint8_t timeCounter,j=0;
uint16_t kbiTime,adcTime;
uint16_t velocityMeassureTimer;
uint16_t actualLeftStep,actualRightStep; 
uint8_t lastStatus;
uint16_t lastLeftStep=0,lastRightStep=0;
uint16_t lastLeftWheelVelocity=0;
uint16_t valores[100];

/*==================[internal functions declaration]=========================*/

void decreaseTimer(FunctionStruct*);

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[external functions definition]==========================*/

interrupt VectorNumber_Vrtc   void RTCInterrupt (void){
  unsigned long long velocityAux=0;
  
  uint8_t i=0;
  
  static calibrar,apagar=0;
  RTCSC_RTIF=1;
  
  adcTime++;
  velocityMeassureTimer++;
  
  if(velocityMeassureTimer==VELOCITY_MEASSURE_FREQ){
    tickTime++;
    velocityMeassureTimer=0;
  }
    /*
    velocityMeassureTimer=0;
    actualLeftStep=(leftWheelStepValue-lastLeftStep);
    actualRightStep=(rightWheelStepValue-lastRightStep);
    /*
    calibrar++;
    if(calibrar==5){
      calibrar=0;
      if(apagar==1){
        PTED_PTED4=0;
      }else{
        
        PTED_PTED4=1;
        apagar=1;
      }
    }*/ 

   /*
    velocityAux=(actualLeftStep*9);
    velocityAux=velocityAux*3142;
    velocityAux=velocityAux/180;
    velocityAux=(velocityAux*1000)/VELOCITY_TIME;
    
    leftWheelVelocity=velocityAux;    
    lastLeftWheelVelocity=velocityAux;
    valores[j]=actualLeftStep;
    if(j<100){
      j++;
    }
    lastLeftStep=leftWheelStepValue;
    
    velocityAux=(actualRightStep*9);
    velocityAux=velocityAux*3142;
    velocityAux=velocityAux/180;
    velocityAux=(velocityAux*1000)/VELOCITY_TIME;
    rightWheelVelocity=velocityAux;    
    lastRightStep=rightWheelStepValue;
    
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

/*==================[internal functions definition]==========================*/

/**
  @brief Decremeta el timer la funcion que se asigna por parametro.
  @param currentFunction puntero a la funcion que se encuentra en el vector 
  de ejecucion 
  @return void
*/
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