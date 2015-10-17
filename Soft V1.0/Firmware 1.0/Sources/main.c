/*==================[inclusions]=============================================*/

#include "Linker.h"

void main(void) {

  InitDevice();  
    
  for(;;) {
    
    if(adcEnable==TRUE){
      adcEnable=FALSE;
      switchSensor();    
    } 
    
    functionHandler();
    dispatcher(&executingVector,&bufferOut);
    frameGenerator();
       
  } /* loop forever */   
  /* please make sure that you never leave main */
}
