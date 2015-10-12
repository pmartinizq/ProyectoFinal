#include "SensoresUltraSonido.h"

void getUltrasonic(FunctionStruct* currentFunction){
  uint8_t ultrasonic=0;
  ultrasonic=currentFunction->functionId;
  switch(ultrasonic){
    
  case ULTRASONIC_FRONT:   sensorFrontFunctionStruct=currentFunction;
                                  (void)(TPM1C0SC==0);
                                  TPM1C0SC_CH0F=0; //ACOMODAR ESTO PARA QUE SEA GENERICO
                                  SENSOR_FRONT_ENABLE_INTERRUPT;
                                  SENSOR_FRONT_TRIGGER=1;
                                  triggerDelay();
                                  SENSOR_FRONT_TRIGGER=0;                                  
                                  break;
                                  
  case ULTRASONIC_LEFT:   sensorLeftFunctionStruct=currentFunction;
                                  (void)(TPM1C1SC==0);
                                  TPM1C1SC_CH1F=0;
                                  SENSOR_LEFT_ENABLE_INTERRUPT;
                                  SENSOR_LEFT_TRIGGER=1;
                                  triggerDelay();
                                  SENSOR_LEFT_TRIGGER=0;                                  
                                  break;
  case ULTRASONIC_RIGHT:   sensorRightFunctionStruct=currentFunction;
                                  (void)(TPM1C2SC==0);
                                  TPM1C2SC_CH2F=0;
                                  SENSOR_RIGHT_ENABLE_INTERRUPT;
                                  SENSOR_RIGHT_TRIGGER=1;
                                  triggerDelay();
                                  SENSOR_RIGHT_TRIGGER=0;                                  
                                  break;                                	  
  
  
  }
}



  
void triggerDelay(void){
 int t;
 t=16;
  while(t!=0){
    t--;
  } 
  
}


interrupt VectorNumber_Vtpm1ch0 void interruptSensorFront (void)                        //sensor1 (frente)
{
  
  
  (void)(TPM1C0SC==0);//Borra el flag de interrupcion
  TPM1C0SC_CH0F = 0;
  
  if(mefSensorFrontStatus==MEF_STATUS_WAIT) //Si es el primer flanco(ascendente) toma el valor en b
  {  
    sensorFrontFunctionStruct->status=RUNNING;
    risingEdgeTimeSensorFront=SENSOR_FRONT_TIMER_VALUE; 
    mefSensorFrontStatus=MEF_STATUS_RUNNING;//flag bit indica que ya fue tomado el primer flanco ascendente
    return;
  }
  else         //flag bit=1 indica que ya fue tomado el primer flanco ahora se captura el flanco descendente
  {  
    fallingEdgeTimeSensorFront=SENSOR_FRONT_TIMER_VALUE;
    mefSensorFrontStatus=MEF_STATUS_WAIT;
    sensorFrontTime=fallingEdgeTimeSensorFront-risingEdgeTimeSensorFront;//d es la medicion, resta los tiempos de muuestra de ambos flancos
    measureSensorFront16=(sensorFrontTime*10)/58;
    if(measureSensorFront16>255){
      sensorFrontDatos=255;
    } else{
      sensorFrontDatos=(byte)measureSensorFront16;
    }
    sensorFrontFunctionStruct->data[0]=sensorFrontDatos;
    sensorFrontFunctionStruct->status=AVAILABLE;    
    SENSOR_FRONT_DISABLE_INTERRUPT;
    
  }
  return;   
}


interrupt VectorNumber_Vtpm1ch1 void interruptSensorLeft (void)                        
{
  
  
  (void)(TPM1C1SC==0);//Borra el flag de interrupcion
  TPM1C1SC_CH1F = 0;
  
  if(mefSensorLeftStatus==MEF_STATUS_WAIT) 
  {  
    sensorLeftFunctionStruct->status=RUNNING;
    risingEdgeTimeSensorLeft=SENSOR_LEFT_TIMER_VALUE; 
    mefSensorLeftStatus=MEF_STATUS_RUNNING;
    return;
  }
  else         
  {  
    fallingEdgeTimeSensorLeft=SENSOR_LEFT_TIMER_VALUE;
    mefSensorLeftStatus=MEF_STATUS_WAIT;
    sensorLeftTime=fallingEdgeTimeSensorLeft-risingEdgeTimeSensorLeft;
    measureSensorLeft16=(sensorLeftTime*10)/58;
    if(measureSensorLeft16>255){
      sensorLeftDatos=255;
    } else{
      sensorLeftDatos=(byte)measureSensorLeft16;
    }
    sensorLeftFunctionStruct->data[0]=sensorLeftDatos;
    sensorLeftFunctionStruct->status=AVAILABLE;
    SENSOR_LEFT_DISABLE_INTERRUPT;
    
  }
  return;   
}


interrupt VectorNumber_Vtpm1ch2 void interruptSensorRight (void)                        
{
  
  
  (void)(TPM1C2SC==0);//Borra el flag de interrupcion
  TPM1C2SC_CH2F = 0;
  
  if(mefSensorRightStatus==MEF_STATUS_WAIT) 
  {  
    sensorRightFunctionStruct->status=RUNNING;
    risingEdgeTimeSensorRight=SENSOR_RIGHT_TIMER_VALUE; 
    mefSensorRightStatus=MEF_STATUS_RUNNING;
    return;
  }
  else         
  {  
    fallingEdgeTimeSensorRight=SENSOR_RIGHT_TIMER_VALUE;
    mefSensorRightStatus=MEF_STATUS_WAIT;
    sensorRightTime=fallingEdgeTimeSensorRight-risingEdgeTimeSensorRight;
    measureSensorRight16=(sensorRightTime*10)/58;
    if(measureSensorRight16>255){
      sensorRightDatos=255;
    } else{
      sensorRightDatos=(byte)measureSensorRight16;
    }
    sensorRightFunctionStruct->data[0]=sensorRightDatos;
    sensorRightFunctionStruct->status=AVAILABLE;
    SENSOR_RIGHT_DISABLE_INTERRUPT;
    
  }
  return;   
}

