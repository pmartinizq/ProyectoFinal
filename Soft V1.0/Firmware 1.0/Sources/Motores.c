#include "Motores.h"



void setPwmValue(int valueToSetRight,int valueToSetLeft){
 uint8_t highValue=0;
 
 
 calculateValueRight=PENDIENTE*valueToSetRight;
 calculateValueLeft=PENDIENTE*valueToSetLeft;
 
 if(calculateValueRight==0){
  TPM2C0SC=TPM2C0SC&0xf0;
  lastValueRight=0;
 } else{
    if(lastValueRight==0){
       TPM2C0SC=PWM_CH0_CONFIG;
    }
    if(calculateValueRight!=TPM2C0V){
    
      TPM2C0V=calculateValueRight;
      lastValueRight=calculateValueRight;
   }
 }
 
 if(calculateValueLeft==0){
  TPM2C1SC=TPM2C1SC&0xf0;
  lastValueLeft=0;
 } else{
    if(lastValueLeft==0){
       TPM2C1SC=PWM_CH1_CONFIG;
    }
    if(calculateValueLeft!=TPM2C1V){
    
      TPM2C1V=calculateValueLeft;
      lastValueLeft=calculateValueLeft;
   }
 }
    
 /* 
 
 if(calculateValueRight!=lastValueRight&&calculateValueRight!=0){
  lastValueRight=calculateValueRight;  
   if(calculateValueRight!=TPM2C0V&&calculateValueRight!=0){
    
    TPM2C0V=calculateValueRight;
   } else{
     TPM2C0SC=TPM2C0SC&0xf0;
   }
 }
 else{
    TPM2C0SC=TPM2C0SC&0xf0;
    
   }
 
 if(calculateValueLeft!=lastValueLeft&&calculateValueLeft!=0){
  lastValueLeft=calculateValueLeft;  
   if(calculateValueLeft!=TPM2C1V&&calculateValueLeft!=0){
    
    TPM2C1V=calculateValueLeft;
   }else{
    TPM2C1SC=TPM2C1SC&0xf0;
    
   }
 }
 else{
    TPM2C1SC=TPM2C1SC&0xf0;
    
   }
  
   */
}

void calcularSentido(int sentido){
  
  if(sentido==robotAdelante){
    SENTIDO_M1_1=0;
    SENTIDO_M1_2=1;   
    SENTIDO_M2_1=0;
    SENTIDO_M2_2=1;  
  }
  if(sentido==robotAtras){
    SENTIDO_M1_1=1;
    SENTIDO_M1_2=0;    
    SENTIDO_M2_1=1;
    SENTIDO_M2_2=0;  
    
  }
  if(sentido==robotGiroDerecha){
    SENTIDO_M1_1=0;
    SENTIDO_M1_2=1;    
    SENTIDO_M2_1=1;
    SENTIDO_M2_2=0; 
  }
  if(sentido==robotGiroIzquierda){
    SENTIDO_M1_1=1;
    SENTIDO_M1_2=0;    
    SENTIDO_M2_1=0;
    SENTIDO_M2_2=1; 
    
  }   
  
}