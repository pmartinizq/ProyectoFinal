/*==================[inclusions]=============================================*/

#include "GlobalVariables.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

//ADC

Bool adcEnable=TRUE;
Bool isAdcRunning=FALSE;

//Velocidad

uint16_t leftWheelVelocity=0;
uint16_t rightWheelVelocity=0;

//Motores

uint8_t pwmLeftValue=0;
uint8_t pwmRightValue=0;

//Tipo de movimiento

uint8_t moveBy=NO_MOVE;

//IDnumber

uint8_t IDNumberExtern=0;

//Pasos
uint16_t leftWheelStepValue=0;
uint16_t rightWheelStepValue=0;
int leftWheelStepValueToSet=0;
int rightWheelStepValueToSet=0;

//Serial Error
uint8_t serialErrorType=0;

/*==================[external functions definition]==========================*/

void initIDNumber(void){
  IDNumberExtern = 1;
}

uint8_t getIDNumber(){
 uint8_t var = 0;
 var =  IDNumberExtern;
 if(IDNumberExtern <= 100){
  IDNumberExtern++;
 }
 else{
  IDNumberExtern = 1;
 }
 return var; 
}

void initGlobalVariables(void){
	//ADC
adcEnable=TRUE;
isAdcRunning=FALSE;
//Velocidad
leftWheelVelocity=0;
rightWheelVelocity=0;
//Motores
pwmLeftValue=0;
pwmRightValue=0;
//Tipo de movimiento
moveBy=NO_MOVE;
//IDnumber
IDNumberExtern=0;
//Pasos
leftWheelStepValue=0;
rightWheelStepValue=0;
leftWheelStepValueToSet=0;
rightWheelStepValueToSet=0;
setPwmValue(0,0);
serialErrorType=0;
}
/*==================[internal functions definition]==========================*/