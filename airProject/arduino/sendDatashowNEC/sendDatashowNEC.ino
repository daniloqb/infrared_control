/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <SoftwareSerial.h>

#include <IRremote.h>

#include "DatashowNEC.h"

DatashowNEC nec;

SoftwareSerial mySerial(10, 11); // RX, TX

void setup()
{
  mySerial.begin(9600);
}

void loop() {
  /*
  nec.btn_powerOn();
	delay(5000); //5 second delay between each signal burst
  nec.btn_powerOff();
 delay(5000); //5 second delay between each signal burst

 */


 if (mySerial.available()){

  int command = mySerial.parseInt();


  switch(command){


   case 10:
     nec.btn_powerOff();
   break;   
   case 11:
     nec.btn_powerOn();
   break;
   case 12:
     nec.btn_autoAdj();
   break;
   case 0:
     nec.btn_num0();
   break;
   case 1:
     nec.btn_num1();
   break;
   case 2:
     nec.btn_num2();
   break;   
   case 3:
     nec.btn_num3();
   break;
   case 4:
     nec.btn_num4();
   break;
   case 5:
     nec.btn_num5();
   break;
   case 6:
     nec.btn_num6();
   break;
   case 7:
     nec.btn_num7();
   break;   
   case 8:
     nec.btn_num8();
   break;
   case 9:
     nec.btn_num9();
   break;
   case 13:
     nec.btn_idSet();
   break;
   case 14:
     nec.btn_clear();
   break;
   case 15:
     nec.btn_avMute();
   break;
   case 16:
     nec.btn_freeze();
   break;
   case 17:
     nec.btn_exit();
   break;
   case 18:
     nec.btn_menu();
   break;
   case 19:
     nec.btn_arrowUp();
   break;
   case 20:
     nec.btn_arrowDown();
   break;
   case 21:
     nec.btn_arrowLeft();
   break;
   case 22:
     nec.btn_arrowRight();
   break;
   case 23:
     nec.btn_enter();
   break;
   case 24:
     nec.btn_zoomPlus();
   break;
   case 25:
     nec.btn_zoomMinus();
   break;
   case 26:
     nec.btn_pageUp();
   break;
   case 27:
     nec.btn_pageDown();
   break;
   case 28:
     nec.btn_lClick();
   break;
   case 29:
     nec.btn_rClick();
   break;
   case 30:
     nec.btn_echo();
   break;          
   case 31:
     nec.btn_keystone();
   break;
   case 32:
     nec.btn_picture();
   break;
   case 33:
     nec.btn_help();
   break;
   case 34:
     nec.btn_focus();
   break;
   case 35:
     nec.btn_aspect();
   break;
   case 36:
     nec.btn_volUp();
   break;
   case 37:
     nec.btn_volDown();
   break;                                                                       
    
  }
 }


 
 
}
