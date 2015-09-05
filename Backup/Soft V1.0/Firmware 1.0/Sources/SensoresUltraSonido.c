#include "SensoresUltraSonido.h"

byte flagFrente,flagDerecha,flagIzquierda=0;
 
void Sensor1(FunctionStruct* currentFunction)                          //FRONTAL
{
  
  uint8_t t=0;
  ch0FunctionStruct=currentFunction;
  currentFunction->status=RUNNING;
  /*
  TIME1_CH0_DISABLE_INTERRUPT;
  
  SENSOR_FRONT_TRIGGER=1; //Flanco ascendente del pulso de trigger
  
  t=8;
  while(t!=0){
    t--;
  }
  SENSOR_FRONT_TRIGGER=0;//flanco descendente el pulso de trigger
 
  TIME1_CH0_ENABLE_INTERRUPT; */

  return;       
}

/*

void Sensor2(void)                                   //IZQUIERDO
{
  unsigned int t=8;
  unsigned long int a=650000;    
 
  TPM2SC=0B00001100;  
  TPM2C0SC=0B01000100;  //ascendente
  TPM2C0SC_CH0IE=1;
               
  
  PTCD_PTCD1=1;
  
  while(t!=0){
    t--;
  }
  
  
  PTCD_PTCD1=0;
  
  
  while(a!=0&&flagIzquierda==0) 
  {    
  a=a-1; 
  }
  flagIzquierda=0;
  TPM2C0SC_CH0F = 0;
  TPM2C0SC_CH0IE=0;
  bit1=0; 
  return;        
}


void Sensor3(void)                           //DERECHO
{
  unsigned int t=8;
  unsigned long int a=650000;    
 
  TPM2SC=0B00001100;  
  TPM2C1SC=0B01000100;  //ascendente
  TPM2C1SC_CH1IE=1;
 
  PTCD_PTCD0=1;
  
  t=8;
  while(t!=0){
    t--;
  }
  
  PTCD_PTCD0=0;
  
  while(a!=0&&flagDerecha==0) 
  {    
  a=a-1; 
  }
  
  flagDerecha=0;
  TPM2C1SC_CH1F = 0;
  TPM2C1SC_CH1IE=0;
  bit2=0; 
  return;        
}

void Sensor4(void)                           //TRASERO
{

  unsigned int a=20000;    
 
  TPM1C1SC_CH1IE=1;
  DisableInterrupts;
  TPM1C3VL = 0B00000000;
  PTED_PTED5=1;
  TPM1C3VL = 10;
  while(TPM1C3SC_CH3F==0);
  PTED_PTED5=0;
  EnableInterrupts;
  TPM1C3VL = 0B00000000;
  while(a!=0) 
  {    
  a=a-1; 
  }
  
  TPM1C1SC_CH1F = 0;
  TPM1C1SC_CH1IE=0;
  bit3=0; 
  return;        
}

*/
interrupt VectorNumber_Vtpm1ch0 void InterruptChannel0 (void)                        //sensor1 (frente)
{
  
  
  (void)(TPM1C0SC==0);//Borra el flag de interrupcion
  
  TPM1C0SC_CH0F = 0;
  if(mefStatus==MEF_STATUS_WAIT) //Si es el primer flanco(ascendente) toma el valor en b
  {  
    ch0FunctionStruct->status=RUNNING;
    risingEdgeTime=TIMER1_CH0_VALUE; 
    mefStatus=MEF_STATUS_RUNNING;//flag bit indica que ya fue tomado el primer flanco ascendente
    measureCh0Status=MEASURE_STATUS_RUNNING;
    //TPM1C0SC=0B01001000;
    return;
  }
  else         //flag bit=1 indica que ya fue tomado el primer flanco ahora se captura el flanco descendente
  {  
    fallingEdgeTime=TIMER1_CH0_VALUE;
    mefStatus=MEF_STATUS_WAIT;
    ch0Time=fallingEdgeTime-risingEdgeTime;//d es la medicion, resta los tiempos de muuestra de ambos flancos
    measureCh0Status=MEASURE_STATUS_DONE;
    measureUltrasonicCenterSensor16=ch0Time/54;
    ch0Datos.data[0]=(byte)measureUltrasonicCenterSensor16;
    ch0Datos.pointer=1;
    ch0FunctionStruct->data=&ch0Datos;
    ch0FunctionStruct->status=AVAILABLE;
    measureCh0Status=MEASURE_STATUS_WAIT;
    TIME1_CH0_DISABLE_INTERRUPT;
    measureUltrasonicCenterSensor16=ch0Time/54;
  }
  return;   
}

/*
interrupt 16 void CH1 (void)                             //sensor2(Iquierda)
{
  static word b1=0,c1=0;
  
  (void)(TPM2C0SC==0);
  TPM2C0SC_CH0F = 0;
  if(bit1==0)
  {  
  b1=TPM2C0V;
  bit1=1;
  TPM2C0SC=0B01001000;
  return;
  }
  else
  {  
  c1=TPM2C0V;
  bit1=0;
  d2=c1-b1;
  flagIzquierda=1;
  }
  return;   
} 

interrupt 17 void CH2 (void)                             //SENSOR3 (derecha)
{
  static word b2=0,c2=0;
  
  (void)(TPM2C1SC==0);
  TPM2C1SC_CH1F = 0;
  if(bit2==0)
  {  
  b2=TPM2C1V;
  bit2=1;
  TPM2C1SC=0B01001000;
  return;
  }
  else
  {  
  c2=TPM2C1V;
  bit2=0;
  d3=c2-b2;
  flagDerecha=1;
  }
  return;   
} 

interrupt 10 void CH3 (void)                                //SENSOR4
{
  static word b3=0,c3=0;
  
  (void)(TPM1C1SC==0);
  TPM1C1SC_CH1F = 0;
  if(bit3==0)
  {  
  b3=TPM1C1V;
  bit3=1;
  return;
  }
  else
  {  
  c3=TPM1C1V;
  bit3=0;
  d4=c3-b3;
  }
  return;   
}  */