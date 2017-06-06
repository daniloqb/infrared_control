#include "Arduino.h"

#ifndef York_h
#define York_h


  const unsigned char ACT_NORMAL   = 0x01;
  const unsigned char ACT_CLEAR    = 0x07;
  const unsigned char ACT_FILTER   = 0x0F;
  const unsigned char ACT_SLEEP    = 0x08;
  const unsigned char ACT_OFFTIMER = 0x26;
  const unsigned char ACT_ONTIMER  = 0x36;

  const unsigned char STATUS_ON    = 0x10;
  const unsigned char STATUS_OFF   = 0x00;

  const unsigned char FAN_AUTO     = 0x08;
  const unsigned char FAN_1        = 0x01;
  const unsigned char FAN_2        = 0x02;
  const unsigned char FAN_3        = 0x03;

  const unsigned char MODE_COOL    = 0x02;
  const unsigned char MODE_DRY     = 0x03;
  const unsigned char MODE_FAN     = 0x04;

  const unsigned char SWEEP_ON     = 0x01;
  const unsigned char SWEEP_OFF    = 0x00;


  const unsigned char TEMP_16      = 0x40;
  const unsigned char TEMP_17      = 0x44;
  const unsigned char TEMP_18      = 0x48;
  const unsigned char TEMP_19      = 0x4c;
  const unsigned char TEMP_20      = 0x50;
  const unsigned char TEMP_21      = 0x54;
  const unsigned char TEMP_22      = 0x58;
  const unsigned char TEMP_23      = 0x5c;
  const unsigned char TEMP_24      = 0x60;
  const unsigned char TEMP_25      = 0x64;
  const unsigned char TEMP_26      = 0x68;
  const unsigned char TEMP_27      = 0x6c;
  const unsigned char TEMP_28      = 0x70;
  const unsigned char TEMP_29      = 0x74;
  const unsigned char TEMP_30      = 0x78;
  const unsigned char TEMP_31      = 0x7c;
  const unsigned char TEMP_32      = 0x80;

  const unsigned char SLEEP_1H     = 0x06;
  const unsigned char SLEEP_2H     = 0x0C;
  const unsigned char SLEEP_3H     = 0x12;
  const unsigned char SLEEP_5H     = 0x1E;
  const unsigned char SLEEP_7H     = 0x1A;
  const unsigned char SLEEP_9H     = 0x00;

  const unsigned char TIMER_OFF       = 0x06;
  const unsigned char TIMER_1H        = 0x09;
  const unsigned char TIMER_1H30      = 0x0c;
  const unsigned char TIMER_2H        = 0x0f;
  const unsigned char TIMER_2H30      = 0x12;
  const unsigned char TIMER_3H        = 0x15;
  const unsigned char TIMER_3H30      = 0x18;
  const unsigned char TIMER_4H        = 0x1B;
  const unsigned char TIMER_4H30      = 0x1E;
  const unsigned char TIMER_5H        = 0x21;
  const unsigned char TIMER_5H30      = 0x24;
  const unsigned char TIMER_6H        = 0x27;
  const unsigned char TIMER_6H30      = 0x2A;
  const unsigned char TIMER_7H        = 0x2D;
  const unsigned char TIMER_7H30      = 0x30;
  const unsigned char TIMER_8H        = 0x33;
  const unsigned char TIMER_8H30      = 0x36;
  const unsigned char TIMER_9H        = 0x39;
  const unsigned char TIMER_9H30      = 0x3C;
  const unsigned char TIMER_10H       = 0x3F;
  const unsigned char TIMER_10H30     = 0x42;
  const unsigned char TIMER_11H       = 0x45;
  const unsigned char TIMER_11H30     = 0x48;
  const unsigned char TIMER_12H       = 0x4B;
  const unsigned char TIMER_12H30     = 0x4E;
  const unsigned char TIMER_13H       = 0x51;
  const unsigned char TIMER_13H30     = 0x54;
  const unsigned char TIMER_14H       = 0x57;
  const unsigned char TIMER_14H30     = 0x5A;
  const unsigned char TIMER_15H       = 0x5D;
  const unsigned char TIMER_15H30     = 0x60;
  const unsigned char TIMER_16H       = 0x63;
  const unsigned char TIMER_16H30     = 0x66;
  const unsigned char TIMER_17H       = 0x69;
  const unsigned char TIMER_17H30     = 0x6C;
  const unsigned char TIMER_18H       = 0x6F;
  const unsigned char TIMER_18H30     = 0x72;
  const unsigned char TIMER_19H       = 0x75;
  const unsigned char TIMER_19H30     = 0x78;
  const unsigned char TIMER_20H       = 0x7B;
  const unsigned char TIMER_20H30     = 0x7E;
  const unsigned char TIMER_21H       = 0x81;
  const unsigned char TIMER_21H30     = 0x84;
  const unsigned char TIMER_22H       = 0x87;
  const unsigned char TIMER_22H30     = 0x8A;
  const unsigned char TIMER_23H       = 0x8D;
  const unsigned char TIMER_23H30     = 0x90;
  const unsigned char TIMER_24H       = 0x93;




  const unsigned char HEADER_1     = 0x08;
  const unsigned char HEADER_2     = 0x10;
  const unsigned char HEADER_3     = 0x07;
  const unsigned char HEADER_4     = 0x02;
  const unsigned char HEADER_5     = 0x40;
  const unsigned char HEADER_6     = 0x08;

  const unsigned char FOOTER       = 0xEC;

  const unsigned char BYTE_13      = 0x00;




class York{

  private:
    unsigned char params[17];
    void updateCRC();
    

  
  public:
    York(); 
    void turnOn();
    void turnOff();
    
    void setStatus(unsigned char status);
    void setMode(unsigned char mode);
    void setFan(unsigned char fan);
    void setAct(unsigned char act);
    void setAct(unsigned char act, unsigned char timer);
    void setTemp(unsigned char temp);

    
    
    void getStatus();
    void execute();

     
  };



#endif
