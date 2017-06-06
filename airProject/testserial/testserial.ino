

unsigned long int airState[5]={};
unsigned long code;
String inString = "";
char *tmp;
int i;

void setup() {
  
 
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


}


void loop() {
        boolean currentLineIsBlank = true;

        char c = 0;
        
        if (Serial.available() > 0){
            c = Serial.read();
            //Serial.write(c);
            
            inString += c;
        }
        
        if (c == '#'){
          
          i = 0;
          tmp = strtok(&inString[0], " ");
          while (tmp) {
              airState[i++] = atol(tmp);
              tmp = strtok(NULL, " ");
          }
          
          for(i=0;i<5;i++){
          
                Serial.println(airState[i]);
          
          }
          
          Serial.println(inString);
          inString = "";
        }
        
        
   
    delay(13);

  }


