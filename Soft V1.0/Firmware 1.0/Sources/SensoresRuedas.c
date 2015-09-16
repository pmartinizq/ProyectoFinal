#include "SensoresRuedas.h"

interrupt VectorNumber_Vkeyboard void kbiInterrupt (void){
  KBISC_KBACK=1;
  if(valorFlanco==1){
    valorFlanco=0;
    KBIES_KBEDG2=0;
  }else{
    valorFlanco=1;
    KBIES_KBEDG2=1;
  }
  pasos++;
  
  if(pasos==pasosGoal){
    SENTIDO_M2_1=1;
    SENTIDO_M2_2=1;
    setPwmValue(0);
    
  }
  //KBISC=0x00;
  KBIPE_KBIPE2=0;
    
  
  
}