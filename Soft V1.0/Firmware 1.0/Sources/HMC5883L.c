/*==================[inclusions]=============================================*/
#include "HMC5883L.h"



/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
int m_Scale;
/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/



void HMC5883L()
{
  m_Scale = 1;
  MPU6050_setI2CMasterModeEnabled(FALSE);
  MPU6050_setI2CBypassEnabled(TRUE) ;
  MPU6050_setSleepEnabled(FALSE);
}

MagnetometerRaw HMC5883L_ReadRawAxis()
{
 uint8_t buffer[10];
 MagnetometerRaw raw;

 IICReadNBytes(HMC5883L_Address,DataRegisterBegin,6,&buffer);
  
  raw.XAxis = (buffer[0] << 8) | buffer[1];
  raw.ZAxis = (buffer[2] << 8) | buffer[3];
  raw.YAxis = (buffer[4] << 8) | buffer[5];
  return raw;
}

MagnetometerScaled HMC5883L_ReadScaledAxis()
{
long aux;
  MagnetometerScaled scaled ;
  MagnetometerRaw raw = HMC5883L_ReadRawAxis();
  aux=raw.XAxis * m_Scale;
  scaled.XAxis = aux/10;
  aux=raw.ZAxis * m_Scale;
  scaled.ZAxis = aux/10;
  aux=raw.YAxis * m_Scale;
  scaled.YAxis = aux/10;
  return scaled;
}

void HMC5883L_SetScale(int gauss)
{
	uint8_t regValue = 0x00;
	if(gauss == 88)
	{
		regValue = 0x00;
		m_Scale = 73;
	}
	else if(gauss == 130)
	{
		regValue = 0x01;
		m_Scale = 92;
	}
	else if(gauss == 190)
	{
		regValue = 0x02;
		m_Scale = 122;
	}
	else if(gauss == 250)
	{
		regValue = 0x03;
		m_Scale = 152;
	}
	else if(gauss == 400)
	{
		regValue = 0x04;
		m_Scale = 227;
	}
	else if(gauss == 470)
	{
		regValue = 0x05;
		m_Scale = 256;
	}
	else if(gauss == 560)
	{
		regValue = 0x06;
		m_Scale = 303;
	}
	else if(gauss == 810)
	{
		regValue = 0x07;
		m_Scale = 435;
	}
	
	
	// Setting is in the top 3 bits of the register.
	regValue = regValue << 5;
	IICWriteRegister(HMC5883L_Address,ConfigurationRegisterB, regValue);
}

void HMC5883L_SetMeasurementMode(uint8_t mode)
{
	IICWriteRegister(HMC5883L_Address,ModeRegister, mode);
}

void GetHMC5883LRawMeasure(uint8_t* buffer){
 MPU6050();  
 HMC5883L();
 HMC5883L_SetScale(13);
 HMC5883L_SetMeasurementMode(Measurement_Continuous); 
 IICReadNBytes(HMC5883L_Address,DataRegisterBegin,6,buffer);
 
  
}



/*==================[end of file]============================================*/