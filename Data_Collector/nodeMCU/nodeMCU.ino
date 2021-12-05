
#include <ESP8266WiFi.h>
#include "uMQTTBroker.h"

uMQTTBroker myBroker;

char ssid[] = "wind_tutut";      // your network SSID (name)
char pass[] = "edferoca"; // your network password
int counter = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.println();

  WiFi.softAP(ssid, pass);
  Serial.println("AP started");
  Serial.println("IP address: " + WiFi.softAPIP().toString());

  // Start the broker
  Serial.println("Starting MQTT broker");
  myBroker.init();

  myBroker.subscribe("#");
}

void loop()
{
  myBroker.publish("broker/counter", (String)counter++);

  Serial.print("Clients:");
  Serial.println(myBroker.getClientCount());
  // wait a second
  delay(1000);
}
