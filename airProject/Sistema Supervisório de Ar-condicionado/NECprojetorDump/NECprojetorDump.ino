/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

IRsend irsend;
int inByte;

unsigned int raw_liga[104] = {8950,4450,550,550,550,550,550,550,550,1650,550,1700,550,550,550,550,550,550,550,1650,550,550,550,550,550,1650,600,550,550,1600,600,1650,600,1600,600,500,600,500,600,500,600,1650,550,550,550,550,550,550,550,550,550,1650,600,1650,550,1650,550,550,550,1650,600,1650,550,1650,550,1650,600,500,600,500,600,500,600,550,550,500,600,550,550,550,550,550,550,1650,550,1650,600,1600,600,1650,550,1650,600,1600,600,1650,550,1650,600,14250,8900,2250,550,};
unsigned int raw_desliga[104] = {8950,4450,500,600,500,600,500,600,550,1650,550,1650,550,550,550,550,550,550,550,1700,550,550,550,550,550,1650,550,550,550,1650,600,1650,550,1650,550,550,550,550,550,1650,600,500,600,1600,600,550,550,550,550,550,550,1650,550,1650,600,500,600,1650,550,550,550,1650,600,1650,550,1650,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,550,1650,600,1650,550,1650,550,1650,600,1650,550,1650,550,1700,550,1650,550,14300,8900,2250,500,};



void setup()
{
  Serial.begin(9600);
}


void loop() {
  
  inByte = 0;
  /*
  if (Serial.read() != -1) {
    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(0x189710EF, 32); // Sony TV power code
      delay(40);
    }
  }
  */
  
  if (Serial.available() > 0) {
  
    inByte = Serial.read();
  
  Serial.println(inByte);
  
  if(inByte ==48){
   irsend.sendRaw(raw_desliga,104,38);
    // irsend.sendNEC(0x189728D7, 32); // Sony TV power code
    Serial.println('D');
  
  }else if (inByte ==49){
    irsend.sendRaw(raw_liga,104,38);
   // irsend.sendNEC(0x189710EF, 32); // Sony TV power code
    Serial.println('L');
  }
}
}
