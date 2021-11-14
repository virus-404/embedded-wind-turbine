#include <DHT.h>
#include <DHT_U.h>
#include <ESP8266WiFi.h>
#include "SerialLCDesp01.h"

//***************Variables*************
#define DHTTYPE DHT11   // DHT 11
// Replace with your network details
const char* ssid ="LowiC6D0";//"edferocaPoco"; "LowiC6D0";
const char* password ="NLS67B8CTL8SBY";//"edferoca"; "NLS67B8CTL8SBY";
// Variables temporales de las lecturas
static char celsiusTemp[7];
static char humidityTemp[7];
// Servidor web en el puerto 80 (por defecto para navegadores)
WiFiServer server(80);
//  Inicialización yPin del sensor DHT, en mi caso GPI02
const int DHTPin = 2;
DHT dht(DHTPin, DHTTYPE);
//inicializo LCD
LCD LCD;

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
  //**********Server HTLM
  server.begin();
  // mostrar en pantalla a dodne se conecto
  DecoWifi();
}

// Recoradmos que loop() se ejecuta ciclicamente
void loop() {
  //**********DHT11
  DHT11Medidas();
  //**********Datos por HTML
  HtmlData();
  //*********precentar en LCD
  LCDShow();
  
}

//**********************************************
//**********Funciones Adicionales***************
//**********************************************

void WifiInitSTA(){
    // Nos conectamos al wifi configurado
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    LCD.printStr(".");
  }
  delay(100);
}
void DecoWifi(){
  LCD.printStr("Servidor web online ");
  LCD.setY(55);
  LCD.setX(0);
  LCD.printStr("en la IP: ");
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

void LCDShow(){
  LCD.clearScreen();
  LCD.setY(55);
  LCD.setX(0);
  Serial.print("T: ");
  Serial.print(celsiusTemp);
  LCD.setY(20);
  LCD.setX(0);
  LCD.printStr("H: ");
  Serial.print(humidityTemp);
  delay(3000);
  }

void HtmlData(){
  // Esperamos nuevo cliente
  WiFiClient client = server.available();

  if (client) {
    boolean blank_line = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n' && blank_line) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            // Creamos el html para enviar
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<head></head><body bgcolor='#3523E0'><h1>Edferoca</h1><h2>ESP8266 - Humedad y temperatura</h2><h4>Temperature in Celsius: ");
            client.println(celsiusTemp);
            client.println("*C</h4><h4>Humidity: ");
            client.println(humidityTemp);
            client.println("%</h4><h4>");
            client.println("</body></html>");
            break;
        }
        if (c == '\n') {
          // when starts reading a new line
          blank_line = true;
        }
        else if (c != '\r') {
          // when finds a character on the current line
          blank_line = false;
        }
      }
    }
    // Cerrando conexión con el cliente
    delay(1);
    client.stop();
  }
  }
