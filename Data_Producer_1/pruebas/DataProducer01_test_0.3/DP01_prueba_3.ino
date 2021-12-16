#include <DHT.h>
#include <DHT_U.h>
#include <ESP8266WiFi.h>
#include "SerialLCDesp01.h"
#include "config.h"

//***************Variables*************
#define DHTTYPE DHT11   // DHT 11
// Servidor web en el puerto 80 (por defecto para navegadores)
WiFiServer server(80);
//  Inicialización yPin del sensor DHT, en mi caso GPI02
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
  LCD_Dibujos();
  LCDShow();
  delay(5000);

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
  LCD.clearScreen();
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
  LCD.setY(47);
  LCD.setX(40);
  Serial.print(celsiusTemp);
  Serial.print("C");
  LCD.setY(14);
  LCD.setX(40);
  Serial.print(humidityTemp);
  LCD.printStr("%");
  }

void LCD_Dibujos(){
//***********termometro******
LCD.drawLine(33,56,36,56, 1);
LCD.drawLine(33,50,36,50, 1);
LCD.setPixel(31,61,1);
LCD.setPixel(30,62,1);
LCD.setPixel(29,61,1);
LCD.drawLine( 28,43,28,60, 1);
LCD.drawLine( 32,43,32,60, 1);
LCD.setPixel(33,42,1);
LCD.setPixel(34,41,1);
LCD.setPixel(35,40,1);
LCD.drawLine(36,35,36,39, 1);
LCD.setPixel(35,34,1);
LCD.setPixel(34,33,1);
LCD.setPixel(33,32,1);
LCD.drawLine(28,31,32,31, 1);
LCD.setPixel(27,32,1);
LCD.setPixel(26,33,1);
LCD.setPixel(25,34,1);
LCD.drawLine(24,35,24,39, 1);
LCD.setPixel(25,40,1);
LCD.setPixel(26,41,1);
LCD.setPixel(27,42,1);
//interior
LCD.drawLine(30,40,30,53, 1);
LCD.drawLine(29,41,31,41, 1);
LCD.drawLine(28,40,32,40, 1);
LCD.drawLine(27,39,33,39, 1);
LCD.drawLine(26,38,34,38, 1);
LCD.drawLine(26,37,34,37, 1);
LCD.drawLine(26,36,34,36, 1);
LCD.drawLine(27,35,33,35, 1);
LCD.drawLine(28,34,32,34, 1);
LCD.drawLine(29,33,31,33, 1);

//*****************humedad*******
LCD.setPixel(30,29,1);
SetPixelSimetrico(29,28);
SetPixelSimetrico(29,27);
SetPixelSimetrico(28,26);
SetPixelSimetrico(28,25);
SetPixelSimetrico(27,24);
SetPixelSimetrico(27,23);
SetPixelSimetrico(26,22);
SetPixelSimetrico(26,21);
SetPixelSimetrico(25,20);
SetPixelSimetrico(25,19);
SetPixelSimetrico(24,18);
SetPixelSimetrico(24,17);
SetPixelSimetrico(24,16);
SetPixelSimetrico(23,15);
SetPixelSimetrico(23,14);
SetPixelSimetrico(23,13);
SetPixelSimetrico(22,12);
SetPixelSimetrico(22,11);
SetPixelSimetrico(22,10);
SetPixelSimetrico(22,9);
SetPixelSimetrico(22,8);
SetPixelSimetrico(23,7);
SetPixelSimetrico(23,6);
SetPixelSimetrico(24,5);
SetPixelSimetrico(24,4);
SetPixelSimetrico(25,3);
SetPixelSimetrico(26,2);
SetPixelSimetrico(27,1);
SetPixelSimetrico(28,0);
SetPixelSimetrico(29,0);
LCD.setPixel(30,0,1);
LCD.setY(14);
LCD.setX(28);
LCD.printStr("%");
}

void SetPixelSimetrico(int x,int y){
int simetriaX=(30-x)*2;
LCD.setPixel(x,y,1);
LCD.setPixel(x+simetriaX,y,1);
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
