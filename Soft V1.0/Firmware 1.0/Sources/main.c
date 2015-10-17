/*==================[inclusions]=============================================*/
#include "Linker.h"


void main(void) {

  
  
  /* include your code here */  
  InitDevice();
  
  
 
  
  

  
  for(;;) {
  
  if(adcEnable==TRUE){      //5000 para bajas velocidades
    adcEnable=FALSE;
    switchSensor();
    
  } 
  
  
    
    functionHandler();
    dispatcher(&executingVector,&bufferOut);
    frameGenerator();
    
    
      
    } /* loop forever */
   
  /* please make sure that you never leave main */
}
