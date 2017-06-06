
#include <aJSON.h>

#include <IRremote.h>




aJsonStream serial_stream(&Serial);
IRsend irsend;
int inByte;


#define TOP 0x80000000

unsigned long  airState[5]={};
int airIndex = 0;
unsigned long code;

int nbits = 32;


void setup()
{
  Serial.begin(9600);
 
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
  

  /*enviar status*/

  aJsonObject *state = aJson.getObjectItem(msg, "state");

  Serial.println(state->valuestring);
  




 
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
