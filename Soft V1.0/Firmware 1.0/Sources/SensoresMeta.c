#include "SensoresMeta.h"



interrupt VectorNumber_Vadc void adcInterrupt (void){
  
 (void) ADCRH;
 //ADCSC1_AIEN=0;
 
 if(sensorNumber == 1){
    varSensorLeft = ADCRL;
  } 
  else if(sensorNumber == 2){
      varSensorRight = ADCRL;
  } 
  else if(sensorNumber == 3){
      varSensorStepADC = ADCRL;
      ADCSC1=0x00;
 
  
  if(varSensorStepADC!=lastStepValue){
    if(lastStepValue>varSensorStepADC){
      diferencia = lastStepValue - varSensorStepADC;
    }else{
      diferencia = varSensorStepADC - lastStepValue;
    }
    if(diferencia > 180){
      stepsWheelADC++;
          if(stepsWheelADC==40){
        SENTIDO_M1_1=1;
        SENTIDO_M1_2=1;
        SENTIDO_M2_1=1;
        SENTIDO_M2_2=1;
        setPwmValue(0);
      }             
      lastStepValue=varSensorStepADC;
    }
  }
  }  
  
  
  if(left == 1 && right == 1){
      goalSensorStatus = 1;
 } else{
      goalSensorStatus = 0;
 }
 left = getGoalLeftStatus(); 
 right = getGoalRightStatus();
 switchSensor(); 
  
}


void initSample(void){
  
  
}

void switchSensor (void){

  

  if(sensorNumber==1){
    //ADCSC1_ADCH=00001;
    ADCSC1=11100001;
    sensorNumber=2;
  } 
  else{
    if(sensorNumber==2){
      //ADCSC1_ADCH=01001;
      ADCSC1=11101001;
      sensorNumber=3;
    } 
    else{
      if(sensorNumber==3){
        //ADCSC1_ADCH=00001;
        //ADCSC1=11100000;
        sensorNumber=1; 
      }
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