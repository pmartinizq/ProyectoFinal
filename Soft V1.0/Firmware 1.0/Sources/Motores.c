#include "Motores.h"



void setPwmValue(int valueToSetRight,int valueToSetLeft){
 uint8_t highValue=0;
 
 
 calculateValueRight=PENDIENTE*valueToSetRight;
 calculateValueLeft=PENDIENTE*valueToSetLeft;
 if(calculateValueRight!=lastValueRight){
  lastValueRight=calculateValueRight;  
   if(calculateValueRight!=TPM2C0V){
    
    TPM2C0V=calculateValueRight;
   }
 }
 
 if(calculateValueLeft!=lastValueLeft){
  lastValueLeft=calculateValueLeft;  
   if(calculateValueLeft!=TPM2C1V){
    
    TPM2C1V=calculateValueLeft;
   }
 }
  
  
}