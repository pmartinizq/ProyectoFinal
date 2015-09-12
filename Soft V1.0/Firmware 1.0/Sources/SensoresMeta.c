#include "SensoresMeta.h"



interrupt VectorNumber_Vadc void adcInterrupt (void){
  
 (void) ADCRH;
 
 if(sensorNumber==1){
    varSensorLeft=ADCRL;
  } 
  else{
    if(sensorNumber==2){
      varSensorRight=ADCRL;
    }
  }
 switchSensor(); 
}

void switchSensor (void){

  
  if(sensorNumber==1){
    ADCSC1_ADCH=1111;
    ADCSC1=11000001;
    sensorNumber=2;
  } 
  else{
    if(sensorNumber==2){
      ADCSC1_ADCH=1111;
      ADCSC1=11000000;
      sensorNumber=1;
    }
  }
}

void setGoalMode(int parameter, FunctionStruct* currentFunction){
 currentFunction->status=RUNNING;
 setReadSensor(parameter);
 
 left = getGoalLeftStatus(); 
 right = getGoalRightStatus();
 
 if( left == 1 && right == 1){
      goalSensorStatus = 1;
 } else{
      goalSensorStatus = 0;
 }
 goalStatus = goalSensorStatus;
 currentFunction->status=AVAILABLE;
}

void setReadSensor(int parameter){
 if(parameter != NOP){
   if(parameter == STOP_ON_GOAL){
    readSensor = 1;
   } else if(parameter == CONTINUE){
    readSensor = 0;
   }
 }
}

uint8_t getGoalRightStatus(void){
 if(readSensor == 0){
    return 0;
 }
 if(varSensorRight >= (varSensorRightRef + varSensorRightRefMargin)){
    return 1;
 }
}

uint8_t getGoalLeftStatus(void){
  if(readSensor == 0){
    return 0;
 }
 if(varSensorLeft >= (varSensorLeftRef + varSensorLeftRefMargin)){
    return 1;
 }
}

void initGoalSensor(void){
    whileFlag = 1000;
   while(whileFlag > 0){
   whileFlag--;
   }
   varSensorLeftRef = varSensorLeft;
   varSensorRightRef = varSensorRight;
}