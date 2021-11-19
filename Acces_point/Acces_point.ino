#include <ESP8266WiFi.h>        // Include the Wi-Fi library
#define LEDpin D4   //set led pin

// Configuración de la WiFi generada
const char *ssid = "mqtt_broker";
const char *password = "wiiiii";

void setup() {
  Serial.begin(9600);
  delay(10);

  WiFi.mode(WIFI_AP);
  while (!WiFi.softAP(ssid, password))
  {
    Serial.println(".");
    delay(100);
  }
  pinMode(LEDpin, OUTPUT);

  Serial.print("Iniciado AP ");
  Serial.println(ssid);
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());
  
}

void loop() {
  digitalWrite(LEDpin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LEDpin, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
    
}
