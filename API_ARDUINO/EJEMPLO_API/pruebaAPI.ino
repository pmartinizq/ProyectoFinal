#include <API.h>


#define writeSerial(x) (Serial3.write(x))
#define availableSerial() (Serial3.available())
#define readSerial() (Serial3.read())

#define COMMAND_ERROR 17
#define INACCESSIBLE_DEVICE 18
#define TIMEOUT 19

uint8_t getResponse;
int time=0,paquetes=0;

void Send(uint8_t DATA){
	writeSerial(DATA);
}
uint8_t Get(){
        long time=0;
	getResponse = NULL;
  
	//for(int i=0; i > TIMERGET; i++){
        time=1000000;
        while(availableSerial()==0&&time!=0){
          time--;}
        Serial.print("-->");
        
        getResponse = (uint8_t)readSerial();
        Serial.print(getResponse,HEX);
        /*
        while(availableSerial()==0&&time<320000){
          time++;}
          if(time==320000){
            Serial.println("Error");
            getResponse =0;
          }else{
	    getResponse = (uint8_t)readSerial();
          }*/
        //Serial.print("Recibe: ");
        //Serial.println(getResponse,HEX);
        
		
	//}
	return getResponse;
}
void ErrorPrint(char function[], uint8_t var){
	Serial.print("\tERROR: ");
	if(var == INACCESSIBLE_DEVICE){
		Serial.print("INACCESSIBLE DEVICE");
	}
	else{
		if(var == COMMAND_ERROR){
			Serial.print("COMMAND ERROR");
		}
		else{
			if(var == TIMEOUT){
				Serial.print("TIMEOUT");
			}
     else{
      	Serial.print(var);
     }
		}
	}
	Serial.print(" in function: ");
	Serial.print(function); 
	Serial.println(".");
}



void setup() {
    // initialize serial communications at 9600 bps:
  pinMode(18,INPUT);
  Serial.begin(9600);
  Serial3.begin(115200);
  /*TCCR1A = 0;
  TCCR1B = 0; 
  TCNT1 = 34286;   // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  */
}

void loop() {
  // put your main code here, to run repeatedly:
  

  
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    if(inChar=='a'){
    Serial.print("Frente igual a...");
    Serial.println(GetMeassure(ULTRASONIC_FRONT)[0],DEC);
    }
    
    if(inChar=='b'){
    Serial.print("Izquierda igual a...");
    Serial.println(GetMeassure(ULTRASONIC_LEFT)[0],DEC);
    }
    
    if(inChar=='c'){
    Serial.print("Derecha igual a...");
    Serial.println(GetMeassure(ULTRASONIC_RIGHT)[0],DEC);
    }
    
    if(inChar=='d'){
    Serial.print("Utrasonic All igual a...");
    int *puntero=GetMeassure(ULTRASONIC_ALL);
    Serial.print(puntero[0],DEC);
    Serial.print(" - ");
    Serial.print(puntero[1],DEC);
    Serial.print(" - ");
    Serial.println(puntero[2],DEC);
    }
    
    if(inChar=='e'){
    Serial.print("SetVelocity");
    SetVelocity(100,0);
    Serial.println(" ");
    }
    
    if(inChar=='f'){
    Serial.print("SetVelocity");
    SetVelocity(0,0);
    Serial.println(" ");
    }

    if(inChar=='i'){
    Serial.print("SetSteps");
    SetSteps(40,40);
    Serial.println(" ");
    }
    
    if(inChar=='h'){
    Serial.println("Prueba de fuego");
    while(1){
      //Serial.println(GetMeassure(ULTRASONIC_ALL)[0],DEC);
      GetMeassure(ULTRASONIC_ALL);
      paquetes++;
      //delay(1);
    }
    }
    
    if(inChar=='g'){
    Serial.print("Is goal:");
    if(IsGoal(15)){
      Serial.println(" -> SI");
    }
    else{
       Serial.println(" -> NO");
    }
    }

     if(inChar=='j'){
    Serial.print("ACCEL igual a...");
    int *puntero=GetMeassure(ACCEL);
    Serial.print(puntero[0],DEC);
    Serial.print(" - ");
    Serial.print(puntero[1],DEC);
    Serial.print(" - ");
    Serial.println(puntero[2],DEC);
    }

     if(inChar=='k'){
    Serial.print("GYRO igual a...");
    int *puntero=GetMeassure(GYRO);
    Serial.print(puntero[0],DEC);
    Serial.print(" - ");
    Serial.print(puntero[1],DEC);
    Serial.print(" - ");
    Serial.println(puntero[2],DEC);
    }

     if(inChar=='l'){
    Serial.print("COMPASS igual a...");
    int *puntero=GetMeassure(COMPASS);
    Serial.println(puntero[0],DEC);
    }
    //SetVelocity(inChar,0);
    // add it to the inputString:
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    
  }
}

/*
ISR(TIMER1_OVF_vect)        // interrupt service routine 
{
  TCNT1 = 34286;   // preload timer
  time++;
  Serial.print("Time:");
  Serial.print(time,DEC);
  Serial.print("Paquetes: ");
  Serial.println(paquetes,DEC);
}*/


