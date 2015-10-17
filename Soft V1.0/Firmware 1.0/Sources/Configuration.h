


#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_


/*==================[inclusions]=============================================*/

#include "ConfigMicro.h"

/*==================[macros]=================================================*/



//-------------------estados globales-------------//
#define STATUS_START 0xB0
#define STATUS_RESET 0xB1
#define STATUS_STAND_BY 0xB2


//-------------------Buffers-------------//
#define BUFFER_SIZE 30


//Buffer de salida
#define BUFFEROUT_LENGTH 30
//Buffer de entrada
#define BUFFERIN_LENGTH 30
#define BUFFER_DATA_SIZE 6
#define EXECUTING_STRUCT_SIZE 20

//-------------------Sensores Ultrasonido-------------//

#define SENSOR_ULTRASONIC_FRONT 1
#define SENSOR_ULTRASONIC_LEFT 2
#define SENSOR_ULTRASONIC_RIGHT 3

//-------------------ID Funciones -------------//
# define getMeasure 0x01
# define getMeasureResponse 0x82
# define isGoal 0x02
# define setSteps 0x80
# define setVelocity 0x81
# define error 0x85
# define ACK 0x06

// Parametros de getMeasure
# define ULTRASONIC_ALL 7
# define ULTRASONIC_LEFT 8
# define ULTRASONIC_RIGHT 9
# define ULTRASONIC_FRONT 10
# define ACCEL 11
# define GYRO 12
# define COMPASS 13

// Parametros de  isGoal
# define STOP_ON_GOAL 14
# define CONTINUE 15
# define NOP 16

// Parametros de  error
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

//Timers funciones
# define ULTRASONIC_ALL_TIMER NO_TIMER
# define ULTRASONIC_LEFT_TIMER 3200
# define ULTRASONIC_RIGHT_TIMER 3200
# define ULTRASONIC_FRONT_TIMER 3200
# define ACCEL_TIMER 200
# define GYRO_TIMER 200
# define COMPASS_TIMER 200
# define IS_GOAL_TIMER 200
# define SET_STEPS_TIMER 200
# define SET_VELOCITY_TIMER 200
#define NO_TIMER 0xffff

//Definiciones para funciones con mas de una funcion
#define MORE_FUNCTION 0xff
#define UNIQUE_FUNCTION 0x00
#define MAX_CHILDREN 0x03

//-------------------Tipo de movimiento-------------//
#define STEPS 0x01
#define LINEAR_VELOCITY 0x02
#define NO_MOVE 0x03

//-------------------Sentido de motores-------------//
#define PENDIENTE 10
#define FORWARD 0x00
#define REVERSE 0x03
#define TURN_RIGHT 0x01
#define TURN_LEFT 0x02


//timers funciones
//#define getMeasure_TIMER 20


//-------------------Estados MEF Comunicacion-------------//

#define MEF_WAIT 0x01
#define MEF_START 0x02
#define MEF_FUNCTION 0x03
#define MEF_N_BYTES 0x04
#define MEF_DATA 0x05
#define MEF_TIME_OUT 0x06
#define MEF_ERROR 0x07
#define FUNCTION_ID 0x7F

//-------------------ADC-------------//

#define ADC_SAMPLE_FREQUENCY 1000

//-------------------Parametros de velocidad y pasos-------------//
#define MIN_SLOPE 10
#define ADC_OFF ADCSC1_ADCH=0xff;
#define RTC_BASE_TIME 3125
#define DEGREES_FOR_STEP 9



/*==================[typedef]================================================*/
#define uint8_t byte
#define uint16_t word
#define int32_t long
#define int32   long

/*==================[external data declaration]==============================*/



/*==================[external functions declaration]=========================*/





#endif
