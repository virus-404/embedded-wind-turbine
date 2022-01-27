/*
 * SLAVE CONFIG
 */

#include "Wire.h"
#include "SoftwareSerial.h"

#define SLAVE_ADDR 0x04
SoftwareSerial softSerial(2, 3); // RX, TX

char value= 'a';
int leng=0;
char cola[15];
uint8_t sp01;

void receiveFunc()
{
   while (Wire.available() != 1);
}

void sendFunc()
{
   
   Wire.write(cola[leng]);
}


void sendvalue(char value){
  return value;
}
void setup()
{
   // put your setup code here, to run once:
   Serial.begin(115200);
   softSerial.begin(9600);
   Wire.begin(SLAVE_ADDR);
   Wire.onReceive(receiveFunc);
   Wire.onRequest(sendFunc);
   
  
}

void loop()
{
     while(!softSerial.available());
     cola[leng]= softSerial.read();
     Serial.print(cola[leng]);
     //Wire.write(cola[leng]);
     //Serial.print("leng");
     Serial.println();
     //cola[leng]=softSerial.read();
     leng=leng+1;
     
      for(int i=0;i<=leng;i++){
        //Serial.print(cola[i]);
      }
      if(leng==15){
        leng=0;
      }
   delay(500);
   //Serial.println();
   
}
