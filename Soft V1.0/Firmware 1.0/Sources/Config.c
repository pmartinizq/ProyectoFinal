#include "Config.h"


/**
  \brief Inicializacion de buffer. 

  	Inicializa los parametros 'readPointer', 'writePointer' y 'buffer' de la estructura 'bufferStruct'.

  \param *BufferToInit es el puntero a  bufferStruct a inicializar.

  \returns void

  */
void InitBuffer(BufferStruct* BufferToInit){
	BufferToInit->readPointer = 0;
	BufferToInit->writePointer = 0;
}

/**
  \brief toma dato del buffer. 

  	toma un dato uint8_t del buffer e incrementa el puntero 'readPointer'.
  	Si no hay datos que leer no incrementa el puntero.
  	Lipia la celda luego de leerla.

  \param BufferToGet es el buffer (struct bufferStruct) a leer.

  \returns data Parametro uint8_t con el valor de la celda tomada del buffer.

  */
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

/**
  @brief Setea un dato en el buffer. 

  	setea un dato uint8_t en el buffer e incrementa el puntero 'writePointer'.
  	Si no hay lugar en el buffer en donde setear el dato, lo descarta.

  @param BufferToSet es el buffer (struct bufferStruct) a escribir.

  @returns void.

  */
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
/**
  @brief devuelve el espacio disponible en el buffer. 

  	calcula el espacio disponible para almacenamiento en el buffer.

  @param BufferToCalculate es el buffer (struct bufferStruct) a calcular.

  @returns data Parametro uint8_t con el valor del espacio disponible para almacenamiento en el buffer.

  */
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


void setToExecutingVector(FunctionStruct FunctionToSet){
int i=0;
if(executingVector.vector[executingVector.pointer].functionId==0){
  executingVector.vector[executingVector.pointer]=FunctionToSet;
  //executingVector.pointer=executingVector.pointer+1;
} else{
  for(i=0;i<executingVector.pointer;i++){
    
    if(executingVector.vector[i].status==DONE){
      executingVector.vector[i]=FunctionToSet;
      //executingVector.pointer=executingVector.pointer+1;
      return;
    }
  }
   executingVector.pointer=executingVector.pointer+1;
   executingVector.vector[executingVector.pointer]=FunctionToSet;
} 
  

}

FunctionStruct* setFunctionToExecutingVector(FunctionStruct FunctionToSet){
int i=0,j=0,n=0;
if(FunctionToSet.root==UNIQUE_FUNCTION){
  
    for(i=0;i<=executingVector.pointer;i++){
        
        if(executingVector.vector[i].status==DONE||executingVector.vector[i].status==0){
          executingVector.vector[i]=FunctionToSet;
          return &executingVector.vector[i];
        }
      }
       executingVector.pointer=executingVector.pointer+1;
       executingVector.vector[executingVector.pointer]=FunctionToSet;
       return &executingVector.vector[executingVector.pointer];
    
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
          if(FunctionToSet.root==executingVector.vector[i].functionId){//PREGUNTA SI ES EL PADRE
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
      
  
  




/*
FunctionStruct* setFunctionToExecutingVector(FunctionStruct FunctionToSet){
int i=0,j=0,n=0;
if(FunctionToSet.root==UNIQUE_FUNCTION){
  
    if(executingVector.vector[executingVector.pointer].functionId==0){
      executingVector.vector[executingVector.pointer]=FunctionToSet;
      return &executingVector.vector[executingVector.pointer];
      //executingVector.pointer=executingVector.pointer+1;
    } else{
      for(i=0;i<executingVector.pointer;i++){
        
        if(executingVector.vector[i].status==DONE||executingVector.vector[i].status==0){
          executingVector.vector[i]=FunctionToSet;
          //executingVector.pointer=executingVector.pointer+1;
          return &executingVector.vector[i];
        }
      }
       executingVector.pointer=executingVector.pointer+1;
       executingVector.vector[executingVector.pointer]=FunctionToSet;
       return &executingVector.vector[executingVector.pointer];
    }
}
else{
    if(FunctionToSet.root==MORE_FUNCTION){ //SI ES LA FUNCION PADRE BUSCO QUE TENGA LUGAR CONTIGUO PARA LOS HIJOS
       //SI es la primera funcion la pone en el primer lugar
       if(executingVector.vector[executingVector.pointer].functionId==0){
      executingVector.vector[executingVector.pointer]=FunctionToSet;
      return &executingVector.vector[executingVector.pointer];
       }else{//SINO TENGO QUE BUSCAR LUGAR
            for(i=0;i<=executingVector.pointer;i++){
        
              if(executingVector.vector[i].status==DONE||executingVector.vector[i].status==0){
              //BUSCO 3 LUGARES
                for(j=0;j<MAX_CHILDREN;j++){
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
    }
    
    else{ //SI SON LOS HIJOS LOS PONGO AL LADO DE LA FUNCION PADRE
       for(i=0;i<executingVector.pointer;i++){
        
        
        if(executingVector.vector[i].root==MORE_FUNCTION&&executingVector.vector[i].status!=DONE){
          if(FunctionToSet.root==executingVector.vector[i].functionId){
              for(j=1;j<=MAX_CHILDREN;j++){
                  if((executingVector.vector[i+j].root!=FunctionToSet.root)||executingVector.vector[i+j].status==DONE){
                     // executingVector.pointer=executingVector.pointer+1;
                      executingVector.vector[i+j]=FunctionToSet;
                      return &executingVector.vector[i+j];
                  }
              }
            
          }
        }
       }
       executingVector.pointer=executingVector.pointer+1;
       executingVector.vector[executingVector.pointer]=FunctionToSet;
       return &executingVector.vector[executingVector.pointer];
            
      
    }
}
      
  
  

}


/*FunctionStruct* setFunctionToExecutingVector(FunctionStruct FunctionToSet){
int i=0;
if(executingVector.vector[executingVector.pointer].functionId==0){
  executingVector.vector[executingVector.pointer]=FunctionToSet;
  return &executingVector.vector[executingVector.pointer];
  //executingVector.pointer=executingVector.pointer+1;
} else{
  for(i=0;i<executingVector.pointer;i++){
    
    if(executingVector.vector[i].status==DONE){
      executingVector.vector[i]=FunctionToSet;
      //executingVector.pointer=executingVector.pointer+1;
      return &executingVector.vector[i];
    }
  }
   executingVector.pointer=executingVector.pointer+1;
   executingVector.vector[executingVector.pointer]=FunctionToSet;
   return &executingVector.vector[executingVector.pointer];
}
  

}
*/


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


FunctionStruct* newFunctionInExecutingVector(){
  
  FunctionStruct newFunction;
  setToExecutingVector(newFunction);
  return &newFunction;
}

      

  
  

