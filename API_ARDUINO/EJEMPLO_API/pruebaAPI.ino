#include <API.h>

#define writeSerial(x) (Serial1.write(x))
#define availableSerial() (Serial1.available())
#define readSerial() (Serial1.read())

#define COMMAND_ERROR 1
#define INACCESSIBLE_DEVICE 2
#define TIMEOUT 3

uint8_t getResponse;

void Send(uint8_t DATA){
	writeSerial(DATA);
}
uint8_t Get(){
	getResponse = NULL;
	//for(int i=0; i > TIMERGET; i++){
		if(availableSerial()){
	    	  getResponse = (uint8_t)readSerial();
		}
	//}
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



void setup() {
    // initialize serial communications at 9600 bps:
  pinMode(18,INPUT);
  Serial.begin(9600);
  Serial1.begin(115200);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    bool data;
    uint16_t left = 12;
    uint16_t right = 12;
    data = SetVelocity(left, right);
    Serial.write(data);
  }
}

