/*==================[inclusions]=============================================*/

#include "AdcModule.h"

/*==================[macros and definitions]=================================*/

#define SENSOR_META_1 1
#define SENSOR_META_2 2
#define SENSOR_RUEDA_1 3
#define SENSOR_RUEDA_2 5

/*==================[internal data declaration]==============================*/

static uint8_t sensorNumber=1;
static int varSensorLeft;
static int varSensorRight;
static uint8_t adcWheelSensor1;
static uint8_t adcWheelSensor2; 
static int varSensorLeftRef;
static int varSensorRightRef;
static int varSensorLeftRefMargin = 20;
static int varSensorRightRefMargin = 4;
static int sensorStatus = 1;

int left;
int right;
int whileFlag;
int goalSensorStatus;
uint32_t tiempoActual,tiempoAnterior;
uint32_t tiempoEntrePasos;
uint8_t newStepLeftWheel;
uint16_t datos[6];

/*==================[internal functions declaration]=========================*/

/**
  @brief establece el estado obtenido desde la capa superior en la variable global 'sensorStatus'. 

  @param parameter representa el estado obtenido desde la capa superior.

  @returns void.

  */
void setSensorStatus(int parameter);

/**
  @brief establece el valor medido en el sensor derecho del modulo sensor de meta. 

  @returns retorna el valor establecido.

  */
uint8_t getGoalRightStatus(void);

/**
  @brief establece el valor medido en el sensor izquierdo del modulo sensor de meta. 

  @returns retorna el valor establecido.

  */
uint8_t getGoalLeftStatus(void);

/*==================[internal data definition]===============================*/

static uint8_t firstTimeSensor1=0,firstTimeSensor2=0;
static uint8_t lastAdcValueSensor1,lastAdcValueSensor2;
static uint8_t slopeSensor1,slopeSensor2,signSlopeSensor1,signSlopeSensor2;
static uint8_t lastSignSlopeSensor1,lastSignSlopeSensor2; 

/*==================[external data definition]===============================*/

/*==================[external functions definition]==========================*/

/*==================[internal functions definition]==========================*/

interrupt VectorNumber_Vadc void adcInterrupt (void){
//uint8_t adcWheelSensor1,adcWheelSensor2; 

isAdcRunning=1;
(void) ADCRH;

 
 if(sensorNumber == SENSOR_META_1||sensorNumber == SENSOR_META_2){
  
     if(sensorNumber == SENSOR_META_1){
        varSensorLeft = ADCRL;
      } 
      else if(sensorNumber == SENSOR_META_2){
          varSensorRight = ADCRL;
      }
      
      if(left == 1 && right == 1){
         goalSensorStatus = 1;
       } else{
            goalSensorStatus = 0;
       }
       left = getGoalLeftStatus(); 
       right = getGoalRightStatus();
       
 }
  else if(sensorNumber == SENSOR_RUEDA_1||sensorNumber == SENSOR_RUEDA_2){
    
      if(sensorNumber == SENSOR_RUEDA_1){
        adcWheelSensor1 = ADCRL;
        
        
        if(firstTimeSensor1==0){
           if(adcWheelSensor1>150){
            lastAdcValueSensor1=0;
           }else{
            lastAdcValueSensor1=255;
           }         
        }
 

        if(adcWheelSensor1!=lastAdcValueSensor1){
          if(lastAdcValueSensor1>adcWheelSensor1){
            slopeSensor1 = lastAdcValueSensor1 - adcWheelSensor1;
            signSlopeSensor1=0;
         }else{
            slopeSensor1 = adcWheelSensor1 - lastAdcValueSensor1;
            signSlopeSensor1=1;
         }
         lastAdcValueSensor1=adcWheelSensor1;
    
    
          if(firstTimeSensor1==0){
            firstTimeSensor1=1;
            lastSignSlopeSensor1=signSlopeSensor1;
          }
    
      
          if(slopeSensor1 > MIN_SLOPE){
          
          
          if(signSlopeSensor1==1&&lastSignSlopeSensor1==0){
              rightWheelStepValue++;
              lastSignSlopeSensor1=signSlopeSensor1;
          }else if(signSlopeSensor1==0&&lastSignSlopeSensor1==1){
              rightWheelStepValue++;
            lastSignSlopeSensor1=signSlopeSensor1;
          
          }
    
          if(verifyStepsRight()&&moveBy==STEPS){
            stopRightWheel();
          }
          
                
          }
        }
      } else if(sensorNumber == SENSOR_RUEDA_2){
        adcWheelSensor2 = ADCRL;
        
        if(firstTimeSensor2==0){
           if(adcWheelSensor2>150){
            lastAdcValueSensor2=0;
           }else{
            lastAdcValueSensor2=255;
           }         
        }
 

        if(adcWheelSensor2!=lastAdcValueSensor2){
          if(lastAdcValueSensor2>adcWheelSensor2){
            slopeSensor2 = lastAdcValueSensor2 - adcWheelSensor2;
            signSlopeSensor2=0;
         }else if(lastAdcValueSensor2<adcWheelSensor2){
            slopeSensor2 = adcWheelSensor2 - lastAdcValueSensor2;
            signSlopeSensor2=1;
         }
         lastAdcValueSensor2=adcWheelSensor2;
    
    
          if(firstTimeSensor2==0){
            firstTimeSensor2=1;
            lastSignSlopeSensor2=signSlopeSensor2;
          }
    
      
          if(slopeSensor2 > MIN_SLOPE){
            
          
          if(signSlopeSensor2==1&&lastSignSlopeSensor2==0){
              leftWheelStepValue++;
              newStepLeftWheel=1;
              lastSignSlopeSensor2=signSlopeSensor2;
              getVelocity();
              
          }else if(signSlopeSensor2==0&&lastSignSlopeSensor2==1){
              leftWheelStepValue++;
              newStepLeftWheel=1;
              lastSignSlopeSensor2=signSlopeSensor2;
              getVelocity();
          
          }
          
          if(verifyStepsLeft()&&moveBy==STEPS){
            stopLeftWheel();
          }
    
      
                
          }
        }
      }
      
      
      
      
  }
  

isAdcRunning=0; 
  
}

int getVelocity(){
  
  uint8_t k=0;
  static uint8_t flag=0;
  uint32_t timeAux,suma=0;
  static i=0,velocidad;
 
    newStepLeftWheel=0;
    if(flag==0){
      tiempoAnterior=tickTime;
      flag=1;
    }else{
      flag=0;
      tiempoActual=tickTime;     
      tiempoEntrePasos=tiempoActual-tiempoAnterior;
      
    }
    
      if(tiempoEntrePasos>0){
        
        velocidad=1570000/tiempoEntrePasos;
        if(i<6){
          datos[i]=velocidad;;
          i++;
        }else{
          i=0;
        }
      }
      
    for(k=0;k<6;k++){
      suma=suma+datos[k];
    }
    leftWheelVelocity=suma/6;
      
        
 
    
  
}

//DEVUELVE TRUE SI LOS PASOS SON IGUALES A LOS PASOS TO SET
Bool verifyStepsRight (){
Bool result=FALSE;
  if(rightWheelStepValueToSet!=0){
   if(rightWheelStepValue>=rightWheelStepValueToSet){
    result=TRUE;
   }
    
  }else{
    return FALSE;
  }
  return result;
}


Bool verifyStepsLeft (){
Bool result=FALSE;
  if(leftWheelStepValueToSet!=0){
   if(leftWheelStepValue>=leftWheelStepValueToSet){
    result=TRUE;
   }
    
  }else{
    return FALSE;
  }
  return result;    
  
}


void switchSensor (void){
uint8_t channel=0;


 switch(sensorNumber){
  
  case SENSOR_META_1:   sensorNumber=SENSOR_META_2;
                        channel=0b00001;
                        //ADCSC1_ADCH=00001;
                        break;
  case SENSOR_META_2:   sensorNumber=SENSOR_RUEDA_1;
                        channel=0b01001;
                        //ADCSC1_ADCH=01000;
                        break;
                           
  case SENSOR_RUEDA_1:  sensorNumber=SENSOR_RUEDA_2;
                        channel=0b01000;
                        //ADCSC1_ADCH=01001;
                        break;  
  case SENSOR_RUEDA_2:  sensorNumber=SENSOR_META_1;
                        //isAdcRunning=0;
                        channel=0b00000;
                        //ADC_OFF;
                        break;    
                          
 }                       
 APCTL1=0x03;
 APCTL2=0x03;
 isAdcRunning=1;
 ADCSC1_ADCH=channel;
 
}


void setGoalMode(int parameter, FunctionStruct* currentFunction){
 currentFunction->status = RUNNING;
 setSensorStatus(parameter);
 currentFunction->data[0] = goalSensorStatus;
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

int varToCast = 0;
void testFunction1(FunctionStruct* currentFunction){
 currentFunction->status = RUNNING;
 varToCast = 122;
 currentFunction->data[0] = varToCast >> 8;
 currentFunction->data[1] = varToCast;
 varToCast = 133;
 currentFunction->data[2] = varToCast >> 8;
 currentFunction->data[3] = varToCast; 
 varToCast = 144;
 currentFunction->data[4] = varToCast >> 8;
 currentFunction->data[5] = varToCast;
 currentFunction->status = AVAILABLE;
}

void testFunction2(FunctionStruct* currentFunction){
 currentFunction->status = RUNNING;
 varToCast = 155;
 currentFunction->data[0] = varToCast >> 8;
 currentFunction->data[1] = varToCast;
 varToCast = 166;
 currentFunction->data[2] = varToCast >> 8;
 currentFunction->data[3] = varToCast; 
 varToCast = 177;
 currentFunction->data[4] = varToCast >> 8;
 currentFunction->data[5] = varToCast;
 currentFunction->status = AVAILABLE;
}

void testFunction3(FunctionStruct* currentFunction){
 currentFunction->status = RUNNING;
 varToCast = 299;
 currentFunction->data[0] = varToCast >> 8;
 currentFunction->data[1] = varToCast;
 currentFunction->status = AVAILABLE;
}