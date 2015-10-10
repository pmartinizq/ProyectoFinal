#include "FunctionHandler.h"
/**
  @brief Toma una instruccion del buffer de entrada y selecciona la funcion a ejecutar

  @returns void

  */
// desarrollar todas las funciones internas!!
  
void functionHandler(void){

  long time = 0,t=0;
	uint8_t idFunction = 0; 
	uint8_t parameter = 0;
	uint8_t numberOfBytes = 0;
	uint8_t stepParameters[ 4 ];
	uint8_t iterationFlagSteps = 0;	
	uint8_t velocityParameters[ 4 ];
	uint8_t iterationFlagVelocity = 0;
	uint16_t leftSteps = 0;
	uint16_t rightSteps = 0;
	int tangencialVelocity = 0;
	int angularVelocity = 0;
	FunctionStruct functionStructInstance;
	FunctionStruct *newFunction;
	FunctionStruct *lastFunction;

	// Tomar funcion del buffer de entrada
	if(isDataAvailable(&bufferIn)==1){
//	(void)SCI1S1; 
	idFunction = getFromBuffer(&bufferIn);
	switch ( idFunction ) {
		
		case getMeasure:
			//tomo el parametro de getMeasure
			  (void)SCI1S1;
		  	parameter = getFromBuffer(&bufferIn);
		  	switch ( parameter ) {
				
				case ULTRASONIC_ALL:
            functionStructInstance.functionParameter=getMeasureResponse;
				  	functionStructInstance.functionId = ULTRASONIC_ALL;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = NO_TIMER;
				  	functionStructInstance.root = MORE_FUNCTION;
				  	setFunctionToExecutingVector(functionStructInstance);
				  	
				  	
				  	
				  
				  	
				  	functionStructInstance.functionParameter=getMeasure;
				  	functionStructInstance.functionId = ULTRASONIC_FRONT;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = ULTRASONIC_FRONT_TIMER;
				  	functionStructInstance.root = ULTRASONIC_ALL;
				  	lastFunction=setFunctionToExecutingVector(functionStructInstance);
				  	getUltrasonic(lastFunction);
				  	/*
				  	while(lastFunction->status==RUNNING||lastFunction->status==READY);
				  	t=10000;
				  	while(t!=0){
				  	  t--;
				  	} */
				  	
				  	functionStructInstance.functionParameter=getMeasure;
				  	functionStructInstance.functionId = ULTRASONIC_LEFT;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = ULTRASONIC_LEFT_TIMER;
				  	functionStructInstance.root = ULTRASONIC_ALL;
				  	lastFunction=setFunctionToExecutingVector(functionStructInstance);
				  	getUltrasonic(lastFunction);
				  	
				  	/*
				  	while(lastFunction->status==RUNNING||lastFunction->status==READY);
				  	t=10000;
				  	while(t!=0){
				  	  t--;
				  	} */
				  	
				  	functionStructInstance.functionParameter=getMeasure;
				  	functionStructInstance.functionId = ULTRASONIC_RIGHT;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = ULTRASONIC_RIGHT_TIMER;
				  	functionStructInstance.root = ULTRASONIC_ALL;
				  	lastFunction=setFunctionToExecutingVector(functionStructInstance);
				  	getUltrasonic(lastFunction);
				  	//while(lastFunction->status==RUNNING||lastFunction->status==READY);
				  
				  	break;

				case ULTRASONIC_LEFT:
				    functionStructInstance.functionParameter=getMeasure;
				  	functionStructInstance.functionId = ULTRASONIC_LEFT;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = ULTRASONIC_LEFT_TIMER;
				  	functionStructInstance.root=UNIQUE_FUNCTION;
				  	getUltrasonic(setFunctionToExecutingVector(functionStructInstance));
				  	break;

				
				case ULTRASONIC_RIGHT:
				    functionStructInstance.functionParameter=getMeasure;
				  	functionStructInstance.functionId = ULTRASONIC_RIGHT;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = ULTRASONIC_RIGHT_TIMER;
				  	functionStructInstance.root=UNIQUE_FUNCTION;
	          getUltrasonic(setFunctionToExecutingVector(functionStructInstance));
				  	break;

				
				case ULTRASONIC_FRONT:
				    functionStructInstance.functionParameter=getMeasure;
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
					setToBuffer(getMeasure, &bufferOut);

					//Llamo la funcion que toma la medicion
					//accelMessure();
				  	break;
				
				case GYRO:
				  	functionStructInstance.functionId = GYRO;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = GYRO_TIMER;
				  	setToExecutingVector(&functionStructInstance);
					setToBuffer(ACK, &bufferOut);
					setToBuffer(getMeasure, &bufferOut);

					//Llamo la funcion que toma la medicion
					//gyroMessure();
				  	break;
				
				case COMPASS:
				  	functionStructInstance.functionId = COMPASS;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = COMPASS_TIMER;
				  	setToExecutingVector(&functionStructInstance);
					setToBuffer(ACK, &bufferOut);
					setToBuffer(getMeasure, &bufferOut);

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
			
		  	functionStructInstance.functionParameter=isGoal;
		  	functionStructInstance.functionId = isGoal;
		  	functionStructInstance.root=UNIQUE_FUNCTION;
		  	functionStructInstance.status = READY;
		  	functionStructInstance.timerCount = IS_GOAL_TIMER;
		  //	setToExecutingVector(&functionStructInstance);
		//	setToBuffer(ACK, &bufferOut);
		//	setToBuffer(isGoal, &bufferOut);
		  	
			//Tomo el parametro de isGoal
		  	parameter = getFromBuffer(&bufferIn);
		  	
				//Llamo funcion que setea el modo de meta
				setGoalMode(parameter, setFunctionToExecutingVector(functionStructInstance)); 
				
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
		  	tangencialVelocity=0;
		  	tangencialVelocity = tangencialVelocity + velocityParameters[0];
		  	tangencialVelocity=tangencialVelocity <<8 ;
		  	tangencialVelocity=tangencialVelocity+ velocityParameters[1];
		  	angularVelocity=0;
		  	angularVelocity = angularVelocity+velocityParameters[2];
		  	angularVelocity=angularVelocity <<8 + velocityParameters[3];
		  	

		  	
		  	setToBuffer(ACK, &bufferOut);
			  setToBuffer(setVelocity, &bufferOut);
		  	
		  	calcularSentido(robot_speed_to_pwm(tangencialVelocity,angularVelocity,&pwmRightValue,&pwmLeftValue));
        setPwmValue(pwmRightValue,pwmLeftValue);
      
		    //setToExecutingVector(&functionStructInstance);
			
			
			
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

