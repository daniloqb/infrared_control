#include <IRremote.h>
#include "Arduino.h"
#include "York.h"
#include "lib_crc.c"

York::York() {

  params[0] = HEADER_1;
  params[1] = HEADER_2;
  params[2] = HEADER_3;
  params[3] = HEADER_4;
  params[4] = HEADER_5;
  params[5] = HEADER_6;
  params[6] = ACT_NORMAL;
  params[7] = STATUS_ON + FAN_AUTO;
  params[8] = MODE_COOL;
  params[9] = TEMP_25;
  params[10] = TIMER_OFF;
  params[11] = TIMER_OFF;
  params[12] = BYTE_13;
  params[13] = SWEEP_OFF;

};



void York::turnOn() {

  params[7] = params[7] & 0x0F;
  params[7] = STATUS_ON + params[7];

}

void York::turnOff() {

  params[7] = params[7] & 0x0F;
  params[7] = STATUS_OFF + params[7];

}


void York::setStatus(unsigned char status){

  params[7] = params[7] & 0x0F;
  params[7] = status + params[7];
  
}

void York::setMode(unsigned char mode){
  
  params[8] = mode;

  }

void York::setFan(unsigned char fan){

  params[7] = params[7] & 0xF0;
  params[7] = params[7] + fan;
  
}


void York::setAct(unsigned char act){

  params[6] = act;
  params[10] = TIMER_OFF;
  params[11] = TIMER_OFF;
  
}



void York::setAct(unsigned char act, unsigned char timer=0x00){

  params[6] = act;

  switch(act){

    case ACT_ONTIMER:
      params[10] = timer;
    break;

    case ACT_OFFTIMER||ACT_SLEEP:
      params[11] = timer;
    break;
  }
  
}

void York::setTemp(unsigned char temp){

  params[9] = temp;  
}











void York::getStatus() {

  for (int i = 0; i < 17; i++) {

    Serial.println(params[i], HEX);

  }

}

void York::updateCRC() {

  unsigned short crc_calc = 0;

  for (int i = 0; i < 14; i++) {
    crc_calc = update_crc_16(crc_calc, params[i]);
  }
  params[14] = FOOTER;
  params[15] = crc_calc & 0x00FF;
  params[16] = (crc_calc & 0xFF00) >> 8;

}


void York::execute() {

  IRsend irsend;
  unsigned char code[17];

  updateCRC();


  for (int i = 0; i < 17; i++) {
    code[i] = params[i];
  }

  irsend.sendYorkMKC(code, 8);

}

