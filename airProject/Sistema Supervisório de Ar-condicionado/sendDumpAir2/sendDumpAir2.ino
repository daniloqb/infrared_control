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

unsigned long int desligar[5] = {0x1008E040,0x02108010,0x40260000,0x00003729,0x98};

unsigned long int data0 = 0x1008E040;
unsigned long int data1 = 0x02108010;
unsigned long int data2 = 0x40260000;
unsigned long int data3 = 0x00003729;
unsigned int data4 = 0x98;

int nbits = 32;

unsigned int raw_desliga[275] = {4800, 2400, 560, 560, 560, 560, 560, 560, 560, 1850, 584, 624, 592, 624, 592, 620, 600, 604, 608, 608, 608, 600, 612, 600, 612, 604, 612, 1800, 624, 608, 604, 600, 612, 600, 616, 1800, 616, 1800, 616, 1800, 612, 592, 616, 608, 608, 596, 616, 600, 612, 600, 612, 596, 620, 1800, 616, 604, 608, 596, 616, 600, 616, 608, 604, 600, 612, 608, 604, 612, 604, 604, 608, 600, 612, 616, 596, 604, 612, 600, 612, 1800, 616, 588, 628, 596, 616, 596, 616, 608, 604, 1800, 612, 600, 612, 600, 616, 600, 612, 600, 612, 1800, 612, 608, 604, 600, 616, 596, 616, 596, 616, 604, 608, 604, 612, 608, 604, 612, 600, 600, 616, 600, 612, 1832, 596, 596, 616, 608, 608, 596, 616, 600, 612, 600, 612, 1824, 604, 600, 616, 608, 604, 600, 612, 608, 604, 612, 604, 600, 612, 604, 608, 600, 616, 1824, 604, 604, 608, 1800, 616, 592, 620, 1820, 608, 596, 616, 600, 612, 612, 600, 604, 608, 612, 604, 608, 604, 612, 600, 600, 616, 608, 604, 604, 608, 604, 612, 600, 612, 604, 608, 612, 604, 612, 600, 612, 600, 604, 612, 608, 604, 600, 612, 608, 604, 612, 604, 604, 608, 612, 600, 612, 604, 608, 604, 616, 596, 616, 600, 612, 600, 612, 600, 612, 604, 612, 600, 600, 612, 604, 608, 616, 600, 616, 596, 1800, 612, 1800, 612, 600, 612, 1828, 600, 1800, 616, 1800, 612, 612, 596, 612, 596, 1820, 604, 628, 584, 1836, 600, 616, 596, 1832, 604, 1800, 624, 1800, 624, 588, 624, 1800, 628, 1800, 640, 1800, 632, 572, 640, 588, 620, 592, 624};

unsigned int raw_liga[275] = {4800, 2400, 556, 660, 548, 664, 552, 664, 548, 1850, 572, 664, 548, 664, 548, 664, 552, 664, 548, 664, 548, 668, 548, 684, 532, 620, 592, 1850, 572, 664, 548, 668, 548, 636, 580, 1850, 576, 1852, 576, 1848, 576, 664, 548, 664, 552, 660, 552, 664, 548, 668, 548, 640, 572, 1852, 576, 664, 544, 668, 548, 644, 572, 620, 592, 608, 608, 588, 624, 608, 604, 608, 608, 612, 600, 616, 596, 616, 600, 608, 604, 1852, 576, 592, 620, 608, 604, 608, 608, 612, 600, 1852, 576, 640, 572, 608, 604, 596, 616, 588, 628, 1848, 580, 632, 576, 616, 600, 580, 636, 576, 636, 608, 604, 608, 608, 588, 620, 1856, 576, 1844, 580, 664, 548, 620, 596, 1848, 576, 632, 576, 648, 572, 616, 600, 584, 628, 1820, 604, 636, 576, 624, 592, 580, 632, 584, 632, 588, 624, 580, 632, 588, 628, 584, 628, 1800, 628, 580, 632, 1800, 624, 636, 576, 1800, 628, 628, 588, 616, 596, 580, 632, 584, 632, 580, 632, 584, 632, 580, 632, 580, 632, 580, 636, 580, 632, 584, 628, 584, 628, 568, 648, 580, 632, 584, 628, 584, 632, 580, 628, 588, 628, 584, 632, 580, 632, 584, 632, 580, 628, 584, 628, 588, 628, 584, 628, 584, 632, 584, 628, 588, 624, 588, 628, 584, 628, 584, 632, 580, 632, 584, 628, 584, 632, 584, 624, 1800, 632, 1796, 628, 568, 648, 1796, 628, 1800, 628, 1796, 628, 1776, 652, 1800, 624, 1800, 628, 1796, 632, 1776, 648, 1796, 632, 1800, 624, 612, 604, 608, 604, 608, 608, 1800, 628, 1796, 628, 1796, 628, 612, 600, 612, 604, 608, 608};

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

    irsend.sendYork(desligar[0],desligar[1],desligar[2],desligar[3],desligar[4],32);
    // irsend.sendRaw(raw_desliga,275,38);
    Serial.println('D');
  
  }else if (inByte ==49){
    irsend.sendRaw(raw_liga,275,38);
    Serial.println('L');
  }
}
}
