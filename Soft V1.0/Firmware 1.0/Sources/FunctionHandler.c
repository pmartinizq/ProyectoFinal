/*==================[inclusions]=============================================*/

#include "FunctionHandler.h"



/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/



/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/


/*==================[external functions definition]==========================*/



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
	uint8_t IDnumber;
	int tangencialVelocity = 0;
	int angularVelocity = 0;
	FunctionStruct functionStructInstance;
	FunctionStruct *rootFunction;	
	FunctionStruct *newFunction;
	FunctionStruct *lastFunction;

	// Tomar funcion del buffer de entrada
	if(isDataAvailable(&bufferIn)==1){
//	(void)SCI1S1; 
	idFunction = getFromBuffer(&bufferIn);
	switch ( idFunction ) {
		
		case getMeasure:
			//tomo el parametro de getMeasure
		  	parameter = getFromBuffer(&bufferIn);
		  	switch ( parameter ) {
				
				case ULTRASONIC_ALL:
				    
				    IDnumber = getIDNumber();
				    functionStructInstance.IDNumber = IDnumber; 
            		functionStructInstance.functionParameter=getMeasureResponse;
				  	functionStructInstance.functionId = ULTRASONIC_ALL;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = NO_TIMER;
				  	functionStructInstance.root = UNIQUE_FUNCTION;
				  	functionStructInstance.dataSize = 3;
				  	rootFunction=setFunctionToExecutingVector(functionStructInstance);

				    functionStructInstance.IDNumber = IDnumber; 
				  	functionStructInstance.functionParameter=getMeasure;
				  	functionStructInstance.functionId = ULTRASONIC_FRONT;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = ULTRASONIC_FRONT_TIMER;
				  	functionStructInstance.root = UNIQUE_FUNCTION;
				  	functionStructInstance.dataSize = 1;
				  	lastFunction=setFunctionToExecutingVector(functionStructInstance);
				  	getUltrasonic(lastFunction);
				  	
				  	while(lastFunction->status==RUNNING||lastFunction->status==READY);
				  	if(lastFunction->status==AVAILABLE){
				  	  rootFunction->data[0]=lastFunction->data[0];
				  	  lastFunction->status=DONE;
				  	}
				  	else if(lastFunction->status==TIMEOUT){
				  	  rootFunction->status=TIMEOUT;
				  	  break;
				  	}
				  	else if(lastFunction->status==INACCESSIBLE_DEVICE){
				  	  rootFunction->status=INACCESSIBLE_DEVICE;
				  	  break;  
				  	}
				  
				    functionStructInstance.IDNumber = IDnumber; 
				  	functionStructInstance.functionParameter=getMeasure;
				  	functionStructInstance.functionId = ULTRASONIC_LEFT;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = ULTRASONIC_LEFT_TIMER;
				  	functionStructInstance.root = UNIQUE_FUNCTION;
				  	functionStructInstance.dataSize = 1;
				  	lastFunction=setFunctionToExecutingVector(functionStructInstance);
				  	getUltrasonic(lastFunction);
				  	
				    while(lastFunction->status==RUNNING||lastFunction->status==READY);
				  	if(lastFunction->status==AVAILABLE){
				  	  rootFunction->data[1]=lastFunction->data[0];
				  	  lastFunction->status=DONE;
				  	}
				  	else if(lastFunction->status==TIMEOUT){
				  	  rootFunction->status=TIMEOUT;
				  	  break;
				  	}
				  	else if(lastFunction->status==INACCESSIBLE_DEVICE){
				  	  rootFunction->status=INACCESSIBLE_DEVICE;
				  	  break;  
				  	}
				 
				    functionStructInstance.IDNumber = IDnumber; 
				  	functionStructInstance.functionParameter=getMeasure;
				  	functionStructInstance.functionId = ULTRASONIC_RIGHT;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = ULTRASONIC_RIGHT_TIMER;
				  	functionStructInstance.root = UNIQUE_FUNCTION;
				  	functionStructInstance.dataSize = 1;
				  	lastFunction=setFunctionToExecutingVector(functionStructInstance);
				  	getUltrasonic(lastFunction);
				  
				    while(lastFunction->status==RUNNING||lastFunction->status==READY);
				  	if(lastFunction->status==AVAILABLE){
				  	  rootFunction->data[2]=lastFunction->data[0];
				  	  rootFunction->status=AVAILABLE;
				  	  lastFunction->status=DONE;
				  	}
				  	else if(lastFunction->status==TIMEOUT){
				  	  rootFunction->status=TIMEOUT;
				  	  break;
				  	}
				  	else if(lastFunction->status==INACCESSIBLE_DEVICE){
				  	  rootFunction->status=INACCESSIBLE_DEVICE;
				  	  break;				  	  
				  	}
				  	break;

				case ULTRASONIC_LEFT:
				    functionStructInstance.IDNumber = 0;
				    functionStructInstance.functionParameter=getMeasure;
				  	functionStructInstance.functionId = ULTRASONIC_LEFT;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = ULTRASONIC_LEFT_TIMER;
				  	functionStructInstance.root=UNIQUE_FUNCTION;
				  	functionStructInstance.dataSize = 1;
				  	getUltrasonic(setFunctionToExecutingVector(functionStructInstance));
				  	break;

				
				case ULTRASONIC_RIGHT:
				functionStructInstance.IDNumber = 0;
				    functionStructInstance.functionParameter=getMeasure;
				  	functionStructInstance.functionId = ULTRASONIC_RIGHT;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = ULTRASONIC_RIGHT_TIMER;
				  	functionStructInstance.root=UNIQUE_FUNCTION;
				  	functionStructInstance.dataSize = 1;
	          		getUltrasonic(setFunctionToExecutingVector(functionStructInstance));
				  	break;

				
				case ULTRASONIC_FRONT:
					functionStructInstance.IDNumber = 0;
				    functionStructInstance.functionParameter=getMeasure;
				  	functionStructInstance.functionId = ULTRASONIC_FRONT;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = ULTRASONIC_FRONT_TIMER;
				  	functionStructInstance.root=UNIQUE_FUNCTION;
				  	functionStructInstance.dataSize = 1;
				  	getUltrasonic(setFunctionToExecutingVector(functionStructInstance));				  	
				  	break;


				case ACCEL:
					functionStructInstance.IDNumber = 0;
				    functionStructInstance.functionParameter=getMeasureResponse;
				  	functionStructInstance.functionId = ACCEL;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = ACCEL_TIMER;
				  	functionStructInstance.root=UNIQUE_FUNCTION;
					//Llamo la funcion que toma la medicion
				  	//getAccelMeasure(setFunctionToExecutingVector(functionStructInstance));
				  	functionStructInstance.dataSize = 6;
				  	testFunction1(setFunctionToExecutingVector(functionStructInstance));
				  	break;
				
				case GYRO:
					functionStructInstance.IDNumber = 0;
				    functionStructInstance.functionParameter=getMeasureResponse;
				  	functionStructInstance.functionId = GYRO;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = GYRO_TIMER;
				  	functionStructInstance.root=UNIQUE_FUNCTION;
					//Llamo la funcion que toma la medicion
				  	//getGyroMeasure(setFunctionToExecutingVector(functionStructInstance));
				  	functionStructInstance.dataSize = 6;
				  	testFunction2(setFunctionToExecutingVector(functionStructInstance));
				  	break;
				
				case COMPASS:
					functionStructInstance.IDNumber = 0;
				    functionStructInstance.functionParameter=getMeasureResponse;
				  	functionStructInstance.functionId = COMPASS;
				  	functionStructInstance.status = READY;
				  	functionStructInstance.timerCount = COMPASS_TIMER;
				  	functionStructInstance.root=UNIQUE_FUNCTION;
					//Llamo la funcion que toma la medicion
				  	//getCompassMeasure(setFunctionToExecutingVector(functionStructInstance));
				  	functionStructInstance.dataSize = 2;
				  	testFunction3(setFunctionToExecutingVector(functionStructInstance));
				  	break;

				default:
					setToBuffer(error, &bufferOut);
					setToBuffer(COMMAND_ERROR, &bufferOut);
				  	break;
			}
		  	break;
		
		case isGoal:
			  functionStructInstance.IDNumber = 0;
		  	functionStructInstance.functionParameter=isGoal;
		  	functionStructInstance.functionId = isGoal;
		  	functionStructInstance.root=UNIQUE_FUNCTION;
		  	functionStructInstance.status = READY;
		  	functionStructInstance.timerCount = IS_GOAL_TIMER;
			functionStructInstance.dataSize = 1;
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
		    leftWheelStepValueToSet = 0;
		  	leftWheelStepValueToSet = leftWheelStepValueToSet + stepParameters[0];
		  	leftWheelStepValueToSet = leftWheelStepValueToSet << 8;
		  	leftWheelStepValueToSet = leftWheelStepValueToSet + stepParameters[1];
		  	rightWheelStepValueToSet =0;
		  	rightWheelStepValueToSet = rightWheelStepValueToSet + stepParameters[2];
		  	rightWheelStepValueToSet = rightWheelStepValueToSet <<8;
		  	rightWheelStepValueToSet = rightWheelStepValueToSet + stepParameters[3];
  			setToBuffer(ACK, &bufferOut);
  			setToBuffer(setSteps, &bufferOut);
  			
  			moveBy=STEPS;
  			leftWheelStepValue=0;
  			rightWheelStepValue=0;
  			
  		  if(leftWheelStepValueToSet>=0&&rightWheelStepValueToSet>=0){
  		    calcularSentido(FORWARD);
  		  }else if(leftWheelStepValueToSet<0&&rightWheelStepValueToSet<0){
  		    calcularSentido(REVERSE);
  		  }else if(leftWheelStepValueToSet<0&&rightWheelStepValueToSet>0){
  		    calcularSentido(TURN_RIGHT);
  		  }else if(leftWheelStepValueToSet>0&&rightWheelStepValueToSet<0){
  		    calcularSentido(TURN_LEFT);
  		  }
  		  //robot_speed_to_pwm(100,0,&pwmRightValue,&pwmLeftValue);
  		  //setPwmValue(pwmRightValue,pwmLeftValue);
        setPwmValue(100,100);

		  	//funcion que setea los pasos mandando los parametros leftSteps y rightSteps
		  	//setSteps(leftWheelStepValueToSet, rightWheelStepValueToSet);
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
			moveBy=LINEAR_VELOCITY;
			
		  	calcularSentido(robot_speed_to_pwm(tangencialVelocity,angularVelocity,&pwmRightValue,&pwmLeftValue));
       	setPwmValue(pwmRightValue,pwmLeftValue);
       	//setPwmValue(tangencialVelocity,tangencialVelocity);
		  	break;
		
		default:
			setToBuffer(error, &bufferOut);
			setToBuffer(COMMAND_ERROR, &bufferOut);
		  	break;
	}
	}

}


/*==================[internal functions definition]==========================*/


