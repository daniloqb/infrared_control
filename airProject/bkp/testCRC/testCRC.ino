#include "lib_crc.c";

/*/
 * 
 * CONSTANTS
 * 
 */

const byte ACT_NORMAL   = B00000001;
const byte ACT_CLEAR    = B00000111;
const byte ACT_FILTER   = B00001111;
const byte ACT_SLEEP    = B00001000;
const byte ACT_OFFTIMER = B00100110;
const byte ACT_ONTIMER  = B00110110;

const byte STATUS_ON    = B00010000;
const byte STATUS_OFF   = B00000000;

const byte FAN_AUTO     = B00001000;
const byte FAN_1        = B00000001;
const byte FAN_2        = B00000010;
const byte FAN_3        = B00000011;

const byte MODE_COOL    = B00000010;
const byte MODE_DRY     = B00000011;
const byte MODE_FAN     = B00000100;

const byte SWEEP_ON     = B00000001;
const byte SWEEP_OFF    = B00000000;


const byte TEMP_16      = B01000000;
const byte TEMP_17      = B01000100;
const byte TEMP_18      = B01001000;
const byte TEMP_19      = B01001100;
const byte TEMP_20      = B01010000;
const byte TEMP_21      = B01010100;
const byte TEMP_22      = B01011000;
const byte TEMP_23      = B01011100;
const byte TEMP_24      = B01100000;
const byte TEMP_25      = B01100100;
const byte TEMP_26      = B01101000;
const byte TEMP_27      = B01101100;
const byte TEMP_28      = B01110000;
const byte TEMP_29      = B01110100;
const byte TEMP_30      = B01111000;
const byte TEMP_31      = B01111100;
const byte TEMP_32      = B10000000;

const byte OFF_TIME     = B00000000;
const byte ON_TIME      = B00000000;

const byte BYTE_13      = B00000000;

const byte FOOTER = B11101100;

const byte header[] = {B00001000,B00010000,B00000111,B00000010,B01000000,B00001000};


unsigned short crc_calc;

byte  calc[] = {header[0], header[1], header[2], header[3], header[4], header[5], ACT_NORMAL, STATUS_ON+FAN_AUTO, MODE_COOL, TEMP_25, ON_TIME, OFF_TIME, BYTE_13, SWEEP_OFF};
byte code[17];



void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("Test CRC");
  Serial.println("Test CRC");

}

void loop() {


crc_calc = 0;

for(int i=0;i<14;i++){
  crc_calc = update_crc_16(crc_calc, calc[i]);
  code[i] = calc[i];
}

  code[14] = FOOTER;
  code[15] = crc_calc & 0x00FF;
  code[16] = (crc_calc & 0xFF00) >> 8;


Serial.println("CODE:");
for(int i=0;i<17;i++){
  

 Serial.print(code[i],BIN);
 Serial.print(" ");
}
Serial.println();
 
 delay(5000);
}
