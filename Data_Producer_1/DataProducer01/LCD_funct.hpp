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


void SetPixelSimetrico(int x,int y){
int simetriaX=(30-x)*2;
LCD.setPixel(x,y,1);
LCD.setPixel(x+simetriaX,y,1);
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
