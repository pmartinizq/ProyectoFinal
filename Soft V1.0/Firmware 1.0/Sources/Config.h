
#include "ConfigJM16.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef _Config_h
#define _Config_h


//Definicion de tipos de datos
#define uint8_t byte
#define uint16_t word
#define int32_t long
#define int32   long

//Definicion estados globales
#define STATUS_START 0xB0
#define STATUS_RESET 0xB1
#define STATUS_STAND_BY 0xB2

#define BUFFER_SIZE 15

//Definiciones 
extern uint8_t GLOBAL_STATUS;

//Buffer de salida
#define BUFFEROUT_LENGTH 30
//Buffer de entrada
#define BUFFERIN_LENGTH 30

#define BUFFER_DATA_SIZE 6
#define EXECUTING_STRUCT_SIZE 20


//definiciones para sensores ultrasonicos
#define SENSOR_ULTRASONIC_FRONT 1
#define SENSOR_ULTRASONIC_LEFT 2
#define SENSOR_ULTRASONIC_RIGHT 3

// Funciones 
# define getMeasure 0x01
# define getMeasureResponse 0x82
# define isGoal 0x02
# define setSteps 0x80
# define setVelocity 0x81
# define error 0x85
# define ACK 0x06

// parametros de getMeasure
# define ULTRASONIC_ALL 7
# define ULTRASONIC_LEFT 8
# define ULTRASONIC_RIGHT 9
# define ULTRASONIC_FRONT 10
# define ACCEL 11
# define GYRO 12
# define COMPASS 13

// parametros de  isGoal
# define STOP_ON_GOAL 14
# define CONTINUE 15
# define NOP 16

// parametros de  error
# define COMMAND_ERROR 17
# define INACCESSIBLE_DEVICE 18
# define ERROR_TIMEOUT 19
# define ERROR_FUNCTION 130



//Estados de funciones
# define READY 20
# define RUNNING 21
# define AVAILABLE 22
# define ERROR 23
# define TIMEOUT 24
# define DONE 25

//timers funciones
# define ULTRASONIC_ALL_TIMER 255
# define ULTRASONIC_LEFT_TIMER 100
# define ULTRASONIC_RIGHT_TIMER 100
# define ULTRASONIC_FRONT_TIMER 100
# define ACCEL_TIMER 200
# define GYRO_TIMER 200
# define COMPASS_TIMER 200
# define IS_GOAL_TIMER 200
# define SET_STEPS_TIMER 200
# define SET_VELOCITY_TIMER 200
#define NO_TIMER 255

//Definiciones para funciones con mas de una funcion
#define MORE_FUNCTION 0xff
#define UNIQUE_FUNCTION 0x00
#define MAX_CHILDREN 0x03


//timers funciones
#define getMeasure_TIMER 20

//Punteros de lectura y escritura
extern uint8_t readPointerBufferOut;
extern uint8_t writePointerBufferOut;
static uint16_t kbiSampleFreq=1000,adcSampleFreq=1000;
extern uint16_t measureUltrasonicCenterSensor16;

//variables sensor meta
extern int goalStatus;

//motores
static uint8_t pwmLeftValue=0,pwmRightValue=0;


static uint8_t STATUS_MEF;


//Definicion estados MEF

#define MEF_WAIT 0x01
#define MEF_START 0x02
#define MEF_FUNCTION 0x03
#define MEF_N_BYTES 0x04
#define MEF_DATA 0x05
#define MEF_TIME_OUT 0x06
#define MEF_ERROR 0x07
#define FUNCTION_ID 0x7F


#pragma options align = packed
typedef struct  
{
uint8_t readPointer;
uint8_t writePointer;
uint8_t Buffer[ BUFFER_SIZE ];
uint8_t BufferFlags[ BUFFER_SIZE ];
}BufferStruct;

typedef struct  
{
uint8_t data[BUFFER_DATA_SIZE];
uint8_t pointer;
}DataStruct;

typedef struct  
{
uint8_t functionParameter;
uint8_t functionId;
uint8_t status;
uint8_t timerCount;
DataStruct* data;
uint8_t root;
}FunctionStruct;

typedef struct  
{
FunctionStruct vector[EXECUTING_STRUCT_SIZE];
uint8_t pointer;
uint8_t readPointer;

}ExecutingStruct;


#pragma options align = reset

extern BufferStruct bufferIn;
extern BufferStruct bufferOut;
static ExecutingStruct executingVector;
extern FunctionStruct f1;

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

void setToExecutingVector(FunctionStruct*);
FunctionStruct* getFromExecutingVector(void);
uint8_t getExecutingVectorPointer(void);
void initExecutingVector(void);
FunctionStruct* getFromExecutingVectorOnIndex(uint8_t position);
FunctionStruct* getChildOf(uint8_t);
uint8_t isDataAvailable(BufferStruct *);
FunctionStruct* newFunctionInExecutingVector(void);
FunctionStruct* setFunctionToExecutingVector(FunctionStruct);

#endif
