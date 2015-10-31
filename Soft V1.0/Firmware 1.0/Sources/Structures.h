#ifndef STRUCTURES_H_
#define STRUCTURES_H_

/*==================[inclusions]=============================================*/

#include "Configuration.h"
#include <stdint.h>

/*==================[macros]=================================================*/

/*==================[typedef]================================================*/

typedef struct  
{
  uint8_t readPointer;
  uint8_t writePointer;
  uint8_t Buffer[ BUFFER_SIZE ];
  uint8_t BufferFlags[ BUFFER_SIZE ];
}BufferStruct;

typedef struct  
{
  uint8_t IDNumber;
  uint8_t functionParameter;
  uint8_t functionId;
  uint8_t status;
  uint16_t timerCount;
  uint8_t data[BUFFER_DATA_SIZE];
  uint8_t dataSize;
  uint8_t root;
}FunctionStruct;

typedef struct  
{
  FunctionStruct vector[EXECUTING_STRUCT_SIZE];
  uint8_t pointer;
  uint8_t readPointer;
}ExecutingStruct;


/*==================[external data declaration]==============================*/

extern BufferStruct bufferIn;
extern BufferStruct bufferOut;
extern ExecutingStruct executingVector;

/*==================[external functions declaration]=========================*/

/**
  @brief Inicializacion de buffer. 

  	Inicializa los parametros 'readPointer', 'writePointer' y 'buffer' de la estructura 'bufferStruct'.

  @param Buffer es el buffer (struct bufferStruct) a inicializar.

  @returns void

  */
void InitBuffer(BufferStruct* BufferToInit);

/**
  @brief toma dato del buffer. 

  	toma un dato uint8_t del buffer e incrementa el puntero 'readPointer'.
  	Si no hay datos que leer no incrementa el puntero.
  	Lipia la celda luego de leerla.

  @param BufferToGet es el buffer (struct bufferStruct) a leer.

  @returns data Parametro uint8_t con el valor de la celda tomada del buffer.

  */
uint8_t getFromBuffer(BufferStruct* BufferToGet);
/**
  @brief Setea un dato en el buffer. 

  	setea un dato uint8_t en el buffer e incrementa el puntero 'writePointer'.
  	Si no hay lugar en el buffer en donde setear el dato, lo descarta.

  @param BufferToSet es el buffer (struct bufferStruct) a escribir.

  @returns void.

  */
  
 void setToBuffer(uint8_t data, BufferStruct* BufferToSet);

/**
  @brief devuelve el espacio disponible en el buffer. 

    calcula el espacio disponible para almacenamiento en el buffer.

  @param BufferToCalculate es el buffer (struct bufferStruct) a calcular.

  @returns data Parametro uint8_t con el valor del espacio disponible para almacenamiento en el buffer.

  */
uint8_t getSpaceOfBuffer(BufferStruct* BufferToCalculate);

/**
  @brief setea los datos de un buffer en otro buffer. 

  	controla si el buffer es capaz de almacenar la cantidad de datos a guardar antes de realizar el proceso de almacenamiento.
  	devuelve 1 si el proceso fue exitoso y 0 si no lo fue.

  @param BufferGet es el buffer (struct bufferStruct) que contiene los datos a ser almacenado en bufferAdd.
  @param BufferAdd es el buffer (struct bufferStruct) que contendra los datos a almacenar.

  @returns data Parametro uint8_t con el valor 1 si el proceso fue exitoso, 0 si no lo fue.

  */
uint8_t setBufferOnBuffer(BufferStruct* BufferGet, BufferStruct* BufferAdd);


/**
  @brief obtiene puntero de la estructura executingVector.

  @returns uint8_t con el valor del puntero.

  */
uint8_t getExecutingVectorPointer(void);

/**
  @brief inicializa el vector de ejecucion.

  */
void initExecutingVector(void);

/**
  @brief obtiene una funcion del vector de ejecucion apartir de un indice.

  @param position indice en el cual buscar la funcion.

  @returns functionStruct puntero a funcion requerida del vector de ejecucion.

  */
FunctionStruct* getFromExecutingVectorOnIndex(uint8_t position);

//FunctionStruct* getChildOf(uint8_t);

/**
  @brief devuelve 1 si hay datos en el buffer y 0 si no lo hay.

  @param BufferStruct puntero al buffer al cual queremos verificar.

  @returns valor 1 o 0 dependiendo si hay o no datos en el buffer.

  */
uint8_t isDataAvailable(BufferStruct *);

/**
  @brief agrega una funcion al vector de ejecucion.
  @param FunctionStruct funcion a agregar al vector.

  @returns FunctionStruct retorna puntero a la funcion agregada al vector.

  */
FunctionStruct* setFunctionToExecutingVector(FunctionStruct);

#endif