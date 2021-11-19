#include <ESP8266WiFi.h>
#include "uMQTTBroker.h"
#include "Wire.h"

uMQTTBroker myBroker;

/*
 * Your WiFi config here
 */
char ssid[] = "edferoca";      // your network SSID (name)
char pass[] = "edferoca"; // your network password

int counter = 0;

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
  Serial.begin(9600); //9600bps //115200
  while (!Serial) {}; //Serial port initialization

  WiFi.softAP(ssid, pass);
  Serial.println("AP started");
  Serial.println("IP address: " + WiFi.softAPIP().toString());
  
  // Start the broker
  Serial.println("Starting MQTT broker");
  myBroker.init();

  myBroker.subscribe("#");
  

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
  
  myBroker.publish("broker/counter", (String)counter++);
  time1 = micros();
  

  Serial.print("Clients:");

  Serial.println(myBroker.getClientCount());
  // wait a second
  delay(1000);
  int clientes = myBroker.getClientCount();
  uint8_t value;
    Serial.print(value);
  Serial.print(clientes);
  switch(clientes) //donde opción es la variable a comparar
 {
    case 1: //Bloque de instrucciones 1;
    value = 00000001;
    break;
    case 2: //Bloque de instrucciones 2;
    value = 00000011;
    break;
    case 3: //Bloque de instrucciones 3;
    value = 00000111;
    break;
    case 4: //Bloque de instrucciones 1;
    value = 00001111;
    break;
    case 5: //Bloque de instrucciones 2;
    value = 00011111;
    break;
    case 6: //Bloque de instrucciones 3;
    value = 00111111;
    break;
    case 7: //Bloque de instrucciones 2;
    value = 01111111;
    break;
    case 8: //Bloque de instrucciones 3;
    value = 11111111;
    break;
    //Nótese que valor 1 2 y 3 son los valores que puede tomar la opción
    //la instrucción break es necesaria, para no ejecutar todos los casos.
    default: //Bloque de instrucciones por defecto;
    break;
    //default, es el bloque que se ejecuta en caso de que no se de ningún caso
  }
 


  time2 = micros();
  
  delay(500);
    
  Wire.beginTransmission(MCPADDRESS);
  Wire.write(GPIOB);      // B Register
  Wire.write(value);      // value to send - all HIGH
  Wire.endTransmission(); 
  
  delay(500);




}
