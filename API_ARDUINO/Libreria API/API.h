#ifndef _API_H_
#define _API_H_


#define START_BYTE 10

#define GETMEASSURE 1
#define SETVELOCITY 2
#define SETSTEPS 3
#define ISGOAL 4
#define ACK 5
#define ERROR 6


#define ULTRASONIC_RIGTH 1 
#define ULTRASONIC_LEFT 2
#define ULTRASONIC_FRONT 3
#define ULTRASONIC_ALL 4
#define ACCEL 5
#define GYRO 6
#define COMPASS 7

#define STOP_ON_GOAL 1
#define CONTINUE 2
#define NOP 3
#define ISGOAL_TRUE 1
#define ISGOAL_FALSE 0

#define COMMAND_ERROR 1
#define INACCESSIBLE_DEVICE 2
#define TIMEOUT 3


#define writeSerial(x) (Serial1.write(x))
#define availableSerial() (Serial1.available())
#define readSerial() (Serial1.read())

uint8_t variable;
uint8_t counter;
uint8_t auxCounter;
uint8_t result[3];
bool boolResult;
uint8_t getResponse;

uint8_t GetMeassure(uint8_t TYPE);

bool SetVelocity(uint16_t leftWheelVelocity, uint16_t rightWheelVelocity);
bool SetSteps(uint16_t leftWheelSteps, uint16_t rightWheelSteps);

bool IsGoal(uint8_t MODE);
void Send(uint8_t DATA);
uint8_t Get();
void ErrorPrint(char function[], uint8_t var);

#endif