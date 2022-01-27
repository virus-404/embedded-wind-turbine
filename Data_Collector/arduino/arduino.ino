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
   
   Wire.write(value);
}

void setup()
{
   // put your setup code here, to run once:
   Serial.begin(115200);
   softSerial.begin(115200);
   Wire.begin(SLAVE_ADDR);
   Wire.onReceive(receiveFunc);
   Wire.onRequest(sendFunc);
   
  
}

void loop()
{
  
  //if (softSerial.available())
   
     // value=softSerial.read();
     while(!softSerial.available());
     value= softSerial.read();
     cola[leng]=softSerial.read();
     leng=leng+1;
     //value ++;
      //if( value==' '){
        //Serial.print("aaaa");
      //}
      //  value = char(softSerial.read());
      //Serial.print(value);
      for(int i=0;i<=leng;i++){
        Serial.print(cola[i]);
      }
      if(leng==15){
        leng=0;
      }
      
      
   
   delay(500);
   Serial.println();
   /*if (softSerial.available()){
      //value = char(softSerial.read());
      value = softSerial.read();
      Serial.print(softSerial.read());
      //Serial.println(char(softSerial.read()));
      //delay(2500);
   }
   */
}
