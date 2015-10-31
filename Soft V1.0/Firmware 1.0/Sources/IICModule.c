/*==================[inclusions]=============================================*/
#include "IICModule.h"

/*==================[macros and definitions]=================================*/

#define REPEAT_START IICC_RSTA=1
/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
void IIC1_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_Delay (void);

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/





void IIC1_Init(void)
{
  IICF_MULT=0x00;
  IICF_ICR=0x20; //100kHz                         
  IICC1_IICEN=1;   
              
}


void IIC_Start(void){
  (void)(IICS==0);
  IICC_IICEN=1;
  IICC_TX=1;
  IICC_MST = 1; 
 
}

void IIC_Stop(void){
  
  IICC1_MST = 0; // generate STOP condition;
  IICC_IICEN=0;
}

byte IIC_read_byte(Bool more)
{
 unsigned int time=40000;
 uint8_t RD_data,error;
 IICC1_TX = 0; // set up to receive;
 if(more==TRUE){
  
 IICC1_TXAK = 0; 
 }else{
  IICC1_TXAK = 1; 
  
 }
 RD_data = IICD; // dummy read;
 while (!IICS_IICIF){
  time--;
 }
 IICS_IICIF=1; // clear the interrupt event flag;
 if(time==0){
  error=1;
 }else{
  RD_data = IICD;
 }
 
 return RD_data;
}

void IIC_write_byte(byte* data)
{
 int i=0,time=10000;
 //-------start of transmit first byte to IIC bus-----
 IICD = *data;
 while (!IICS_IICIF){
  time--;
 }
 IICS_IICIF=1; // clear the interrupt event flag;
 while(IICS_RXAK){ // check for RXAK;
    
 }

}


void IIC_Delay (void){
  unsigned int t=8; //10uS
  while(t!=0){
  t--;
  }
}


/*==================[external functions definition]==========================*/

void IICWriteRegister(byte address,byte reg,byte data){
  uint8_t dato;
  IIC_Start();
  IIC_Delay();
  dato=(address<<1)|0x00;
  IIC_write_byte(&dato);
  dato=reg;
  IIC_write_byte(&dato);
  dato=data;  
  IIC_write_byte(&dato);
  IIC_Stop();
}

void IICReadByte(byte address,byte reg,byte* data){
  uint8_t dato;
  IIC_Start();
  dato=(address<<1)|0x00;
  IIC_write_byte(&dato);
  dato=reg;
  IIC_write_byte(&dato);
  REPEAT_START;
  dato=(address<<1)|0x01;
  IIC_write_byte(&dato);
  *data=IIC_read_byte(FALSE);
  IIC_Delay();
  IIC_Stop();
  
}

void IICReadNBytes(byte address,byte reg,byte n,byte* data){
  uint8_t dato;
  byte i=0;
  i=0;
  IIC_Start();
  dato=(address<<1)|0x00;
  IIC_write_byte(&dato);
  dato=reg;
  IIC_write_byte(&dato);
  REPEAT_START;
  dato=(address<<1)|0x01;
  IIC_write_byte(&dato);  
  while(i<n-1){    
    data[i]=IIC_read_byte(TRUE);
    i++;
  }
  data[i]=IIC_read_byte(FALSE);
  IIC_Stop();  
  
}

void IICWriteBit(uint8_t address,uint8_t reg,uint8_t nbit,Bool state){
uint8_t regSetValue=0,regActualValue;
IICReadByte(address,reg,&regActualValue);
if(state==TRUE){
  regSetValue=0x01;
  regSetValue=regSetValue<<nbit;
  regSetValue=regSetValue | regActualValue;
}else{
  regSetValue=0xFE;
  regSetValue=regSetValue<<nbit;
  regSetValue=regSetValue & regActualValue;
}
IICWriteRegister(address,reg,regSetValue); 
  
  
}

void IICWriteBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data){
uint8_t b,mask;
    IICReadByte(devAddr, regAddr, &b); 
        mask = ((1 << length) - 1) << (bitStart - length + 1);
        data <<= (bitStart - length + 1); // shift data into correct position
        data &= mask; // zero all non-important bits in data
        b &= ~(mask); // zero all important bits in existing byte
        b |= data; // combine data with existing byte
        IICWriteRegister(devAddr, regAddr, b);
    
  
  
}

/*==================[end of file]============================================*/
  