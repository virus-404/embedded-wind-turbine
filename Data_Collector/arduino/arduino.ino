/*
 * SLAVE CONFIG
 */

#include "Wire.h"
#include "SoftwareSerial.h"

#define SLAVE_ADDR 0x04
SoftwareSerial softSerial(2, 3); // RX, TX


int leng=0;
uint8_t cola[29];
char pos[14];
uint8_t sp01;

void receiveFunc()
{
   while (Wire.available() != 1);
}

void sendFunc()
{
   while(Wire.available()!=2);
   uint8_t i = (uint8_t)Wire.read();
   Wire.write((int)cola[i]);
}

void setup()
{
   // put your setup code here, to run once:
   Serial.begin(115200);
   Wire.begin(SLAVE_ADDR);
   Wire.onReceive(receiveFunc);
   Wire.onRequest(sendFunc);


}

void loop()
{
  if(Serial.available()){
    cola[leng]=(int) Serial.read();
    //Serial.print(cola[leng]);
    leng=leng+1;
    if(leng==30 || cola[leng-1]== 80){ //p in ascii
      leng=0;
    }
  }
 }
