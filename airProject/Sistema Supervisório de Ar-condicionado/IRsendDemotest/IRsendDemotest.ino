/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

IRsend irsend;

void setup()
{
  Serial.begin(9600);
}

void loop() {
  int a = 0;
  a = Serial.rea
  if (Serial.read() ==1) {    
      irsend.sendNEC(0x189728D7, 32); // Sony TV power code
      }
  }
}
