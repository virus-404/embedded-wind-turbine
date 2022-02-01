/*
 * SLAVE CONFIG
 */

#include "Wire.h"
#include "SoftwareSerial.h"

#define SLAVE_ADDR 0x04
SoftwareSerial softSerial(2, 3); // RX, TX


int leng=0;
int leng2=0;
char cola[29];
char pos[14];
uint8_t sp01;

void receiveFunc()
{
   while (Wire.available() != 1);
}

void sendFunc()
{
  Wire.write(cola[leng2]);
  Serial.print(leng2);
  leng2=leng2+1;
  if(leng2==30){
      leng2=0;
  }
  /*
  for(int i = 0;i<=29;i++){
    Wire.write(cola[i]);
    Serial.print(cola[i]);
  }
  Serial.println();
  //Wire.write(cola[leng]);
  //Serial.println(cola[leng]);
*/
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
    cola[leng]=Serial.read();
    //Serial.print(cola[leng]);
    leng=leng+1;
    if(leng==30 || cola[leng-1]=='p' ){
      leng=0;
    }
    //cola[0]='w';
  }
}
