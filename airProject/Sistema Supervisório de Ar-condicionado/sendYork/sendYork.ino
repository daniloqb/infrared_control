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

//unsigned long int desligar[5] = {0x1008E040,0x02108010,0x40260000,0x00003729,0x98};
//unsigned long int ligar[5] = {0x1008E040,0x0210A018,0x40060000,0x000037AE,0xD7};

unsigned long int airState[5]={};

int nbits = 32;

void setup()
{
  Serial.begin(9600);
 
}


void loop() {
  
  inByte = 0;

  
  if (Serial.available() > 0) {
      inByte = Serial.read();
  
      Serial.println(inByte);
  
      if(inByte ==48){
           desligarAr();
           Serial.println('D');
  
      }else if (inByte ==49){
          ligarAr();
           Serial.println('L');
      }
      else if (inByte ==51){
        fan03();
        Serial.println('3');
      }
   }
   
   

}

   void ligarAr(){

     
     airState[0]=0x1008E040;
     airState[1]=0x02108018;
     airState[2]=0x40060000;
     airState[3]=0x008037AD;
     airState[4]=0x1B;
     
     
   
   enviar();  
 //   irsend.sendYork(0x1008E040,0x0210A018,0x40060000,0x000037AE,0xD7,32);
   }
   
   void desligarAr(){
    
     airState[0]=0x1008E040;
     airState[1]=0x02108010;
     airState[2]=0x40060000;
     airState[3]=0x00803725;
     airState[4]=0x98;
     
     
     enviar();

   }
   
   
   
   void fan03(){

     
     airState[0]=0x1008E040;
     airState[1]=0x02108048;
     airState[2]=0x40060000;
     airState[3]=0x008037F8;
     airState[4]=0x1B;
     
     
   
   enviar();  
 //   irsend.sendYork(0x1008E040,0x0210A018,0x40060000,0x000037AE,0xD7,32);
   }
   
   
   
   void enviar(){
   
   irsend.sendYork(airState[0],airState[1],airState[2],airState[3],airState[4],32);
  
   }
