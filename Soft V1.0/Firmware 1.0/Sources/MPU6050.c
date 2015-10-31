

/*==================[inclusions]=============================================*/
#include "MPU6050.h"


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
uint8_t devAddr=0,buffer=0;
/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/
void MPU6050(void){
  devAddr=MPU6050_DEFAULT_ADDRESS;
}
void MPU6050_initialize() {
    MPU6050_setClockSource(MPU6050_CLOCK_PLL_XGYRO);
    MPU6050_setFullScaleGyroRange(MPU6050_GYRO_FS_250);
    MPU6050_setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
    MPU6050_setSleepEnabled(FALSE); 
}

void MPU6050_setClockSource(uint8_t source) {
    IICWriteBits(devAddr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, source);
}

void MPU6050_setFullScaleAccelRange(uint8_t range) {
    IICWriteBits(devAddr, MPU6050_RA_ACCEL_CONFIG, MPU6050_ACONFIG_AFS_SEL_BIT, MPU6050_ACONFIG_AFS_SEL_LENGTH, range);
}
void MPU6050_setFullScaleGyroRange(uint8_t range) {
    IICWriteBits(devAddr, MPU6050_RA_GYRO_CONFIG, MPU6050_GCONFIG_FS_SEL_BIT, MPU6050_GCONFIG_FS_SEL_LENGTH, range);
}
void MPU6050_setSleepEnabled(Bool enabled) {
    IICWriteBit(devAddr, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT, enabled);
}
void MPU6050_setI2CMasterModeEnabled(Bool enabled) {
    IICWriteBit(devAddr, MPU6050_RA_USER_CTRL, MPU6050_USERCTRL_I2C_MST_EN_BIT, enabled);
}
void MPU6050_setI2CBypassEnabled(Bool enabled) {
    IICWriteBit(devAddr, MPU6050_RA_INT_PIN_CFG, MPU6050_INTCFG_I2C_BYPASS_EN_BIT, enabled);
}

void MPU6050GetRawMotion6(uint8_t* buffer) {
    IICReadNBytes(devAddr, MPU6050_RA_ACCEL_XOUT_H, 14,buffer);
    
}




/*==================[end of file]============================================*/