/*==================[inclusions]=============================================*/

#include "Motors.h"

/*==================[macros and definitions]=================================*/

#define SENTIDO_M1_1  PTGD_PTGD4
#define SENTIDO_M1_2  PTGD_PTGD5 
#define SENTIDO_M2_1  PTBD_PTBD4
#define SENTIDO_M2_2  PTBD_PTBD5

/*==================[internal data declaration]==============================*/

uint16_t calculateValueRight=0;
uint16_t calculateValueLeft=0;
uint16_t actualValueRight=0;
uint16_t actualValueLeft=0;
uint16_t lastValueRight=0;
uint16_t lastValueLeft=0;
uint8_t lowValue=0;

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[external functions definition]==========================*/

extern void setPwmValue(int valueToSetRight,int valueToSetLeft){
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
    

}

extern void calcularSentido(int sentido){
  
  if(sentido==FORWARD){
    SENTIDO_M1_1=0;
    SENTIDO_M1_2=1;   
    SENTIDO_M2_1=0;
    SENTIDO_M2_2=1;  
  }
  if(sentido==REVERSE){
    SENTIDO_M1_1=1;
    SENTIDO_M1_2=0;    
    SENTIDO_M2_1=1;
    SENTIDO_M2_2=0;  
    
  }
  if(sentido==TURN_RIGHT){
    SENTIDO_M1_1=0;
    SENTIDO_M1_2=1;    
    SENTIDO_M2_1=1;
    SENTIDO_M2_2=0; 
  }
  if(sentido==TURN_LEFT){
    SENTIDO_M1_1=1;
    SENTIDO_M1_2=0;    
    SENTIDO_M2_1=0;
    SENTIDO_M2_2=1; 
    
  }   
  
}

extern void stopLeftWheel(){
  TPM2C1SC=TPM2C1SC&0xf0; 
  
}

extern void stopRightWheel(){
  TPM2C0SC=TPM2C0SC&0xf0;
  
}

/*==================[internal functions definition]==========================*/