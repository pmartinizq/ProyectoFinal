/*==================[inclusions]=============================================*/

#include "SerialPort.h" 

/*==================[macros and definitions]=================================*/

//Definiciones Trama de datos

#define FRAME_START 0xAA
#define DATA_IN_SIZE 0x1D;

//COMUNICACION

#define serialData SCI1D
#define clockRegister(x,y) (y=SCI1BDL,x=SCI1BDH)
#define enableTxInterrupt (SCI1C2_TCIE=1)
#define enableRxInterrupt (SCI1C2_RIE=1)
#define disableTxInterrupt (SCI1C2_TCIE=0)
#define disableRxInterrupt (SCI1C2_RIE=0)
#define statusSerialRegister1 SCI1S1
#define statusSerialRegister2 SCI1S2

/*==================[internal data declaration]==============================*/

static uint8_t nBytes;
uint8_t function;
static uint8_t dataPointer=0;
static uint8_t txDataLength=0;

BufferStruct bufferTx;
BufferStruct bufferRx;

/*==================[internal functions declaration]=========================*/

void SendByte(byte);
void beginComunication();

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

uint8_t STATUS_MEF=MEF_WAIT;

/*==================[external functions definition]==========================*/

interrupt VectorNumber_Vsci1tx  void TxInterrupt (void) {   //rutina para enviar datos por interrupciones

(void)statusSerialRegister1;      //borra flags de interrupcion

if(txDataLength>0&&isDataAvailable(&bufferTx)){
  enableTxInterrupt;  
  serialData=getFromBuffer(&bufferTx);
  txDataLength--;
} else{
  
  disableTxInterrupt;
}
return;
}

interrupt VectorNumber_Vsci1rx  void RxInterrupt (void) {  //Rutina para recepcion de datos por interrupciones

byte inByte=0;
(void) statusSerialRegister1; //borra flags de interrupcion
inByte=serialData;


if((inByte==FRAME_START)&&(STATUS_MEF==MEF_WAIT)){
  STATUS_MEF=MEF_START;
  InitBuffer(&bufferRx);
} else{
  
    if((STATUS_MEF==MEF_DATA)&&(dataPointer<nBytes)){
      setToBuffer(inByte,&bufferRx);
      dataPointer++;
    }
    
    if((STATUS_MEF==MEF_DATA)&&(dataPointer>=nBytes)){
      STATUS_MEF=MEF_WAIT;
      dataPointer=0;
      setBufferOnBuffer(&bufferRx,&bufferIn);
    }
      
      
    
    if(STATUS_MEF==MEF_N_BYTES){
        STATUS_MEF=MEF_DATA;
        setToBuffer(inByte,&bufferRx);
        dataPointer++;
        
      } 
      
    if(STATUS_MEF==MEF_FUNCTION){
    
      if(function>FUNCTION_ID){
        nBytes=inByte;
        setToBuffer(inByte,&bufferRx);
        STATUS_MEF=MEF_N_BYTES;
      } else{
        setToBuffer(inByte,&bufferRx);
        STATUS_MEF=MEF_WAIT;
        setBufferOnBuffer(&bufferRx,&bufferIn);
        
      }
        
    }
    if(STATUS_MEF==MEF_START){
      STATUS_MEF=MEF_FUNCTION;
      function=inByte;
      setToBuffer(inByte,&bufferRx);
    }
      
  
  }
}

interrupt VectorNumber_Vsci1err  void ErrorInterrupt (void) {

(void)(SCI1S1==0);

}

void frameGenerator(){
  
 uint8_t getByte,i=0,nbytes=0;
 if(isDataAvailable(&bufferOut)==1){
 disableTxInterrupt; 
 do{
    //
 getByte=getFromBuffer(&bufferOut);
  if(getByte<=FUNCTION_ID){
  setToBuffer(FRAME_START,&bufferTx);
  txDataLength++;
  setToBuffer(getByte,&bufferTx);
  txDataLength++;
  getByte=getFromBuffer(&bufferOut);
  setToBuffer(getByte,&bufferTx);
  txDataLength++;
}else{
  
  setToBuffer(FRAME_START,&bufferTx);
  txDataLength++;
  if(getByte==getMeasureResponse){ 
   getByte=getMeasure;
  }
  setToBuffer(getByte,&bufferTx);
  txDataLength++;
  nbytes=getFromBuffer(&bufferOut);
  setToBuffer(nbytes,&bufferTx);
  txDataLength++;
  for(i=0;i<nbytes;i++){
     getByte=getFromBuffer(&bufferOut);
     setToBuffer(getByte,&bufferTx);
     txDataLength++;
  }
  
}
 }while(isDataAvailable(&bufferOut)==1);
  txDataLength=txDataLength-1;
  SendByte(getFromBuffer(&bufferTx));
 }
  
}

/*==================[internal functions definition]==========================*/

/**
  @brief Envia una trama de datos por el puerto serial obtenida por el buffer de salida
  @param dato byte a ser enviado
*/
void SendByte(byte dato){

(void)statusSerialRegister1;
serialData=dato;
enableTxInterrupt;
return; 

}

/**
  @brief inicializa la MEF de recepcion de datos.
*/
void beginComunication(){
  STATUS_MEF=MEF_WAIT;
}