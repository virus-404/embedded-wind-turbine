#include <ESP8266WiFi.h>
#include "uMQTTBroker.h"
#include "mcp23017.h"
#include "wifi_config.h"
#include "wifi_utils.hpp"
#include "Wire.h"
#include "MCP23017_config.hpp"


uMQTTBroker myBroker;

int counter = 0;




uint16_t time1, time2;

void setup()
{
  Serial.begin(9600); //9600bps //115200
  while (!Serial) {}; //Serial port initialization

  wifi_create();

  // Start the broker
  Serial.println("Starting MQTT broker");
  myBroker.init();
  myBroker.subscribe("#");

	// I2C prepare
  Wire.setClock(WIRE_SPEED); // I2C Bus speed
  Wire.begin();     // wake up I2C bus
	mcpConfig_Breg();
}

void loop()
{

  myBroker.publish("broker/counter", (String)counter++);


  delay(1000);
  int clientes = myBroker.getClientCount();
  uint8_t value;

  switch(clientes) //donde opción es la variable a comparar
 {
    case 0: //Bloque de instrucciones 1;
    value = 00000000;
    break;
    case 1: //Bloque de instrucciones 1;
    value = 0x01;
    break;
    case 2: //Bloque de instrucciones 2;
    value = 0x03;
    break;
    case 3: //Bloque de instrucciones 3;
    value = 0x07;
    break;
    case 4: //Bloque de instrucciones 1;
    value = 0x0F;
    break;
    case 5: //Bloque de instrucciones 2;
    value = 0x1F;
    break;
    case 6: //Bloque de instrucciones 3;
    value = 0x3F;
    break;
    case 7: //Bloque de instrucciones 2;
    value = 0x7F;
    break;
    case 8: //Bloque de instrucciones 3;
    value = 0x0FF;
    break;
    default: //Bloque de instrucciones por defecto;
    break;
    //default, es el bloque que se ejecuta en caso de que no se de ningún caso
  }

	// serial verification
	Serial.print("Clients:");
	Serial.println(clientes);
	Serial.println(value);
  delay(500);

	//sen data to mcp23017
  Wire.beginTransmission(MCPADDRESS);
  Wire.write(GPIOB);      // B Register
  Wire.write(value);      // value to send - all HIGH
  Wire.endTransmission();

  delay(500);




}
