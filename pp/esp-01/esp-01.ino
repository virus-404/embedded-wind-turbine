#include "wifi_config.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.


WiFiClient espClient;
PubSubClient client(espClient);
WiFiServer server(80);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;



void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  WifiInitSTA();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  //client.connect(clientID,clientUserName,clientPassword);
  //client.subscribe("broker/counter#");
  client.subscribe("broker/WT1/#");
}

void loop() {
   //intento de conectarce a red Wifi
  if (!client.connected()) {
  reconnect();
  }

  client.loop();
  
  //Serial.println("A");
}


//**********************************************
//**********Funciones Adicionales***************
//**********************************************

void WifiInitSTA() {
  // Nos conectamos al wifi configurado
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  delay(100);

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    //delay(250);
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    //Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "DataProducer_1";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.print("connected");
      delay(3000);
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("broker/WT1/#");
    } else {
      /*
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      */
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
