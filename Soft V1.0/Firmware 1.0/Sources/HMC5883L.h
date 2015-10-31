#ifndef HMC5883L_h
#define HMC5883L_h


/*==================[inclusions]=============================================*/


#include "IICModule.h"
#include "MPU6050.h"


/*==================[macros]=================================================*/

#define HMC5883L_Address 0x1E
#define ConfigurationRegisterA 0x00
#define ConfigurationRegisterB 0x01
#define ModeRegister 0x02
#define DataRegisterBegin 0x03

#define Measurement_Continuous 0x00
#define Measurement_SingleShot 0x01
#define Measurement_Idle 0x03

#define ErrorCode_1 "Entered scale was not valid, valid gauss values are: 0.88, 1.3, 1.9, 2.5, 4.0, 4.7, 5.6, 8.1"
#define ErrorCode_1_Num 1

/*==================[typedef]================================================*/
typedef struct 
{
	int XAxis;
	int YAxis;
	int ZAxis;
}MagnetometerScaled;

typedef struct
{
	int XAxis;
	int YAxis;
	int ZAxis;
}MagnetometerRaw;

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
MagnetometerRaw HMC5883L_ReadRawAxis();
MagnetometerScaled HMC5883L_ReadScaledAxis();
void HMC5883L_SetScale(int);
void HMC5883L_SetMeasurementMode(uint8_t );
void HMC5883L_Write(int , int );
uint8_t* HMC5883L_Read(int, int);
void GetHMC5883LRawMeasure(uint8_t*);

/*==================[end of file]============================================*/
#endif