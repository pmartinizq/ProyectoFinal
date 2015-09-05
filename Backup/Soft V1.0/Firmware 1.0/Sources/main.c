
#include "Config.h"



void main(void) {

  
   
  /* include your code here */
  
  f1.functionId=0x01;
  f1.status=RUNNING;
  f1.root=UNIQUE_FUNCTION;
  f1.timerCount=50;
  
  DisableInterrupts;
  InitReg();  
  InitClock();
  InitComunication();
  InitInputCompare();
  InitPorts();
  InitRtc();
  beginComunication();
  initExecutingVector();
  InitBuffer(&bufferIn);
  InitBuffer(&bufferOut);
  EnableInterrupts;
  
  
  for(;;) {
  
  functionHandler();
  dispatcher(&executingVector,&bufferOut);
  frameGenerator();
    
    //Sensor1();
    
  } /* loop forever */
  /* please make sure that you never leave main */
}
