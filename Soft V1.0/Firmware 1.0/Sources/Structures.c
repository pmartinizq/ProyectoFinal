#include "Structures.h"

/*==================[inclusions]=============================================*/

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[external functions definition]==========================*/

void InitBuffer(BufferStruct* BufferToInit){
	BufferToInit->readPointer = 0;
	BufferToInit->writePointer = 0;
}

uint8_t getFromBuffer(BufferStruct* BufferToGet){
	
	//controla que el buffer tenga algun valor cargado
	
	if(BufferToGet->BufferFlags[BufferToGet->readPointer] == 1){
		//toma el dato al que apunta readPointer
		uint8_t data = BufferToGet->Buffer[BufferToGet->readPointer];
		// limpia la celda de bufferFlags
		BufferToGet->BufferFlags[BufferToGet->readPointer] = 0;
		//incrementa el puntero de lectura
		if(BufferToGet->readPointer < BUFFER_SIZE-1){
			BufferToGet->readPointer++;
		}
		else{
			BufferToGet->readPointer = 0;
		}
		return data;
	}
	return 0;
}

void setToBuffer(uint8_t data, BufferStruct* BufferToSet){
	//controla si la celda del buffer esta vacia
	
	
	if(BufferToSet->BufferFlags[BufferToSet->writePointer] != 1){
		// setea la celda con 'data'
		BufferToSet->Buffer[BufferToSet->writePointer] = data;
		BufferToSet->BufferFlags[BufferToSet->writePointer] = 1;
		//incrementa el puntero de escritura
		if(BufferToSet->writePointer < BUFFER_SIZE-1){
			BufferToSet->writePointer++;
		}
		else{
			BufferToSet->writePointer = 0;
		}
	}
}

uint8_t getSpaceOfBuffer(BufferStruct* BufferToCalculate){
	uint8_t data = 0,rp,wp,r;
	rp=BufferToCalculate->readPointer;
	wp=BufferToCalculate->writePointer;
	r=wp-rp;
	if((BufferToCalculate->writePointer) < (BufferToCalculate->readPointer)){
		data = BufferToCalculate->readPointer - BufferToCalculate->writePointer;
	}
	else{
		data = BUFFER_SIZE - (BufferToCalculate->writePointer - BufferToCalculate->readPointer);
	}
	return data;
}

uint8_t isFunctionOnExecutingVector(FunctionStruct FunctionToSet){
  uint8_t flag = 0;
  int i = 0;
  for(i=0;i<=executingVector.pointer;i++){
  if(executingVector.vector[i].status != DONE && executingVector.vector[i].status != 0){
      if(executingVector.vector[i].functionId == FunctionToSet.functionId &&
         executingVector.vector[i].functionParameter == FunctionToSet.functionParameter){
        flag= 1;
      }
  }
  }
  return flag;
}

FunctionStruct* setFunctionToExecutingVector(FunctionStruct FunctionToSet){
int i=0,j=0,n=0;
if(isFunctionOnExecutingVector(FunctionToSet)){
  return;
} 
if(FunctionToSet.root==UNIQUE_FUNCTION){
  
    for(i=0;i<=executingVector.pointer;i++){
        
        if(executingVector.vector[i].status==DONE||executingVector.vector[i].status==0){
          executingVector.vector[i]=FunctionToSet;
          return &executingVector.vector[i];
        }
      }
      if(executingVector.pointer < EXECUTING_STRUCT_SIZE){
         executingVector.pointer=executingVector.pointer+1;
         executingVector.vector[executingVector.pointer]=FunctionToSet;
         return &executingVector.vector[executingVector.pointer];    
       }
      return NULL;
}
else{
    if(FunctionToSet.root==MORE_FUNCTION){ //SI ES LA FUNCION PADRE BUSCO QUE TENGA LUGAR CONTIGUO PARA LOS HIJOS
       
       for(i=0;i<=executingVector.pointer;i++){
        
          if(executingVector.vector[i].status==DONE||executingVector.vector[i].status==0){
            //BUSCO 3 LUGARES
             for(j=1;j<=MAX_CHILDREN;j++){
                if(executingVector.vector[i+j].status==DONE||executingVector.vector[i+j].status==0){
                     n++;
                 }
             }
              //SI ENCUENTRA 3 LUGARES LO PONE AL PADRE Y RETORNA
              if(n==MAX_CHILDREN){
                //executingVector.pointer=executingVector.pointer+1;
                executingVector.vector[i]=FunctionToSet;
                return &executingVector.vector[i];
              }
          }
       }
       
          //SINO ENCUENTRA LOS 3 LUGARES PONE UNO NUEVO
           executingVector.pointer=executingVector.pointer+1;
           executingVector.vector[executingVector.pointer]=FunctionToSet;
           return &executingVector.vector[executingVector.pointer];
    }
    
    else{ //SI SON LOS HIJOS LOS PONGO AL LADO DE LA FUNCION PADRE
       for(i=0;i<=executingVector.pointer;i++){
        
        
        if(executingVector.vector[i].root==MORE_FUNCTION&&executingVector.vector[i].status!=DONE){//ECUENTRA AL PADRE
          if(FunctionToSet.root==executingVector.vector[i].functionId && 
             executingVector.vector[i].IDNumber == FunctionToSet.IDNumber){//PREGUNTA SI ES EL PADRE
              for(j=1;j<=MAX_CHILDREN;j++){//NO SOBRE ESCRIBE A LOS HIJOS
                  if((executingVector.vector[i+j].root!=FunctionToSet.root)||executingVector.vector[i+j].status==DONE){
                     // executingVector.pointer=executingVector.pointer+1;
                      executingVector.vector[i+j]=FunctionToSet;
                      while(executingVector.pointer<(i+j)){
                        executingVector.pointer=executingVector.pointer+1;
                      }
                      return &executingVector.vector[i+j];
                  }
              }
          }
            
        }
       }
    }
            
      
}
}
      
FunctionStruct* getFromExecutingVector(){
  FunctionStruct  functionToReturn;
  functionToReturn=executingVector.vector[executingVector.readPointer];
  if(executingVector.readPointer==executingVector.pointer){
    executingVector.readPointer=0;
  }else{
    executingVector.readPointer=executingVector.readPointer+1;
  }
  
  return &functionToReturn;
}

uint8_t getExecutingVectorPointer(){
  return executingVector.pointer;  
  
}

FunctionStruct* getFromExecutingVectorOnIndex(uint8_t position){
  
  
  if(position<=executingVector.pointer){
    return &executingVector.vector[position];
  } else{
    return &executingVector.vector[0];
  }
  
}

void initExecutingVector(void){
  
  uint8_t i;
  
  for(i=0;i<EXECUTING_STRUCT_SIZE;i++){
    executingVector.vector[i].functionId=0;
  }
  executingVector.pointer=0;
  executingVector.readPointer=0; 
}

FunctionStruct* getChildOf(uint8_t id){
  uint8_t i=0,childIndex=0;
  FunctionStruct* childVector[3];
  FunctionStruct* currentFunction;
  for(i=0;i<=getExecutingVectorPointer();i++){
    currentFunction=getFromExecutingVectorOnIndex(i);
    if((currentFunction->root==id)&&i>childIndex){
      childVector[childIndex]=currentFunction;
    }
  }
  return &childVector;
}

uint8_t setBufferOnBuffer(BufferStruct* BufferGet, BufferStruct* BufferAdd){
	uint8_t space = getSpaceOfBuffer(BufferGet);
	uint8_t spaceOnGet = BUFFER_SIZE - space;
	uint8_t spaceOnAdd = getSpaceOfBuffer(BufferAdd);
	if(spaceOnAdd >= spaceOnGet){
		uint8_t flag = 0;
		for(flag ; flag <spaceOnGet ; flag++){
			setToBuffer(getFromBuffer(BufferGet), BufferAdd);
		}
		return 1;
	}
	else{
		return 0;
	}
}

uint8_t isDataAvailable(BufferStruct *bufferToEvaluate){
  if(bufferToEvaluate->BufferFlags[bufferToEvaluate->readPointer]==1){
    
    return 1;
  }
  else{
    
    return 0;
  }
}

/*==================[internal functions definition]==========================*/