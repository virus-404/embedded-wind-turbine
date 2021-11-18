#include "Wire.h"

#define WIRE_SPEED 3400000

#define MCPADDRESS 0x20 // Conf LOW-LOW-LOW

// Main registers
#define IODIRA 0x00
#define IODIRB 0x01
#define IOCON  0x05
#define GPIOA  0x12
#define GPIOB  0x13
#define GPPUA  0x0C
#define GPPUB  0x0D

// Control
#define BANK   0x80 // 0b10000000 --> 1 Different banks, 0 Same bank
#define MIRROR 0x40 // 0b01000000 --> 1 Int connected, 0 Int dissociated (A/B)
#define SEQOP  0x20 // 0b00100000 --> 1 SEQ, 0 DIRECT
#define DISSLW 0x10 // 0b00010000 --> 1 Disabled
#define HAEN   0x08 // 0b00001000 --> 1 HW , 0 Disabled
#define ODR    0x04 // 0b00000100 --> 1 Open Drain
#define INTPOL 0x02 // 0b00000010 --> 1 INT Active High, INT 0 Active Low



uint16_t time1, time2;

void setup()
{
  Serial.begin(9600); //9600bps
  //while (!Serial) {}; //Serial port initialization

  Wire.setClock(WIRE_SPEED); // I2C Bus speed
  
  Wire.begin();     // wake up I2C bus
  
  // MCP Configuration
  Wire.beginTransmission(MCPADDRESS);
  Wire.write(IOCON);  // Sequential access - better performance
  Wire.write(SEQOP | MIRROR | HAEN );
  Wire.endTransmission(); 
 
  Wire.beginTransmission(MCPADDRESS);
  Wire.write(IODIRA);   
  Wire.write(0xFF);    // A Register INPUT
  Wire.write(0x00);    // B Register OUTPUT
  Wire.endTransmission(); 
  
  Wire.beginTransmission(MCPADDRESS);
  Wire.write(GPPUA);  // PULL-UP resistors
  Wire.write(0xFF);   // A Register
  Wire.write(0xFF);   // B Register
  Wire.endTransmission(); 
 
}
 
void loop()
{
  uint8_t value;
  time1 = micros();
  Wire.beginTransmission(MCPADDRESS);
  Wire.write(GPIOB);      // B Register
  Wire.write(value);      // value to send - all HIGH

  //Wire.beginTransmission(MCPADDRESS);
  //Wire.write(GPIOA);        // A Register
  //Wire.endTransmission();   // Read Value
  //Wire.requestFrom(0x20,1); // 1 Byte
  
  while (!Wire.available()) {
     Serial.print("NO");}; // Wait until ready
    Wire.endTransmission(); 
  value=Wire.read(); // Read A Value
  value=00000111;
  
  time2 = micros();
  
  Serial.print("Read:");
  Serial.print(value);
  Serial.print(" - Time:");
  Serial.println(time2-time1);
  
  delay(500);
    

  
  delay(500);
  
}
