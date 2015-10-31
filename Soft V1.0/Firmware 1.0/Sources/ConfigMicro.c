/*==================[inclusions]=============================================*/

#include "ConfigMicro.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

void InitReg(void);
void InitClock(void);
void InitComunication(void);
void InitInputCompare(void);
void InitPwm(void);
void InitADC(void);
void InitPorts(void);
void InitRtc(void);

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[external functions definition]==========================*/

extern void InitDevice(void){
  DisableInterrupts;
  InitReg();  
  InitClock();
  InitComunication();  
  InitPorts();
  InitInputCompare();
  beginComunication();
  initExecutingVector();
  initIDNumber();
  EnableInterrupts;
  InitPwm();
  InitADC();  
  InitRtc();
}

/*==================[internal functions definition]==========================*/

/**
@brief Inicializa interrupciones.
*/
void InitReg(void){
  EnableInterrupts;
  SOPT1=0X06;
  USBCTL0_USBVREN=1;
}

/**
@brief Inicializa y ajusta el reloj interno del microcontrolador
*/
void InitClock(void){
 if (*(unsigned char*)0xFFAF != 0xFF) { /* Test if the device trim value is stored on the specified address */
    MCGTRM = *(unsigned char*)0xFFAF;  /* Initialize MCGTRM register from a non volatile memory */
    MCGSC = *(unsigned char*)0xFFAE;   /* Initialize MCGSC register from a non volatile memory */
  }
  MCGTRM =0xBB;
  /* MCGC2: BDIV=0,RANGE=0,HGO=0,LP=0,EREFS=0,ERCLKEN=0,EREFSTEN=0 */
  MCGC2= 0x00;                /* Set MCGC2 register */ 
  /* MCGC1: CLKS=0,RDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
  MCGC1=0x06;                /* Set MCGC1 register */ 
  /* MCGC3: LOLIE=0,PLLS=0,CME=0,??=0,VDIV=1 */
  MCGC3=0x01;                /* Set MCGC3 register */ 
  while(!MCGSC_LOCK) {                 /* Wait until FLL is locked */
  }
  return;
}

/**
@brief Inicializa los registros relacionados con 
la comunicacion serie del microcontrolador
*/
void InitComunication(void){ 
  SCI1S2=0x00;  //Configura el bit rate del SCI
  SCI1BDH=0x00;
  SCI1BDL=0x0A;//115200
  
  SCI1C1=0x00;
  SCI1C3=0x00;  
  SCI1C2=0x2C;
   
  #ifdef PARITY_CHECK
    SCI1C1_PE=1;
    SCI1C1_PT=0;
    SCI1C1_M=1;
    SCI1C3_PEIE=1;
  #else
    SCI1C1_PE=0;
    SCI1C1_PT=0;
    SCI1C1_M=0;
    SCI1C3_PEIE=0;
  #endif
  
  #ifdef FRAMMING_CHECK
    SCI1C3_FEIE=1;
  #else
    SCI1C3_FEIE=0;
  #endif
   
  
  (void)(SCI1S1); //borra posibles flags activados     
  return;
}

/**
@brief Establece configuracion del canal y el timer,
inicializa imput compare.
*/
void InitInputCompare(){
  //CONFIGURACION DE CANAL Y TIMER
 TPM1SC=0B00001100;  
 TPM1C0SC=0B00001100; 
 TPM1C1SC=0B00001100;
 TPM1C2SC=0B00001100;
 TPM1C3SC=0B00001100;  
}

/**
@brief Inicializa los registros relacionados con 
el PWM.
*/
void InitPwm(){
  TPM2SC=0B00001111; 
  TPM2MODH=PWM_FREQ_HIGH;
  TPM2MODL=PWM_FREQ_LOW;          
}

/**
@brief Inicializa los registros relacionados con 
el modulo ADC.
*/
void InitADC(){
  APCTL1=0x03;
  APCTL2=0x03;
  ADCCFG=0b00010000;
  ADCSC2=0b10000000;
  ADCSC1=0b11011111;
  (void)ADCRH;
  (void)ADCRL; 
}
  
/**
@brief Inicializa los puertos.
*/
void InitPorts(){ 
  PTADD=0X00;
  PTBDD=0XFF;
  PTCDD=0X03;
  PTDDD=0X08;
  PTEDD=0X70;
  PTEDD_PTEDD4=1;
  PTFDD=0XFF;
  PTGDD=0XFF;
  PTEPE=0B10000000;
}

/**
@brief Inicializa los registros relacionados con 
el RTC.
*/
void InitRtc(){
  RTCMOD=0x00;
  RTCSC=0x58;
}