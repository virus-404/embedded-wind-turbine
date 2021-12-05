#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// Gnd      -  GND
// 3.3v     -  VCC
// 3.3v     -  CS
// Analog 4 -  SDA
// Analog 5 -  SLC

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//WIFI
const char* ssid ="wind_tutut";//"edferocaPoco"; "LowiC6D0";
const char* password ="edferoca";//"edferoca"; "NLS67B8CTL8SBY";
const char* mqtt_server = "192.168.4.1";
WiFiClient espClient;
PubSubClient client(espClient);
WiFiServer server(80);


// ***** ADXL345
//Direccion del dispositivo
const int DEVICE_ADDRESS = (0x53);  
byte _buff[6];
//Direcciones de los registros del ADXL345
char POWER_CTL = 0x2D;
char DATA_FORMAT = 0x31;
char DATAX0 = 0x32;   //X-Axis Data 0
char DATAX1 = 0x33;   //X-Axis Data 1
char DATAY0 = 0x34;   //Y-Axis Data 0
char DATAY1 = 0x35;   //Y-Axis Data 1
char DATAZ0 = 0x36;   //Z-Axis Data 0
char DATAZ1 = 0x37;   //Z-Axis Data 1

//****LCD
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  Serial.begin(115200);
  Serial.print("Iniciado");

   
  //**********WIFI
  WifiInitSTA();
  //**********MQTT server
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
  Wire.begin(0,2);
  writeTo(DEVICE_ADDRESS, DATA_FORMAT, 0x01); //Poner ADXL345 en +- 4G
  writeTo(DEVICE_ADDRESS, POWER_CTL, 0x08);  //Poner el ADXL345 

  lcd.begin(0, 2);                   // Initialize I2C LCD module (SDA = GPIO0, SCL = GPIO2)
 
  lcd.backlight();                   // Turn backlight ON
 
  lcd.setCursor(0, 0);               // Go to column 0, row 0
  lcd.print("ESP-01 I2C LCD");
}
byte i = 0;
char text[4];

void loop()
{
  if (!client.connected()) {
  reconnect();
  }
  client.loop();
  
  readAccel(); //Leer aceleracion x, y, z
  delay(500);

  delay(500);
  lcd.clear();
}

void readAccel() {
  //Leer los datos
  uint8_t numBytesToRead = 6;
  readFrom(DEVICE_ADDRESS, DATAX0, numBytesToRead, _buff);

  //Leer los valores del registro y convertir a int (Cada eje tiene 10 bits, en 2 Bytes LSB)
  int x = (((int)_buff[1]) << 8) | _buff[0];   
  int y = (((int)_buff[3]) << 8) | _buff[2];
  int z = (((int)_buff[5]) << 8) | _buff[4];
  int num = 1234;
  char cstrX[16];
  itoa(x, cstrX, 10);
  char cstrY[16];
  itoa(y, cstrY, 10);
  char cstrZ[16];
  itoa(z, cstrZ, 10);
  client.publish("broker/DP2/acelerometro/x", cstrX);
  client.publish("broker/DP2/acelerometro/y", cstrY);
  client.publish("broker/DP2/acelerometro/z", cstrZ);
  lcd.setCursor(0, 1);               
  lcd.print("x");
  lcd.setCursor(3, 1);               
  lcd.print(x);
  Serial.print("x: ");
  Serial.print( x );
  Serial.print(" y: ");
  Serial.print( y );
  Serial.print(" z: ");
  Serial.println( z );
}

//Funcion auxiliar de escritura
void writeTo(int device, byte address, byte val) {
  Wire.beginTransmission(device);
  Wire.write(address);
  Wire.write(val);
  Wire.endTransmission(); 
}

//Funcion auxiliar de lectura
void readFrom(int device, byte address, int num, byte _buff[]) {
  Wire.beginTransmission(device);
  Wire.write(address);
  Wire.endTransmission();

  Wire.beginTransmission(device);
  Wire.requestFrom(device, num);

  int i = 0;
  while(Wire.available())
  { 
    _buff[i] = Wire.read();
    i++;
  }
  Wire.endTransmission();
}

void WifiInitSTA(){
    // Nos conectamos al wifi configurado
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  delay(100);
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
    Serial.println("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "DataProducer_1";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      delay(3000);
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
