



#include <SparkFunSerialGraphicLCD.h>//inculde the Serial Graphic LCD library
#include <SoftwareSerial.h>

#define maxX 127//159 
#define maxY 63 //127

LCD LCD;

void setup()
{
//we're just going to run through a bunch of demos to show the functionality of the LCD.

delay(1200);///wait for the one second spalsh screen before anything is sent to the LCD.

LCD.setHome();//set the cursor back to 0,0.
LCD.clearScreen();//clear anything that may have been previously printed ot the screen.
delay(10);
  
LCD.printStr("Commence Arduino Demo Mode");
delay(100);
LCD.clearScreen();

//Each of these functions is explained in great detail below. 

}
//-------------------------------------------------------------------------------------------
void loop()
{

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
delay(5000);
LCD.clearScreen();

}
void SetPixelSimetrico(int x,int y){
int simetriaX=(30-x)*2;
LCD.setPixel(x,y,1);
LCD.setPixel(x+simetriaX,y,1);
}

//-------------------------------------------------------------------------------------------
void reverseModeDemo()
{
//Each LCD has a reverse mode built into it. The toggleReverseMode() function swaps the colors of the background and the pixels.
//For example, on the large display, the text is usually white on a blue background, but you could swap that to blue text on a white background. 
//This setting is stored and will remian even after power has been disconnected. 
  
LCD.setHome();
LCD.clearScreen();
LCD.printStr("Toggle reverse mode");
delay(2000);
  
LCD.clearScreen();
LCD.toggleReverseMode();
LCD.printStr("Reverse Mode On");
delay(1000);

LCD.clearScreen();
LCD.toggleReverseMode();
LCD.printStr("Reverse Mode Off");
delay(1000);
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
void XYDemo()
{
//This function shows off the setX() and setY() functions. These two functions set the position of the cursor.
//That cursor sets where text will be printed.
//The parameters are simply the x and y value you want with each respective function. 

//Characters are 8 pixels tall x 6 pixels wide
//The top left corner of a char is where the x/y value will start its print
//For example, if you print a char at position 1,1, the bottom right of your char will be at position 7,9.
//Therefore, to print a character in the very bottom right corner, you would need to print at the coordinates 
//x = 154 , y = 120. You should never exceed these values. ***NOTE*** - these values are for the larger size LCD. 

//Here we have an example using an upper case 'B'. The star is where the character starts, given a set 
//of x,y coordinates. # represents the blocks that make up the character, and _ represnets the remaining 
//unused pixels in the character space. 
//    *###__
//    #   #_
//    #   #_
//    ####__
//    #   #_
//    #   #_
//    ####__
//    ______

  LCD.setHome();
  LCD.clearScreen();
  LCD.printStr("Change X and Y coordinates");
  delay(3000);
  
  LCD.clearScreen();
  LCD.setX((maxX/2)-9);//these are calculated by dividing maxX by 2, then subtracting (half of the number of chars in the word times 6).
  LCD.setY(0);
  LCD.printStr("Top");
  delay(1000);
  
  LCD.setX((maxX/2)-18);
  LCD.setY((maxY/2)-4);
  LCD.printStr("Middle");
  delay(1000);
  
  LCD.setX((maxX/2)-18);
  LCD.setY(maxY - 7);
  LCD.printStr("Bottom");
  delay(1000);
  
  LCD.setX(0);
  LCD.setY((maxY/2)-4);
  LCD.printStr("Left");
  delay(1000);
  
  LCD.setX(maxX - 30);
  LCD.setY((maxY/2)-4);
  LCD.printStr("Right");
  delay(1000);
  
  LCD.setX(maxX - 5);
  LCD.setY(maxY - 7);
  LCD.printStr("B");
  delay(1000);
  
  //Print # signs around the screen
  LCD.clearScreen();
  
  LCD.setY(0);
  for(int i=0;i<=(maxX - 5);i+=6)
  {
  LCD.setX(char(i));
  LCD.printStr("#");
  delay(10);
  }
  
  LCD.setY(maxY - 7);
  for(int i=0;i<=(maxX - 5);i+=6)
  {
  LCD.setX(char(i));
  LCD.printStr("#");
  delay(10);
  }
  
  LCD.setX(maxX - 5);
  for(int i=0;i<=(maxY - 7);i+=8)
  {
  LCD.setY(char(i));
  LCD.printStr("#");
  delay(10);
  }
  
  LCD.setX(0);
  for(int i=0;i<=(maxY - 7);i+=8)
  {
  LCD.setX(0);
  LCD.setY(char(i));
  LCD.printStr("#");
  delay(10);
  }
  delay(2000);
  
}
//-------------------------------------------------------------------------------------------
void pixelDemo()
{
//This function shows the setPixel() function. Any individual pixel on the LCD can be set or reset.
//Set means it's the color of the text depending on the reverse mode setting.
//Reset means it's the color of the background.
//The parameters for this function are (x, y, set) where x and y are the coordinates of the pixel you want to set or reset

  LCD.clearScreen();
  LCD.setHome();
  LCD.printStr("Control each pixel");
  delay(2000);

  LCD.clearScreen();

  //draw a box around the screen
  for(int i = 0; i <= maxX; i ++)
  {
    LCD.setPixel(i,0,1);
  }

  for(int i = 0; i <= maxY; i ++)
  {
    LCD.setPixel(maxX,i,1);
  }
  
    for(int i = maxX; i >= 0; i --)
  {
    LCD.setPixel(i,maxY,1);
  }
  
    for(int i = maxY; i >= 0; i --)
  {
    LCD.setPixel(0,i,1);
  }
  
  //draw vertical lines
  for(int i = 0, j = 0; i <= maxY; i++, j++)
  {
      LCD.setPixel(i,j,1);
  }
  
  for(int i = 0, j = maxY; i <= maxY; i++, j--)
  {
      LCD.setPixel(i,j,1);
  }
  
  for(int i = maxX, j = maxY; i >= 0; i--, j--)
  {
      LCD.setPixel(i,j,1);
  }
  
  for(int i = maxX, j = 0; i >= 0; i--, j++)
  {
      LCD.setPixel(i,j,1);
  }
  
  //draw a small box in the center
  LCD.setPixel((maxX/2),(maxY/2),1);
  LCD.setPixel(((maxX/2)+1),(maxY/2),1);
  LCD.setPixel((maxX/2),((maxY/2)+1),1);
  LCD.setPixel(((maxX/2)+1),((maxY/2)+1),1);
  delay(1000);
  

}
//-------------------------------------------------------------------------------------------
void lineDemo()
{
//This function demonstartes the drawLine() function. The parameters are (x1, y1, x2, y2, set).
//Lines can be drawn from any point to any other point within the boundaries of the LCD. 
  LCD.clearScreen();
  LCD.printStr("You can also draw lines");
  delay(1500);
  LCD.clearScreen();
  //draw x
  LCD.drawLine(0,0,maxX,maxY,1);//draw line from top left to bottom right
  delay(500);
  LCD.drawLine(0,maxY,maxX,0,1);//draw line from top left to bottom right
  delay(500);
  
  //draw box
  LCD.drawLine(0,0,maxX,0,1);//draw line from top left to top right
  delay(500);
  LCD.drawLine(0,maxY,maxX,maxY,1);//draw line from bottom left to bottom right
  delay(500);
  LCD.drawLine(0,0,0,maxY,1);//draw line from top left to bottom left
  delay(500);
  LCD.drawLine(maxX,0,maxX,maxY,1);//draw line from top right to bottom right
  delay(3000);

}
//-------------------------------------------------------------------------------------------
void boxDemo()
{
//This function demonstartes the drawBox() function. The parameters are (x1, y1, x2, y2, set).
  LCD.clearScreen();
  LCD.printStr("Or, just draw a box");
  delay(1500);
  LCD.clearScreen();

  LCD.drawBox(0,0,maxX,maxY,1);//draw box around entire display
  delay(1000);
  
  LCD.drawBox(10,10,(maxX - 10),(maxY - 10),1);//draw box around entire display
  delay(1000);

  LCD.drawBox(20,20,(maxX - 20),(maxY - 20),1);//draw box around entire display
  delay(1000);
  
  LCD.drawBox(30,30,(maxX - 30),(maxY - 30),1);//draw box around entire display
  delay(3000);
}
//-------------------------------------------------------------------------------------------
void circleDemo()
{
//This function demonstartes the drawCircle() function. The parameters are (x1, y1, radius, set).
  
  LCD.clearScreen();
  LCD.printStr("Circles are just as easy");
  delay(1500);
  LCD.clearScreen();
  
  LCD.drawCircle(5,(maxY/2),5,1);//draw box around entire display
  delay(500);
  LCD.drawCircle(15,(maxY/2),10,1);//draw box around entire display
  delay(500);
  LCD.drawCircle(30,(maxY/2),15,1);//draw box around entire display
  delay(500);
  LCD.drawCircle(50,(maxY/2),20,1);//draw box around entire display
  delay(500);
  LCD.drawCircle(75,(maxY/2),25,1);//draw box around entire display
  delay(500);
  LCD.drawCircle(105,(maxY/2),30,1);//draw box around entire display
  delay(500);
  LCD.drawCircle(140,(maxY/2),35,1);//draw box around entire display
  delay(3000);
}
//-------------------------------------------------------------------------------------------
void eraseDemo()
{
//This function demonstartes the eraseBlock() function. The parameters are (x1, y1, x2, y2).
  LCD.setHome();
  LCD.eraseBlock(0,0,maxX,16);//draw box around entire display
  delay(500);
  
  LCD.printStr("Last, earse part of the screen");
  delay(1000);
  
  
  LCD.eraseBlock(20,20,(maxX - 20),(maxY - 20));//draw box around entire display
  delay(500);
  
  LCD.drawBox(20,20,(maxX - 20),(maxY - 20),1);//draw box around entire display
  delay(1000);
  
  LCD.setX((maxX/2)-9);
  LCD.setY((maxY/2)-9);
  
  LCD.printStr("THE");
  
  LCD.setX((maxX/2)-9);
  LCD.setY((maxY/2)+2);
  
  LCD.printStr("END");
  delay(500);
  
  LCD.eraseBlock(21,21,(maxX - 21),(maxY - 21));//draw box around entire display
  delay(1000);
  
  LCD.setX((maxX/2)-6);
  LCD.setY((maxY/2)-9);
  
  LCD.printStr("OR,");
  
  LCD.setX((maxX/2)-18);
  LCD.setY((maxY/2)+2);
  
  LCD.printStr("IS IT?");
  delay(1000);
  
  
}
//-------------------------------------------------------------------------------------------
void helloWorld()
{
//Prints Hello World to the screen and draws a tiny world (circle)  
  
LCD.setHome();
LCD.clearScreen();
delay(10);

  LCD.setX((maxX/2)-15);
  LCD.setY(0);
  LCD.printStr("Hello");
  delay(250);
  
  
  LCD.setX((maxX/2)-15);
  LCD.setY(maxY - 7);
  LCD.printStr("World");
  delay(500);

  if(maxX == 159)
  {
   LCD.drawCircle((maxX/2),(maxY/2),40,1);
   delay(1000);
  }
  else
  {
   LCD.drawCircle((maxX/2),(maxY/2),20,1);
   delay(1000);
  }
}
//-------------------------------------------------------------------------------------------
void demoDemo()
{
//There is an internal demo feature built into the LCD firmware. Tjis function uses the demo() function to start that demo. 
//NOTE: Once the demo is initiated, there is no stopping it until it finishes or until power is disconnected from the LCD.
LCD.setHome();
LCD.clearScreen();
delay(10);

LCD.demo();
}
