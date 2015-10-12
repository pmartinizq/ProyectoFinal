
#include "Config.h"


void main(void) {

  

  int t=15;
  /* include your code here */
  
  f1.functionId=ULTRASONIC_FRONT;
  f1.status=READY;
  f1.root=UNIQUE_FUNCTION;
  f1.timerCount=50;
  
  DisableInterrupts;
  InitReg();  
  InitClock();
  InitComunication();  
  InitPorts();
  InitInputCompare();
  
  //InitKbi();
  beginComunication();
  initExecutingVector();
  InitBuffer(&bufferIn);
  InitBuffer(&bufferOut);
  initIDNumber();
  InitPwm();
  //InitADC();  
  EnableInterrupts;
  //InitRtc();
  /*  
    despues de habilitar interrupciones y
    antes de empezar a mover el robot debe calibrar sensores de meta
    no arrancar el motor sin antes ejecutar initGoalSensor()! 
  */
  //initGoalSensor();
  //calcularSentido(robot_speed_to_pwm(t,0,&pwmRightValue,&pwmLeftValue));
  //setPwmValue(pwmRightValue,pwmLeftValue);
  
  
 
  
  adcSampleFreq=5;
  

  
  for(;;) {
  if(goalStatus == 0){
    
    
    
    //setGoalMode(STOP_ON_GOAL);
    
    
    
    SENSOR_DE_META_ON;
     

    
    
    functionHandler();
    dispatcher(&executingVector,&bufferOut);
    frameGenerator();
    
    /*
     f1.functionId=ULTRASONIC_FRONT;
      f1.status=READY;
      getUltrasonic(&f1);
      
      while(f1.status!=AVAILABLE);
      t=3000;
      while(t!=0){
        t--;
      } 
      
      /*
      f1.functionId=ULTRASONIC_FRONT;
      f1.status=READY;
      f1.root=UNIQUE_FUNCTION;
      f1.timerCount=50;
      getUltrasonic(&f1);
      
      while(f1.status!=AVAILABLE);
      t=3000;
      while(t!=0){
        t--;
      } */
      /*
      f1.functionId=ULTRASONIC_RIGHT;
      f1.status=READY;
      getUltrasonic(&f1);
      
      while(f1.status!=AVAILABLE);
      t=30000;
      while(t!=0){
        t--;
      } */
      
    } /* loop forever */
  } 
  /* please make sure that you never leave main */
}
