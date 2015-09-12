#include "Config.h"
#ifndef _FunctionHandler_h
#define _FunctionHandler_h

#endif

uint16_t leftWheelSteps = 0;
uint16_t rightWheelSteps = 0;
uint16_t leftWheelVelocity = 0;
uint16_t rightWheelVelocity = 0;

void ultrasonicMessure(uint8_t something);
void accelMessure();
void gyroMessure();
void compassMessure();



/**
  @brief Inicializacion de buffer. 

  	Inicializa los parametros 'readPointer', 'writePointer' y 'buffer' de la estructura 'bufferStruct'.

  @param Buffer es el buffer (struct bufferStruct) a inicializar.

  @returns void

*/
void InitBuffer(BufferStruct BufferToInit);

/**
  @brief toma dato del buffer. 

  	toma un dato uint8_t del buffer e incrementa el puntero 'readPointer'.
  	Si no hay datos que leer no incrementa el puntero.
  	Lipia la celda luego de leerla.

  @param BufferToGet es el buffer (struct bufferStruct) a leer.

  @returns data Parametro uint8_t con el valor de la celda tomada del buffer.

  */
uint8_t getFromBuffer(BufferStruct BufferToGet);


/**
  @brief Setea un dato en el buffer. 

  	setea un dato uint8_t en el buffer e incrementa el puntero 'writePointer'.
  	Si no hay lugar en el buffer en donde setear el dato, lo descarta.

  @param BufferToSet es el buffer (struct bufferStruct) a escribir.

  @returns void.

  */
void setToBuffer(uint8_t data, BufferStruct BufferToSet);

/**
  @brief devuelve el espacio disponible en el buffer. 

    calcula el espacio disponible para almacenamiento en el buffer.

  @param BufferToCalculate es el buffer (struct bufferStruct) a calcular.

  @returns data Parametro uint8_t con el valor del espacio disponible para almacenamiento en el buffer.

  */
uint8_t getSpaceOfBuffer(BufferStruct BufferToCalculate);

/**
  @brief setea la cantidad de pasos a cada rueda. 

  @param leftSteps uint16_t que representa la cantidad de pasos de la rueda izquierda.
  @param rightSteps uint16_t que representa la cantidad de pasos de la rueda derecha.
  @returns void.

  */
  
//void setSteps(uint16_t leftSteps, uint16_t rightSteps);

/**
  @brief setea la velocidad a cada rueda. 

  @param leftVelocity uint16_t que representa la velocidad de la rueda izquierda.
  @param rightVelocity uint16_t que representa la velocidad de la rueda derecha.
  @returns void.

  */
//void setVelocity(uint16_t leftVelocity, uint16_t rightVelocity);

/**
  @brief Toma una instruccion del buffer de entrada y selecciona la funcion a ejecutar

  @returns void

  */
void functionHandler(void);
