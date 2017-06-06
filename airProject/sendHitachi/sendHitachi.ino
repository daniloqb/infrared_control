#include "Hitachi.h"

Hitachi hitachi;

void setup() {
  Serial.begin(9600);
}

void loop() {
  hitachi.turnOn();
  hitachi.getStatus();
  hitachi.execute();
  delay(5000);

  
  hitachi.turnOff();
  hitachi.getStatus();
  hitachi.execute();
  delay(5000);

}
