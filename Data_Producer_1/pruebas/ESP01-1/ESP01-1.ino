#include <DHT.h>
#include <DHT_U.h>
#include <ESP8266WiFi.h>


// Si vas a usar un sensor del tipo DHT distinto al 11, descomenta la linea de tu sensor
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// Replace with your network details
const char* ssid = "LowiC6D0";
const char* password = "NLS67B8CTL8SBY";

// Servidor web en el puerto 80 (por defecto para navegadores)
WiFiServer server(80);

// Pin del sensor DHT, en mi caso GPI02
const int DHTPin = 2;
// Inicialización
DHT dht(DHTPin, DHTTYPE);

// Variables temporales de las lecturas
static char celsiusTemp[7];
static char humidityTemp[7];

// Recordamos que setup() solo se ejecuta el primer ciclo, y es util para configurar puertos y comunicaciones
void setup() {
  // Inicializamos el puerto serie a 115200 baudios
  Serial.begin(115200);
  delay(10);

  dht.begin();
  
  Serial.println();
  Serial.print("Intentando conectar a ");
  Serial.println(ssid);

  // Nos conectamos al wifi configurado
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conexion WiFi establecida");
  
  // Iniciamos el servidor web
  server.begin();
  Serial.println("Por favor, espere a obtener la IP ");
  delay(5000);
  Serial.print("Servidor web online en la IP: ");
  Serial.println(WiFi.localIP());
}

// Recoradmos que loop() se ejecuta ciclicamente
void loop() {
  // Esperamos nuevo cliente
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("Nuevo cliente");
    boolean blank_line = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n' && blank_line) {
            // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
            float h = dht.readHumidity();
            // Read temperature as Celsius (the default)
            float t = dht.readTemperature();
            // Check if any reads failed and exit early (to try again).
            if (isnan(h) || isnan(t)) {
              Serial.println("Error al leer del sensor DHT!");
              strcpy(celsiusTemp,"Failed");
              strcpy(humidityTemp, "Failed");         
            }
            else{
                  // Computes temperature values in Celsius + Fahrenheit and Humidity
                  float hic = dht.computeHeatIndex(t, h, false);       
                  dtostrf(hic, 6, 2, celsiusTemp);             
                  dtostrf(h, 6, 2, humidityTemp);
                }
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
    Serial.println("Cliente desconectado.");
  }
}   
