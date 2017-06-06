/*
  Web Server
 
 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)
 
 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 
 */
 

// Include the libraries we need





#include <SPI.h>
#include <Ethernet.h>
#include <IRremote.h>

#include <OneWire.h>
#include <DallasTemperature.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(143,106,230,104);

EthernetServer server(80);

IRsend irsend;
int inByte;
int nbits = 32;
int ledPin = 8;

unsigned long int airState[6]={};
unsigned long code;
String inString = "";
char *tmp;
int i;

#define TOP 0x80000000



// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);



// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):








void setup() {

  pinMode(ledPin,OUTPUT);
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
  
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only

      Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();
  }


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    String inString = "";
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
            Serial.print(c);
            inString += c;
        //Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header



          Serial.print("String:");
          Serial.println(inString);
          i = 0;
          int itens = 0;
          tmp = strtok(&inString[0], " ");
          while (tmp) {
              airState[i++] = atol(tmp);
              tmp = strtok(NULL, " ");
              itens++;
          }
          Serial.print("itens:");
          Serial.println(itens);
          
          for(i=0;i<itens;i++){
          
                Serial.println(airState[i]);
          
          }
    
          inString = "";
          Serial.println(airState[0]);
          switch(airState[0]){

            case 2:
              Serial.print("Requesting temperatures...");
              sensors.requestTemperatures(); // Send the command to get temperatures
               Serial.println("DONE");
              // After we got the temperatures, we can print them here.
              // We use the function ByIndex, and as an example get the temperature from the first sensor only.
             Serial.print("Temperature for the device 1 (index 0) is: ");
               Serial.println(sensors.getTempCByIndex(0));
            
            case 3:
               Serial.println("York Infrared");
               client.println("York Infrared");
               enviar();
               break;
            case 5:
                 digitalWrite(ledPin,airState[1]);
                 client.println("HTTP/1.1 200 OK");                 
                 client.println("Content-Type: text/html");
                 client.println("Connection: close");  // the connection will be closed after completion of the response
                 client.println("Refresh: 5");  // refresh the page automatically every 5 sec
                 client.println();
                 client.println("Led Control: ");
                 client.println(digitalRead(ledPin));
                 client.println("<!DOCTYPE HTML>");
                 client.println("<html>");
                Serial.println("Led Control");

                
                break;
          }
          /*
          if (airState[0] == 3){
            digitalWrite(ledPin,LOW);
          enviar();
          }
          else {
            digitalWrite(ledPin,HIGH);
            }

            */
          break;
        }
        
       
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
   
        }
        }
    }
    // give the web browser time to receive the data
    delay(3);
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}


   void enviar(){
   
   irsend.sendYork(airState[1],airState[2],airState[3],airState[4],airState[5],32);
  
   }

