

#include "York.h"



York york;

void setup() {

  Serial.begin(9600);



}

void loop() {

york.setStatus(STATUS_ON);
york.execute();
 
delay(5000);


york.setStatus(STATUS_OFF);
york.execute();

//while(true);
delay(5000);
}

