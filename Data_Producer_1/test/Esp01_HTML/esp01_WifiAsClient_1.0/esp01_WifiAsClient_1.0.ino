#include <ESP8266WiFi.h>

//parametros para conectarse a red
const char* ssid = "LowiC6D0";
const char* password = "NLS67B8CTL8SBY";

//parametros para ip fija
IPAddress ip(192,168,0,32);  
IPAddress gateway(192,168,1,1);   
IPAddress subnet(255,255,255,0);   


// Servidor web en el puerto 80 (por defecto para navegadores)
WiFiServer server(80);

void setup() {
// Inicializamos el puerto serie a 115200 baudios
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.print("Intentando conectar a ");
  Serial.println(ssid);
  
// Nos conectamos al wifi configurado
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);
 
 
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Conexion WiFi establecida");
   Serial.println(WiFi.localIP());
  
  // Iniciamos el servidor web
  server.begin();
  Serial.println("Por favor, espere a obtener la IP ");
  delay(5000);
  Serial.print("Servidor web online en la IP: ");
  Serial.println(WiFi.localIP());
}


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
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();
            // Creamos el html para enviar
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<head></head><body bgcolor='#3523E0'><h1>Edferoca</h1><h2>ESP8266 </h2><h4>Data"  "</h4>");
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
