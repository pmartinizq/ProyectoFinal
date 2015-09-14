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
 left = getGoalLeftStatus(); 
 right = getGoalRightStatus();
  
 if(left == 1 && right == 1){
      goalSensorStatus = 1;
 } else{
      goalSensorStatus = 0;
 } 
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
 currentFunction->status = RUNNING;
 setSensorStatus(parameter);
 goalStatus = goalSensorStatus;
 currentFunction->status = AVAILABLE;
}

void setSensorStatus(int parameter){
 sensorStatus = parameter;
}

uint8_t getGoalRightStatus(void){
 if(varSensorRight >= (varSensorRightRef + varSensorRightRefMargin)){
    return 1;
 } else{
    return 0;
 }
}

uint8_t getGoalLeftStatus(void){
 if(varSensorLeft >= (varSensorLeftRef + varSensorLeftRefMargin)){
    return 1;
 } else{
    return 0;
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