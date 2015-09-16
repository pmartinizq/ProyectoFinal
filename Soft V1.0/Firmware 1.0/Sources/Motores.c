#include "Motores.h"



void setPwmValue(int valueToSet){
 uint8_t highValue=0;
 
 actualValue=0;
 actualValue=actualValue + PWM_FREQ_HIGH;
 actualValue=actualValue<<8;
 actualValue=actualValue+ PWM_FREQ_LOW;
 calculateValue=PENDIENTE*valueToSet;
 if(calculateValue!=lastValue){
  lastValue=calculateValue;  
   if(calculateValue!=TPM2C0V){
    
    TPM2C0V=calculateValue;
   }
 }
  
  
}