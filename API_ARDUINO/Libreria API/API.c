#include "API.h"

uint8_t GetMeassure(uint8_t TYPE){
	Send(START_BYTE);
	Send(GETMEASSURE);
	Send(TYPE);
	result = NULL;
	variable = Get();
	if(variable == START_BYTE){
		variable = Get();
		if(variable == GETMEASSURE){
			counter = Get();
			for(auxCounter = 0; auxCounter < counter, auxCounter++){
				result[auxCounter] = Get();
			}
		}
		else{
			if(variable == ERROR){
				variable = Get();
				if(variable == 2){
					variable = Get();
					if(variable == GETMEASSURE){
						variable = Get();
						ErrorPrint("GETMEASSURE",variable);
					}
				}
		}	
		}
	}
	return result;
}

bool SetVelocity(uint16_t leftWheelVelocity, uint16_t rightWheelVelocity){
	Send(START_BYTE);
	Send(SETVELOCITY);
	Send(4);
	Send((leftWheelVelocity & 0XFF));
	Send((leftWheelVelocity >> 8));
	Send((rightWheelVelocity & 0XFF));
	Send((rightWheelVelocity >> 8));
	boolResult = FALSE;
	variable = Get();
	if(variable == START_BYTE){
		variable = Get();
		if(variable == ACK){
			variable = Get();
			if(variable == SETVELOCITY){
				boolResult = TRUE;
			}
		}
		else{
			if(variable == ERROR){
				variable = Get();
				if(variable == 2){
					variable = Get();
					if(variable == SETVELOCITY){
						variable = Get();
						ErrorPrint("SETVELOCITY",variable);
					}
				}
			}
		}
	}
	return boolResult;
}
bool SetSteps(uint16_t leftWheelSteps, uint16_t rightWheelSteps){
	Send(START_BYTE);
	Send(SETSTEPS);
	Send(4);
	Send((leftWheelSteps & 0XFF));
	Send((leftWheelSteps >> 8));
	Send((rightWheelSteps & 0XFF));
	Send((rightWheelSteps >> 8));
	boolResult = FALSE;
	variable = Get();
	if(variable == START_BYTE){
		variable = Get();
		if(variable == ACK){
			variable = Get();
			if(variable == SETSTEPS){
				boolResult = TRUE;
			}
		}
		else{
			if(variable == ERROR){
				variable = Get();
				if(variable == 2){
					variable = Get();
					if(variable == SETSTEPS){
						variable = Get();
						ErrorPrint("SETSTEPS",variable);
					}
				}
			}
		}
	}
	return boolResult;
}

bool IsGoal(uint8_t MODE){
	Send(START_BYTE);
	Send(ISGOAL);
	Send(MODE);
	boolResult = FALSE;
	variable = Get();
	if(variable == START_BYTE){
		variable = Get();
		if(variable == ISGOAL){
			variable = Get();
			if(variable == ISGOAL_TRUE){
				boolResult = TRUE;
			}	
		}
		else{
			if(variable == ERROR){
				variable = Get();
				if(variable == 2){
					variable = Get();
					if(variable == SETSTEPS){
						variable = Get();
						ErrorPrint("ISGOAL",variable);
					}
				}
			}
		}
	}
	return boolResult;

}
void Send(uint8_t DATA){
	writeSerial(DATA);
}
uint8_t Get(){
	getResponse = NULL;
	for(int i=0; i > TIMERGET; i++){
		if(availableSerial()){
	    	getResponse = (byte)readSerial();
		}
	}
	return getResponse;
}
void ErrorPrint(char function[], uint8_t var){
	Serial.println("\tERROR: ");
	if(var == INACCESSIBLE_DEVICE){
		Serial.println("INACCESSIBLE DEVICE");
	}
	else{
		if(var == COMMAND_ERROR){
			Serial.println("COMMAND ERROR");
		}
		else{
			if(var == TIMEOUT){
				Serial.println("TIMEOUT");
			}	
		}
	}
	Serial.println(" in function: ");
	Serial.println(function); 
	Serial.println(".");
}

