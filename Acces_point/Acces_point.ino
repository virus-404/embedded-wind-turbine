#include <ESP8266WiFi.h>        // Include the Wi-Fi library

// Configuración de la WiFi generada
const char *ssid = "EDferocassssss";
const char *password = "wiiiii";

void setup() {
  Serial.begin(115200);
  delay(10);
  
  WiFi.mode(WIFI_AP);
  while(!WiFi.softAP(ssid, password))
  {
   Serial.println(".");
    delay(100);
  }
  
  Serial.print("Iniciado AP ");
  Serial.println(ssid);
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());
  
}

void loop() { }
