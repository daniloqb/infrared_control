
#include <aJSON.h>
#include "EmonLib.h"
#include <IRremote.h>

#include <OneWire.h>
#include <DallasTemperature.h>



// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

EnergyMonitor emon1;                  // Create an instance
int pino_sct = A1;
int rede = 110;
double Irms;


double power[20];
int index = 0;

aJsonStream serial_stream(&Serial);
IRsend irsend;
int inByte;
byte ldrPin = A0;



#define TOP 0x80000000

unsigned long  airState[5]={};
int airIndex = 0;
unsigned long code;

int nbits = 32;


void setup()
{
  Serial.begin(9600);
  sensors.begin();
   emon1.current(pino_sct, 111.1);
 
}



void processMessage(aJsonObject *msg)
{

  /* controlar o ar condicionado*/
  aJsonObject *york = aJson.getObjectItem(msg, "york");
  
  if (york) {

    aJsonObject *longValues = aJson.getObjectItem(york,0);
    

    while(longValues!=NULL){
      airState[airIndex++] = atol(longValues->valuestring);
      longValues = longValues->next;
            
    }
    airIndex = 0;
    enviar();
    
  }
  aJson.deleteItem(york);

  

  /*enviar status*/

  aJsonObject *state = aJson.getObjectItem(msg, "state");

  if(state){
   aJsonObject *msg = aJson.createObject();

   aJson.addNumberToObject(msg,"light",analogRead(A0));
   

   sensors.requestTemperatures(); // Send the command to get temperatures
   aJson.addNumberToObject(msg,"temperature",sensors.getTempCByIndex(0));          

  for(int i=0;i< 20; i++)
    Irms = emon1.calcIrms(1480);
 
    
    aJson.addNumberToObject(msg,"power",Irms);          

   


   Serial.println(aJson.print(msg));
  }
  aJson.deleteItem(state);
  




 
}




void loop()
{


  
 
  if (serial_stream.available()) {
    /* First, skip any accidental whitespace like newlines. */
    serial_stream.skip();
  }

  if (serial_stream.available()) {
    /* Something real on input, let's take a look. */
    aJsonObject *msg = aJson.parse(&serial_stream);
    processMessage(msg);
    aJson.deleteItem(msg);
  }


}



   
   
   
   void enviar(){
   
 // irsend.sendYork(airState[0],airState[1],airState[2],airState[3],airState[4],32);
 irsend.sendYork(airState,32);
  
   }
