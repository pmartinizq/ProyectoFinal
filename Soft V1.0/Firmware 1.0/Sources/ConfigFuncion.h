#include "Config.h"


#ifndef _ConfigFuncion_h
#define _ConfigFuncion_h

#endif

//****Definiciones de funciones **////

//Error
#define Error 0x02
#define COMMAND_ERROR 0xAA
#define INACCESIBLE_DEVICE 0xAB
#define TIMEOUT 0xAC
//ACK
#define Ack 0x01
//SetStatus
#define SetStatus 0x05
#define START 0xB0
#define RESET 0xB1
#define STAND-BY 0xB2
//SetGoalMode
#define SetGoalMode 0x04
#define STOP_ON_GOAL 0xAD
#define CONTINUE 0xAE
#define ALERT 0xAF 
//GetMeasure
#define GetMeasure 0x04
#define ULTRASONIC_RIGTH  0xB3
#define ULTRASONIC_LEFT  0xB4
#define ULTRASONIC_FRONT  0xB5
#define ULTRASONIC_ALL 0xB6
#define ACCEL 0xB7
#define GYRO 0xB8
#define COMPASS 0xB9

//SetVelocity
#define SetVelocity  0x80	
//SetStep
#define SetStep   0x81

//Definicion de registros del microprocesador

#define outRegister SCI1D

void frameGenerator(void);



 


