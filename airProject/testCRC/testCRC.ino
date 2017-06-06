

#include "York.h"



York york;

void setup() {

  Serial.begin(9600);



}

void loop() {

york.setAct(ACT_OFFTIMER,TIMER_11H30);

york.setStatus(STATUS_ON);
york.execute();
 
delay(5000);


york.setStatus(STATUS_OFF);
york.execute();

while(true);
}

