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
  else if(sensorNumber == 3&&sensorNumber == 4){
      varSensorStepADC = ADCRL;
      ADCSC1=0x00;
    
      
  /*    
  if(varSensorStepADC>max){
   max=varSensorStepADC; 
    
  }else if(varSensorStepADC<max){
    maximos[indice]=max;
    indice++;
    max=0;
  }
  
  if(varSensorStepADC<min){
   min=varSensorStepADC; 
    
  }else if(varSensorStepADC>min){
    minimos[indiceM]=min;
    indiceM++;
    min=255;
  }   */
 
  if(first==0){
     if(varSensorStepADC>150){
      lastStepValue=0;
     }else{
      lastStepValue=255;
     }
     
  }
 

  if(varSensorStepADC!=lastStepValue){
    if(lastStepValue>varSensorStepADC){
      diferencia = lastStepValue - varSensorStepADC;
      signoPendiente=0;
    }else{
      diferencia = varSensorStepADC - lastStepValue;
      signoPendiente=1;
    }
    lastStepValue=varSensorStepADC;
    
    
    if(first==0){
      first=1;
      ultimoSigno=signoPendiente;
    }
    
      
    if(diferencia > 10){
    pendientes[indice2]=varSensorStepADC;
    indice2++;
    
    if(signoPendiente==1&&ultimoSigno==0){
        stepsWheelADC++;
        ultimoSigno=signoPendiente;
    }else if(signoPendiente==0&&ultimoSigno==1){
      stepsWheelADC++;
      ultimoSigno=signoPendiente;
    
    }
    /*
    if(signoPendiente==1){
      
      if(varSensorStepADC>max){
       max=varSensorStepADC; 
      
      }else if(varSensorStepADC<max){
        maximos[indice]=max;
        indice++;
        max=0;
        stepsWheelADC++;
      }
    }
    else{      
    
    if(varSensorStepADC<min){
    min=varSensorStepADC; 
    
    }else if(varSensorStepADC>min){
      minimos[indiceM]=min;
      indiceM++;
      stepsWheelADC++;
      min=255;
    }
    }*/
      
         if(stepsWheelADC==40){
        SENTIDO_M1_1=1;
        SENTIDO_M1_2=1;
        SENTIDO_M2_1=1;
        SENTIDO_M2_2=1;
        setPwmValue(0);
      }          
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

 switch(sensorNumber){
  
  case SENSOR_META_1:   sensorNumber=SENSOR_META_2;
                        ADCSC1_ADCH=00001;
                        break;
  case SENSOR_META_2:   sensorNumber=SENSOR_RUEDA_1;
                        ADCSC1_ADCH=01000;
                        break;
                        
 }
 /*

  if(sensorNumber==1){
    ADCSC1_ADCH=01001;
    //ADCSC1=11100001;
    sensorNumber=3;
  } 
  else{
    if(sensorNumber==2){
      ADCSC1_ADCH=01001;
      //ADCSC1=11101001;
      sensorNumber=3;
    } 
    else{
      if(sensorNumber==3){
        ADCSC1_ADCH=01001;
        //ADCSC1=11100000;
        sensorNumber=3; 
      }
    }
  }*/
}


void setGoalMode(int parameter, FunctionStruct* currentFunction){
 currentFunction->status = RUNNING;
 setSensorStatus(parameter);
 currentFunction->data->data[0] = goalSensorStatus;
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