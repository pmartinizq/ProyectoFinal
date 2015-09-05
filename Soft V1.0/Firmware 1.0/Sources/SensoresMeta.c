#include "SensoresMeta.h"



interrupt VectorNumber_Vadc void adcInterrupt (void){
  
 (void) ADCRH;
 if(ADCSC1 == 11100000){
  varSensor1 = ADCRL;
 }
 else{
  if(ADCSC1 == 11100001){
   varSensor2 = ADCRL;
  }
 }
 switchSensor(); 
}

void switchSensor (void){
  if(ADCSC1 == 11100000){
    ADCSC1 = 11100001;  
  } 
  else{
    if(ADCSC1 == 11100000){
      ADCSC1 = 11100000;
    }
  }
}