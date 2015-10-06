#include "Comunicacion.h"
/**
@brief Envia una trama de datos por el puerto serial obtenida por el buffer de salida

*/

void SendByte(byte dato){


(void)statusSerialRegister1;
serialData=dato;
enableTxInterrupt;
return; 

}

void beginComunication(){
  STATUS_MEF=MEF_WAIT;
}


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

enableRxInterrupt;
if((inByte==FRAME_START)&&(STATUS_MEF==MEF_WAIT)){
  STATUS_MEF=MEF_START;
} else{
  
    if((STATUS_MEF==MEF_DATA)&&(dataPointer<nBytes)){
      setToBuffer(inByte,&bufferRx);
      dataPointer++;
    }
    
    if((STATUS_MEF==MEF_DATA)&&(dataPointer>=nBytes)){
      STATUS_MEF=MEF_WAIT;
      //setToBuffer(inByte,&bufferRx);
      dataPointer=0;
      setBufferOnBuffer(&bufferRx,&bufferIn);
     // InitBuffer(&bufferRx);
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
        //InitBuffer(&bufferRx);
        //Llamar a funcion para meter en el buffer
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


