#include <DHT.h>
#include <DHT_U.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "SerialLCDesp01.h"
#include "config.h"
#include "LCD_funct.hpp"

//***************Variables*************
#define DHTTYPE DHT11   // DHT 11
// variables de red wifi
const char* ssid ="wind_tutut";
const char* password ="edferoca";
const char* mqtt_server = "192.168.4.1";
WiFiClient espClient;
PubSubClient client(espClient);
WiFiServer server(80);

//  Inicialización y Pin del sensor DHT, en mi caso GPI02
const int DHTPin = 2;
DHT dht(DHTPin, DHTTYPE);
//inicializo LCD


//*****************SETUP**************
void setup() {
  //**********Puerto Serie
  //115200 baudios
  Serial.begin(115200);
  delay(10);
  //**********LCD
  // ubicamos en 0,0 y limpiamos pantalla
  LCD.setHome();
  LCD.clearScreen();
  delay(10);
  //**********DHT11
  // Inicializamos
  dht.begin();
  //**********WIFI
  WifiInitSTA();
	//**********MQTT server
	client.setServer(mqtt_server, 1883);
	client.setCallback(callback);
  // mostrar en pantalla a dodne se conecto
  DecoWifi();
}

// Recoradmos que loop() se ejecuta ciclicamente
void loop() {
  //intento de conectarce a red Wifi
	if (!client.connected()) {
	reconnect();
	}
	client.loop();
  
  //**********DHT11
  DHT11Medidas();
  //**********publicacion en MQTT
	client.publish("broker/WT1/DP1/Humedad", humidityTemp);
  client.publish("broker/WT1/DP1/temperatura", celsiusTemp);
  // mostrar en pantalla LCD
  delay(2000);
  LCD.clearScreen();
  //*********precentar en LCD
  LCD_Dibujos();
  LCDShow();
  delay(5000);
  LCD.clearScreen();
  delay(2000);
  

}

//**********************************************
//**********Funciones Adicionales***************
//**********************************************

void WifiInitSTA(){
    // Nos conectamos al wifi configurado
	WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    LCD.printStr(".");
  }
  delay(100);
  LCD.clearScreen();
}

void DecoWifi(){
  LCD.printStr("WiFi connected");
  LCD.setY(55);
  LCD.setX(0);
  LCD.printStr("on IP address: ");
  LCD.setY(47);
  LCD.setX(0);
  Serial.print(WiFi.localIP());
  delay(10000);
  LCD.clearScreen();
}

void DHT11Medidas(){
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    strcpy(celsiusTemp,"Failed");
    strcpy(humidityTemp, "Failed");
  }
  else{
        // Computes temperature values in Celsius + Fahrenheit and Humidity
        float hic = dht.computeHeatIndex(t, h, false);
        dtostrf(hic, 6, 2, celsiusTemp);
        dtostrf(h, 6, 2, humidityTemp);
      }
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
		LCD.printStr("Attempting MQTT connection...");
		// Create a random client ID
		String clientId = "DataProducer_1";
		clientId += String(random(0xffff), HEX);
		// Attempt to connect
    if (client.connect(clientId.c_str())) {
			LCD.setY(55);
			LCD.setX(0);
      LCD.printStr("connected");
			delay(3000);
			LCD.clearScreen();
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
