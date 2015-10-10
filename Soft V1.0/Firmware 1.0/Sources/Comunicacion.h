
#ifndef _COMUNICACION_H_
#define _COMUNICACION_H_
#include "Config.h"





//Definiciones Trama de datos
#define FRAME_START 0xAA

#define DATA_IN_SIZE 0x1D;

//Definicion variables
static uint8_t nBytes;
uint8_t function;
static uint8_t singleData;
static uint8_t nData[30];
static uint8_t dataPointer=0;
static uint8_t txDataLength=0;
static uint8_t STATUS_MEF;

//Definicion de estructuras
BufferStruct bufferTx;
BufferStruct bufferRx;



//Definicion de funciones
void SendByte(byte);
interrupt VectorNumber_Vsci1rx  void RxInterrupt (void);
interrupt VectorNumber_Vsci1tx  void TxInterrupt (void);
interrupt VectorNumber_Vsci1err  void ErrorInterrupt (void);
void beginComunication();
void putDataIntoBuffer(void);
void sendDataAvailable (void);
void frameGenerator(void);

#endif

