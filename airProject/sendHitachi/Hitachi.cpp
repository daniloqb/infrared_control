#include <IRremote.h>
#include "Arduino.h"
#include "Hitachi.h"


Hitachi::Hitachi(){

    params[0] = ACT_NORMAL + STATUS_ON + SLEEP_OFF + SWEEP_OFF;
    params[1] = MODE_COOL + FAN_AUTO + TEMP_23;
    params[2] = 0x00;
    params[3] = 0x00;
    params[4] = 0x00;
    
    
}


void Hitachi::execute(){

  IRsend irsend;
  unsigned char code[6];
  calcChecksum();
  


    for (int i = 0; i < 6; i++) {
      code[i] = params[i];
  }

  irsend.sendAirHitachi(code, 8);
  
}


void Hitachi::turnOn(){

  params[0] = ACT_NORMAL + STATUS_ON + SLEEP_OFF + SWEEP_OFF;
  
  
}



void Hitachi::turnOff(){

  params[0] = ACT_NORMAL + STATUS_OFF + SLEEP_OFF + SWEEP_OFF;
  
}




void Hitachi::calcChecksum(){


  byte checksum = 0;

  byte byteA, byteB;


  for( int i =0; i< 5;i++){

   byteA = params[i] & 0xF0;
   byteB = params[i] & 0x0F;

   byteA = byteA >> 4;

   checksum = checksum +( byteA + byteB);
    
  }

  checksum = (~checksum) & 0x0F;
  
  params[5] = checksum;
  
}



void Hitachi::getStatus() {

  for (int i = 0; i < 6; i++) {

    Serial.print(params[i], HEX);
    Serial.print(" ");

  }
  Serial.println();

}


