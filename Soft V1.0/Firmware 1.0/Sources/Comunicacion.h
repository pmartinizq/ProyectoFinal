#include "Config.h"
#ifndef _Comunicacion_h
#define _Comunicacion_h


#endif
//Definicion estados MEF
uint8_t STATUS_MEF;
#define MEF_WAIT 0x01
#define MEF_START 0x02
#define MEF_FUNCTION 0x03
#define MEF_N_BYTES 0x04
#define MEF_DATA 0x05
#define MEF_TIME_OUT 0x06
#define MEF_ERROR 0x07
#define FUNCTION_ID 0x7F


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

//Definicion de estructuras
BufferStruct bufferTx;
extern BufferStruct bufferRx;



//Definicion de funciones
void SendByte(byte);
interrupt VectorNumber_Vsci1rx  void RxInterrupt (void);
interrupt VectorNumber_Vsci1tx  void TxInterrupt (void);
void beginComunication();
void putDataIntoBuffer(void);
void sendDataAvailable (void);
void frameGenerator(void);

