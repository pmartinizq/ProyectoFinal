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

void calcularSentido(int sentido){
  
  if(sentido==robotAdelante){
    SENTIDO_M1_1=1;
    SENTIDO_M1_2=0;   
    SENTIDO_M2_1=1;
    SENTIDO_M2_2=0;  
  }
  if(sentido==robotAtras){
    SENTIDO_M1_1=1;
    SENTIDO_M1_2=0;    
    SENTIDO_M2_1=1;
    SENTIDO_M2_2=0;  
    
  }
  if(sentido==robotGiroDerecha){
    SENTIDO_M1_1=1;
    SENTIDO_M1_2=0;    
    SENTIDO_M2_1=1;
    SENTIDO_M2_2=0; 
  }
  if(sentido==robotGiroIzquierda){
    SENTIDO_M1_1=1;
    SENTIDO_M1_2=0;    
    SENTIDO_M2_1=1;
    SENTIDO_M2_2=0; 
    
  }   
  
}