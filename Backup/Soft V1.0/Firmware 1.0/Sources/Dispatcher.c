#include "Dispatcher.h"


void dispatcher(ExecutingStruct* executingVector, BufferStruct* functionBuffer){
	uint8_t vectorSize = getExecutingVectorPointer();
	uint8_t counter = 0;
	uint8_t variable;
	uint8_t functionID;
	uint8_t isRoot;
	uint8_t variableAux1;
	uint8_t variableAux2;
	uint8_t variableAux3;
	if(getFromExecutingVector()!=NULL){
	  
	for(counter = 0; counter <= vectorSize; counter++){
		variable = getFromExecutingVectorOnIndex(counter)->status;
		functionID = getFromExecutingVectorOnIndex(counter)->functionId;
		isRoot = getFromExecutingVectorOnIndex(counter)->root;
		if(isRoot == MORE_FUNCTION || isRoot == UNIQUE_FUNCTION){
			if(isRoot == MORE_FUNCTION){
				variableAux1 = getFromExecutingVectorOnIndex(counter+1)->status;
				variableAux2 = getFromExecutingVectorOnIndex(counter+2)->status;
				variableAux3 = getFromExecutingVectorOnIndex(counter+3)->status;
				if(variableAux1 == ERROR || variableAux2 == ERROR || variableAux3 == ERROR){
					variable = ERROR;
					getFromExecutingVectorOnIndex(counter+1)->status = DONE;
					getFromExecutingVectorOnIndex(counter+2)->status = DONE;
					getFromExecutingVectorOnIndex(counter+3)->status = DONE;
				}
				else{
					if(variableAux1 == TIMEOUT || variableAux2 == TIMEOUT || variableAux3 == TIMEOUT){
						variable = TIMEOUT;
						getFromExecutingVectorOnIndex(counter+1)->status = DONE;
						getFromExecutingVectorOnIndex(counter+2)->status = DONE;
						getFromExecutingVectorOnIndex(counter+3)->status = DONE;
					}
					else{
						if(variableAux1 == AVAILABLE && variableAux2 == AVAILABLE && variableAux3 == AVAILABLE){
							variable = AVAILABLE;
							//revistar estooo!!!
							getFromExecutingVectorOnIndex(counter)->data->data[0] = getFromExecutingVectorOnIndex(counter+1)->data->data[0];
							getFromExecutingVectorOnIndex(counter)->data->data[1] = getFromExecutingVectorOnIndex(counter+2)->data->data[0];
							getFromExecutingVectorOnIndex(counter)->data->data[2] = getFromExecutingVectorOnIndex(counter+3)->data->data[0];
							getFromExecutingVectorOnIndex(counter+1)->status = DONE;
							getFromExecutingVectorOnIndex(counter+2)->status = DONE;
							getFromExecutingVectorOnIndex(counter+3)->status = DONE;
						}
					}
				}
				counter = counter+3;
			}
			switch ( variable ) {
				case AVAILABLE:
							setToBuffer(functionID, functionBuffer);
							if(functionID >= 128){
								variableAux1 = getFromExecutingVectorOnIndex(counter)->data->pointer;
								variableAux2 = 0;
								setToBuffer(variableAux1, functionBuffer);
								for(variableAux2 = 0; variableAux2 < variableAux1; variableAux2++){
									setToBuffer(getFromExecutingVectorOnIndex(counter)->data->data[variableAux2], functionBuffer);
								}	
							}
							else{
							setToBuffer(getFromExecutingVectorOnIndex(counter)->data->data[0], functionBuffer);
							}

				case ERROR:
							setToBuffer(ERROR, functionBuffer);
							setToBuffer(functionID, functionBuffer);
							getFromExecutingVectorOnIndex(counter)->status = DONE;
							break;
							
				case TIMEOUT:
							setToBuffer(TIMEOUT, functionBuffer);
							setToBuffer(functionID, functionBuffer);
							getFromExecutingVectorOnIndex(counter)->status = DONE;
							break;
			}
		}
	}
	}
}