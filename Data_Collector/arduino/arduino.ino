/*
 * SLAVE CONFIG
 */

#include "Wire.h"
#include "SoftwareSerial.h"

#define SLAVE_ADDR 0x04
SoftwareSerial softSerial(2, 3); // RX, TX


int leng=0;
char cola[25];
uint8_t sp01;

void receiveFunc()
{
   while (Wire.available() != 1);
}

void sendFunc()
{
  Wire.write(cola[leng]); 
  Serial.println(cola[leng]);
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
 
  while(!Serial.available());
    cola[leng]= Serial.read();  
    leng=leng+1;
    if(leng==25){
      leng=0; 
    }  
}
