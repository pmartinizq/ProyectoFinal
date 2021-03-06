/*==================[inclusions]=============================================*/

#include "Dispatcher.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[external functions definition]==========================*/

void dispatcher(ExecutingStruct* executingVector, BufferStruct* functionBuffer){
	uint8_t vectorSize = getExecutingVectorPointer();
	uint8_t counter = 0;
	uint8_t variable;
	uint8_t functionID;
	uint8_t functionParameter;
	uint8_t isRoot;
	uint8_t variableAux1;
	uint8_t variableAux2;
	uint8_t variableAux3;
	FunctionStruct* functionAux;
	//if(functionAux->functionId!=0&&){
	  
	for(counter = 0; counter <= vectorSize; counter++){
	  functionAux=getFromExecutingVectorOnIndex(counter);
	  if(functionAux->status!=0&&functionAux->status!=DONE){
	    
		variable = getFromExecutingVectorOnIndex(counter)->status;
		functionID = getFromExecutingVectorOnIndex(counter)->functionId;
		functionParameter = getFromExecutingVectorOnIndex(counter)->functionParameter;
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
					
					if(variableAux1 == INACCESSIBLE_DEVICE || variableAux2 == INACCESSIBLE_DEVICE || variableAux3 == INACCESSIBLE_DEVICE){
						variable = INACCESSIBLE_DEVICE;
						getFromExecutingVectorOnIndex(counter+1)->status = DONE;
						getFromExecutingVectorOnIndex(counter+2)->status = DONE;
						getFromExecutingVectorOnIndex(counter+3)->status = DONE;
					}
					
						if(variableAux1 == AVAILABLE && variableAux2 == AVAILABLE && variableAux3 == AVAILABLE){
							variable = AVAILABLE;
							//revistar estooo!!!
							getFromExecutingVectorOnIndex(counter)->data[0] = getFromExecutingVectorOnIndex(counter+1)->data[0];
							getFromExecutingVectorOnIndex(counter)->data[1] = getFromExecutingVectorOnIndex(counter+2)->data[0];
							getFromExecutingVectorOnIndex(counter)->data[2] = getFromExecutingVectorOnIndex(counter+3)->data[0];
							getFromExecutingVectorOnIndex(counter+1)->status = DONE;
							getFromExecutingVectorOnIndex(counter+2)->status = DONE;
							getFromExecutingVectorOnIndex(counter+3)->status = DONE;
						}
					
				}
				//counter = counter+3;
			}
			switch ( variable ) {
				case AVAILABLE:
							
							if(functionParameter >= 128){
							  setToBuffer(functionParameter, functionBuffer);
		
								variableAux1 = getFromExecutingVectorOnIndex(counter)->dataSize;
								variableAux2 = 0;
								
								setToBuffer(variableAux1, functionBuffer);
								
								for(variableAux2 = 0; variableAux2 <= variableAux1-1; variableAux2++){
									setToBuffer(getFromExecutingVectorOnIndex(counter)->data[variableAux2], functionBuffer);
									//setToBuffer(variableAux2, functionBuffer);
								}	
							}
							else{
							setToBuffer(functionParameter, functionBuffer);
							setToBuffer(getFromExecutingVectorOnIndex(counter)->data[0], functionBuffer);
							}
							getFromExecutingVectorOnIndex(counter)->status = DONE;
							break;

				case INACCESSIBLE_DEVICE:
							setToBuffer(error, functionBuffer);
							setToBuffer(2,functionBuffer);
							if(functionParameter==getMeasureResponse){ 
                functionParameter=getMeasure;
              }
							setToBuffer(functionParameter, functionBuffer);
							setToBuffer(INACCESSIBLE_DEVICE, functionBuffer);
							getFromExecutingVectorOnIndex(counter)->status = DONE;
							break; 							
			
							
				case TIMEOUT:
							setToBuffer(error, functionBuffer);
							setToBuffer(2,functionBuffer);
							setToBuffer(functionID, functionBuffer);
							setToBuffer(TIMEOUT, functionBuffer);
							getFromExecutingVectorOnIndex(counter)->status = DONE;
							break;
			}
		}
	}
	}
	
}

/*==================[internal functions definition]==========================*/