#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#define setReg8(x,y) (x=y)
#define IIC_RepeatStart() IICC1_RSTA=1

void IIC1_Init(void);
void InitClock(void);

void delay(void);
void interrupt VectorNumber_Viic IIC(void);
void IIC_write_byte(byte);
byte IIC_read_byte(void);
void IIC_Start(void);
void IIC_Stop(Bool);
void configIIC(void);

int timeout,error;
byte iic1=0,iic2=0;

void main(void) {
  int i=0;
  EnableInterrupts; /* enable interrupts */
  /* include your code here */
  InitClock();
  IIC1_Init();
  configIIC();
  /*
  IIC_Start();
  IIC_write_byte(0x3D);
  IIC_write_byte(0x03);
  IIC_Stop();    */
  //iic1=IIC_read_byte();
  
  for(;;) {
    IIC_Start();
    IIC_write_byte(0x3C);
    IIC_write_byte(0x03);
    IIC_Stop(FALSE);
    IIC_write_byte(0x3D);
    while(i<6){
      
      iic1=IIC_read_byte();
      i++;
    }
    i=0;
    IIC_Stop(FALSE);
    //__RESET_WATCHDOG(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}




/*
void interrupt VectorNumber_Viic IIC(void){
(void)IICS;
IICS_IICIF=1;  
  
  
} */
  
  

  
void delay (void){
  unsigned int t=30000;
  while(t!=0){
  t--;
  }
}





void configIIC(void){
  IIC_Start();
  IIC_write_byte(0x3C);
  IIC_write_byte(0x02);
  IIC_write_byte(0x00);
  IIC_Stop(TRUE);
  
}





void IIC_write_byte(byte data)
{
 int i=0;
 //-------start of transmit first byte to IIC bus-----
 IICD = data;
 while (!IICS_IICIF); // wait until IBIF;
 IICS_IICIF=1; // clear the interrupt event flag;
 while(IICS_RXAK&&i<=100){ // check for RXAK;
    i++;
 }
  
 //-----Slave ACK occurred------------
 
 
}

void IIC_Start(void){
 
 IICS;
 IICS_IICIF=1;
 IICC1_MST=0;
 IICS_SRW=0;
 IICC1_TX=1;
 IICC1_MST=1;
 //IICC1_TXAK = 0; // RX/TX = 1; MS/SL = 1; TXAK = 0;
 //IICC1 |= 0x30; // And generate START condition;
 
}

void IIC_Stop(Bool type){
if(type){
  
  IICC1_MST = 0; // generate STOP condition;
} else{
  IICC1_RSTA=1;
  IICC1_RSTA=0;
}
}
  


byte IIC_read_byte(void)
{
 
 Byte RD_data;
 IICC1_TX = 0; // set up to receive;
 IICC1_TXAK = 1; // acknowledge disable;
 RD_data = IICD; // dummy read;
 while (!IICS_IICIF); // wait until IBIF;
 IICS_IICIF=1; // clear the interrupt event flag;
 RD_data = IICD; // read right data;
 return RD_data;
}

void IIC1_Init(void)
{
                           
  IICC1_IICEN=1;
  IICF=0x58; //0x58 --> 100KHz   0x40 --> 400KHz  
  
  
 // IICC1_IICEN=1;
  /* IICF: MULT1=0,MULT0=1,ICR5=0,ICR4=0,ICR3=0,ICR2=0,ICR1=0,ICR0=0 */
  //setReg8(IICF, 0x58);
  /* IICC2: GCAEN=0,ADEXT=0,??=0,??=0,??=0,AD10=0,AD9=0,AD8=0 */
  //setReg8(IICC2, 0x00);              
  
  /* IICC1: IICEN=1,IICIE=0,MST=0,TX=0,TXAK=0,RSTA=0,??=0,??=0 */
  //setReg8(IICC1, 0x80);
  /* IICS: TCF=1,IAAS=0,BUSY=0,ARBL=1,??=0,SRW=0,IICIF=1,RXAK=0 */
  //setReg8(IICS, 0x92);                 /* Clear the interrupt flags */                    
}

void InitClock(void){
   if (*(unsigned char*)0xFFAF != 0xFF) { /* Test if the device trim value is stored on the specified address */
    MCGTRM = *(unsigned char*)0xFFAF;  /* Initialize MCGTRM register from a non volatile memory */
    MCGSC = *(unsigned char*)0xFFAE;   /* Initialize MCGSC register from a non volatile memory */
  }
  /* MCGC2: BDIV=0,RANGE=0,HGO=0,LP=0,EREFS=0,ERCLKEN=0,EREFSTEN=0 */
  MCGC2= 0x00;                /* Set MCGC2 register */ 
  /* MCGC1: CLKS=0,RDIV=0,IREFS=1,IRCLKEN=1,IREFSTEN=0 */
  MCGC1=0x06;                /* Set MCGC1 register */ 
  /* MCGC3: LOLIE=0,PLLS=0,CME=0,??=0,VDIV=1 */
  MCGC3=0x01;                /* Set MCGC3 register */ 
  while(!MCGSC_LOCK) {                 /* Wait until FLL is locked */
  }
  SOPT1=0X06;
  return;
  
  
  
}

