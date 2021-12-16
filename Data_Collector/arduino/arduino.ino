/*
 * SLAVE CONFIG
 */

#include "Wire.h"

#define SLAVE_ADDR 0x04

uint8_t value;

void receiveFunc()
{
   while (Wire.available() != 1)
      ;
   value = (uint8_t)Wire.read();
   Serial.print("Value received: ");
   Serial.print(value);
   Serial.print("\n");
}

void sendFunc()
{
   Serial.print("Value send: ");
   Serial.println((uint8_t)(value  * 2));
   Wire.write((uint8_t)(value  * 2));
}

void setup()
{
   // put your setup code here, to run once:
   Serial.begin(9600);
   Wire.begin(SLAVE_ADDR);
   Wire.onReceive(receiveFunc);
   Wire.onRequest(sendFunc);
}

void loop()
{
   // put your main code here, to run repeatedly:
}
