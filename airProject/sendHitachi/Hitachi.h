#include "Arduino.h"
#ifndef Hitachi_h
#define Hitachi_h


const unsigned char ACT_NORMAL =     0x20;
const unsigned char ACT_OFFTIMER =   0x30;
const unsigned char ACT_ONTIMER =    0x30;


  const unsigned char STATUS_ON    = 0x08;
  const unsigned char STATUS_OFF   = 0x00;

  const unsigned char FAN_AUTO     = 0x00;
  const unsigned char FAN_1        = 0x10;
  const unsigned char FAN_2        = 0x20;
  const unsigned char FAN_3        = 0x30;

  const unsigned char MODE_COOL    = 0x40;
  const unsigned char MODE_DRY     = 0x80;
  const unsigned char MODE_FAN     = 0x00;

  const unsigned char SWEEP_ON     = 0x02;
  const unsigned char SWEEP_OFF    = 0x00;


  const unsigned char TEMP_18      = 0x03;
  const unsigned char TEMP_19      = 0x03;
  const unsigned char TEMP_20      = 0x05;
  const unsigned char TEMP_21      = 0x06;
  const unsigned char TEMP_22      = 0x07;
  const unsigned char TEMP_23      = 0x08;
  const unsigned char TEMP_24      = 0x09;
  const unsigned char TEMP_25      = 0x0A;
  const unsigned char TEMP_26      = 0x0B;
  const unsigned char TEMP_27      = 0x0C;
  const unsigned char TEMP_28      = 0x0D;
  const unsigned char TEMP_29      = 0x0E;
  const unsigned char TEMP_30      = 0x0F;

  const unsigned char SLEEP_ON      = 0x40;
  const unsigned char SLEEP_OFF      = 0x00;



class Hitachi{
  
  private:
    unsigned char params[6];  
    void calcChecksum();
  
  
  
  public:
    Hitachi();
    void getStatus();
    void execute();

    void turnOn();
    void turnOff();
  
  
  
};



#endif
