#include <SoftwareSerial.h>
#include "SerialLCDesp01.h"

SoftwareSerial softSerial(2, 3); // RX, TX
LCD LCD;

void setup() {
  Serial.begin(115200);
  softSerial.begin(115200);
  LCD.setHome();//set the cursor back to 0,0.
  LCD.clearScreen();//clear anything that may have been previously printed ot the screen.
  delay(10);
  
  LCD.printStr("Commence Arduino Demo Mode");
  delay(1500);

  
}
void loop() {
  LCD.clearScreen();
  LCD.printStr("te amo aleja");
  delay(2000);
  LCD.clearScreen();
  
  
}  

void clearScreen()
{
  //clears the screen, you will use this a lot!
  Serial.write(0x7C);
  Serial.write((byte)0); //CTRL @
  //can't send LCD.write(0) or LCD.write(0x00) because it's interprestted as a NULL
}
