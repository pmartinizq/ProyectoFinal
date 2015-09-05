#include "FunctionHandler.h"
/**
  @brief Toma una instruccion del buffer de entrada y selecciona la funcion a ejecutar

  @returns void

  */
// desarrollar todas las funciones internas!!
  
void functionHandler(void){

	uint8_t idFunction = 0; 
	uint8_t parameter = 0;
	uint8_t numberOfBytes = 0;
	uint8_t stepParameters[ 4 ];
	uint8_t iterationFlagSteps = 0;	
	uint8_t velocityParameters[ 4 ];
	uint8_t iterationFlagVelocity = 0;
	uint16_t leftSteps = 0;
	uint16_t rightSteps = 0;
	uint16_t leftVelocity = 0;
	uint16_t rightVelocity = 0;
	FunctionStruct functionStructInstance;
	FunctionStruct *newFunction;

	// Tomar funcion del buffer de entrada
	if(isDataAvailable(&bufferIn)==1){
	(void)SCI1S1; 
	idFunction = getFromBuffer(&bufferIn);
	switch ( idFunction ) {
		
		case getMessure:
			//tomo el parametro de getMessure
			  (void)SCI1S1;
		  	parameter = getFromBuffer(&bufferIn);
		  	switch ( parameter ) {
				
				case ULTRASONIC_ALL:

				  	functionStructInstance.functionId = ULTRASONIC_ALL;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = 0;
				  	functionStructInstance.root = MORE_FUNCTION;
				  	getUltrasonic(setFunctionToExecutingVector(functionStructInstance));
				  	
				  	functionStructInstance.functionId = ULTRASONIC_LEFT;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = ULTRASONIC_LEFT_TIMER;
				  	functionStructInstance.root = ULTRASONIC_ALL;
				  	getUltrasonic(setFunctionToExecutingVector(functionStructInstance));
				  	
				  	functionStructInstance.functionId = ULTRASONIC_FRONT;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = ULTRASONIC_FRONT_TIMER;
				  	functionStructInstance.root = ULTRASONIC_ALL;
				  	getUltrasonic(setFunctionToExecutingVector(functionStructInstance));
				  	functionStructInstance.functionId = ULTRASONIC_RIGHT;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = ULTRASONIC_RIGHT_TIMER;
				  	functionStructInstance.root = ULTRASONIC_ALL;
				  	getUltrasonic(setFunctionToExecutingVector(functionStructInstance));
				  	
				  	/*
  					setToBuffer(ACK, &bufferOut);
  					setToBuffer(getMessure, &bufferOut);
  					*/

					//Llamo la funcion que toma la medicion
					//ultrasonicAllMessure();
				  	break;

				case ULTRASONIC_LEFT:
				  	functionStructInstance.functionId = ULTRASONIC_LEFT;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = ULTRASONIC_LEFT_TIMER;
				  	functionStructInstance.root=UNIQUE_FUNCTION;
				  	getUltrasonic(setFunctionToExecutingVector(functionStructInstance));
				  	break;

				
				case ULTRASONIC_RIGHT:
				  	functionStructInstance.functionId = ULTRASONIC_RIGHT;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = ULTRASONIC_RIGHT_TIMER;
				  	functionStructInstance.root=UNIQUE_FUNCTION;
	          getUltrasonic(setFunctionToExecutingVector(functionStructInstance));
				  	break;

				
				case ULTRASONIC_FRONT:
				    
				  	functionStructInstance.functionId = ULTRASONIC_FRONT;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = ULTRASONIC_FRONT_TIMER;
				  	functionStructInstance.root=UNIQUE_FUNCTION;
				  	getUltrasonic(setFunctionToExecutingVector(functionStructInstance));
				  	
				  	break;


				case ACCEL:
				  	functionStructInstance.functionId = ACCEL;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = ACCEL_TIMER;
				  	setToExecutingVector(&functionStructInstance);
					setToBuffer(ACK, &bufferOut);
					setToBuffer(getMessure, &bufferOut);

					//Llamo la funcion que toma la medicion
					//accelMessure();
				  	break;
				
				case GYRO:
				  	functionStructInstance.functionId = GYRO;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = GYRO_TIMER;
				  	setToExecutingVector(&functionStructInstance);
					setToBuffer(ACK, &bufferOut);
					setToBuffer(getMessure, &bufferOut);

					//Llamo la funcion que toma la medicion
					//gyroMessure();
				  	break;
				
				case COMPASS:
				  	functionStructInstance.functionId = COMPASS;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = COMPASS_TIMER;
				  	setToExecutingVector(&functionStructInstance);
					setToBuffer(ACK, &bufferOut);
					setToBuffer(getMessure, &bufferOut);

					//Llamo la funcion que toma la medicion
					//compassMessure();
				  	break;

				default:
					setToBuffer(ERROR, &bufferOut);
					setToBuffer(COMMAND_ERROR, &bufferOut);
				  	break;
			}
		  	break;
		
		case isGoal:
			
		  	functionStructInstance.functionId = isGoal;
		  	functionStructInstance.status = READY;
		  	functionStructInstance.timerCount = IS_GOAL_TIMER;
		  	setToExecutingVector(&functionStructInstance);
			setToBuffer(ACK, &bufferOut);
			setToBuffer(isGoal, &bufferOut);
		  	
			//Tomo el parametro de isGoal
		  	parameter = getFromBuffer(&bufferIn);
			if(parameter != NOP){
				//Llamo funcion que setea el modo de meta
				//setGoalMode(parameter); 
			}
		  	break;
		
		case setSteps:
			// tomo el numero de bytes
			numberOfBytes = getFromBuffer(&bufferIn);
		  	while(numberOfBytes >= iterationFlagSteps){
		  		// tomo uno de los bytes de setStep y lo guardo en un array
		  		stepParameters[ iterationFlagSteps ] = getFromBuffer(&bufferIn);
		  		iterationFlagSteps++;
		  	}
		  	leftSteps = stepParameters[0] * 16 + stepParameters[1];
		  	rightSteps = stepParameters[2] * 16 + stepParameters[3];

		  	functionStructInstance.functionId = setSteps;
		  	functionStructInstance.status = READY;
		  	functionStructInstance.timerCount = SET_STEPS_TIMER;
		  	setToExecutingVector(&functionStructInstance);
			setToBuffer(ACK, &bufferOut);
			setToBuffer(setSteps, &bufferOut);

		  	//funcion que setea los pasos mandando los parametros leftSteps y rightSteps
		  	//setSteps(leftSteps, rightSteps);
		  	break;
		
		case setVelocity:
		  	// tomo el numero de bytes
			numberOfBytes = getFromBuffer(&bufferIn);
		  	while(numberOfBytes >= iterationFlagVelocity){
		  		// tomo uno de los bytes de setVelocity y lo guardo en un array
		  		velocityParameters[iterationFlagVelocity] = getFromBuffer(&bufferIn);
		  		iterationFlagVelocity++;
		  	}
		  	leftVelocity = velocityParameters[0] * 16 + velocityParameters[1];
		  	rightVelocity = velocityParameters[2] * 16 + velocityParameters[3];
		  	// ¿faltan parametros?!!

		  	functionStructInstance.functionId = setVelocity;
		  	functionStructInstance.status = READY;
		  	functionStructInstance.timerCount = SET_VELOCITY_TIMER;
		  	setToExecutingVector(&functionStructInstance);
			setToBuffer(ACK, &bufferOut);
			setToBuffer(setVelocity, &bufferOut);
			
		  	//funcion que setea las velocidades mandando los parametros leftVelocity y rightVelocity
		  	//setVelocity(leftVelocity, rightVelocity);
		  	break;
		
		default:
			setToBuffer(ERROR, &bufferOut);
			setToBuffer(COMMAND_ERROR, &bufferOut);
		  	break;
	}
	}

}

