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


#define TOP 0x80000000

unsigned long  airState[5]={};
unsigned long code;

int nbits = 32;


void setup()
{
  Serial.begin(9600);
 
}


void loop() {
    
  int choice = 0;
  
  if (Serial.available () > 0) {
    choice = Serial.parseInt();
    
    if ( choice == 2){
      for (int i = 0; i<5;i++){
        
        code = Serial.parseInt();
        airState[i] = code;        
      }
      
      enviar();  
    }
  } 
  
}
   
   
   
   void enviar(){
   
 // irsend.sendYork(airState[0],airState[1],airState[2],airState[3],airState[4],32);
 irsend.sendYork(airState,32);
  
   }
