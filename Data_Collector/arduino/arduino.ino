/*
 * SLAVE CONFIG
 */

#include "Wire.h"
#include "SoftwareSerial.h"

#define SLAVE_ADDR 0x04
SoftwareSerial softSerial(2, 3); // RX, TX

uint8_t value;
uint8_t sp01;

void receiveFunc()
{
   while (Wire.available() != 1)
      ;
     
   /*value = (uint8_t) Wire.read();
   Serial.print("Value received: ");
   Serial.print(value);
   Serial.print("\n");
   */
}

void sendFunc()
{
   //Serial.print("Value send: ");
   //Serial.println((uint8_t)(value  * 2));
   Wire.write((uint8_t)(value));
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
   if (softSerial.available())
         value = (uint8_t) softSerial.read();
         delay(250);
   
}
