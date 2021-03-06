/**********************************************
Graphic Serial LCD Libary Main File
Joel Bartlett
SparkFun Electronics
9-25-13

**********************************************/
#include "Arduino.h"
#include "SerialLCDesp01.h"
#include "SoftwareSerial.h"

//initialize an instance of the SoftwareSerial library
//SoftwareSerial serial(2,3);//change these two pin values to whichever pins you wish to use (RX, TX)

LCD::LCD()
{
	Serial.begin(115200);

}
//-------------------------------------------------------------------------------------------
void LCD::printStr(char Str[78])//26 characters is the length of one line on the LCD
{
	Serial.print(Str);
	//if you need to print longer strings, change the size of this array here and in the .h file
}
//-------------------------------------------------------------------------------------------
void LCD::printNum(int num)//can't convert ints to strings so this is just for printing ints
{
	Serial.print(num);
}
//-------------------------------------------------------------------------------------------
void LCD::nextLine()//prints new line
{
	Serial.println();
}
//-------------------------------------------------------------------------------------------
void LCD::clearScreen()
{
  //clears the screen, you will use this a lot!
  Serial.write(0x7C);
  Serial.write((byte)0); //CTRL @
  //can't send LCD.write(0) or LCD.write(0x00) because it's interprestted as a NULL
}
//-------------------------------------------------------------------------------------------
void LCD::toggleReverseMode()
{
  //Everything that was black is now white and vise versa
  Serial.write(0x7C);
  Serial.write(0x12); //CTRL r
}
//-------------------------------------------------------------------------------------------
void LCD::toggleSplash()
{
  //turns the splash screen on and off, the 1 second delay at startup stays either way.
  Serial.write(0x7C);
  Serial.write(0x13); //CTRL s
}
//-------------------------------------------------------------------------------------------
void LCD::setBacklight(byte duty)
{
  //changes the back light intensity, range is 0-100.
  Serial.write(0x7C);
  Serial.write(0x02); //CTRL b
  Serial.write(duty); //send a value of 0 - 100
}
//-------------------------------------------------------------------------------------------
void LCD::setBaud(byte baud)
{
  //changes the baud rate.
  Serial.write(0x7C);
  Serial.write(0x07); //CTRL g
  Serial.write(baud); //send a value of 49 - 54
  delay(100);

/*
???1??? = 4800bps - 0x31 = 49
???2??? = 9600bps - 0x32 = 50
???3??? = 19,200bps - 0x33 = 51
???4??? = 38,400bps - 0x34 = 52
???5??? = 57,600bps - 0x35 = 53
???6??? = 115,200bps - 0x36 = 54
*/

  //these statements change the SoftwareSerial baud rate to match the baud rate of the LCD.
  if(baud == 49)
  {
	Serial.end();
	Serial.begin(4800);
  }
  if(baud == 50)
  {
	Serial.end();
	Serial.begin(9600);
  }
  if(baud == 51)
  {
	Serial.end();
	Serial.begin(19200);
  }
  if(baud == 52)
  {
	Serial.end();
	Serial.begin(38400);
  }
  if(baud == 53)
  {
	Serial.end();
	Serial.begin(57600);
  }
  if(baud == 54)
  {
	Serial.end();
	Serial.begin(115200);
  }
}
//-------------------------------------------------------------------------------------------
void LCD::restoreDefaultBaud()
{
//This function is used to restore the default baud rate in case you change it
//and forget to which rate it was changed.


Serial.end();//end the transmission at whatever the current baud rate is

//cycle through every other possible buad rate and attemp to change the rate back to 115200
Serial.begin(4800);
Serial.write(0x7C);
Serial.write(0x07);
Serial.write(54);//set back to 115200
Serial.end();

Serial.begin(9600);
Serial.write(0x7C);
Serial.write(0x07);
Serial.write(54);//set back to 115200
Serial.end();

Serial.begin(19200);
Serial.write(0x7C);
Serial.write(0x07);
Serial.write(54);//set back to 115200
Serial.end();

Serial.begin(38400);
Serial.write(0x7C);
Serial.write(0x07);
Serial.write(54);//set back to 115200
Serial.end();

Serial.begin(57600);
Serial.write(0x7C);
Serial.write(0x07);
Serial.write(54);//set back to 115200
Serial.end();

Serial.begin(115200);
delay(10);
Serial.write(0x7C);
Serial.write((byte)0); //clearScreen
Serial.print("Baud restored to 115200!");
delay(5000);

}
//-------------------------------------------------------------------------------------------
void LCD::demo()
{
  //Demonstartes all the capabilities of the LCD
  Serial.write(0x7C);
  Serial.write(0x04);//CTRL d
}
//-------------------------------------------------------------------------------------------
void LCD::setX(byte posX) //0-127 or 0-159 pixels
{
  //Set the X position
  Serial.write(0x7C);
  Serial.write(0x18);//CTRL x
  Serial.write(posX);

//characters are 8 pixels tall x 6 pixels wide
//The top left corner of a char is where the x/y value will start its print
//For example, if you print a char at position 1,1, the bottom right of your char will be at position 7,9.
//Therefore, to print a character in the very bottom right corner, you would need to print at the coordinates
//x = 154 , y = 120. You should never exceed these values.


// Here we have an example using an upper case 'B'. The star is where the character starts, given a set
//of x,y coordinates. # represents the blocks that make up the character, and _ represnets the remaining
//unused bits in the char space.
//    *###__
//    #   #_
//    #   #_
//    ####__
//    #   #_
//    #   #_
//    ####__
//    ______
}
//-------------------------------------------------------------------------------------------
void LCD::setY(byte posY)//0-63 or 0-127 pixels
{
  //Set the y position
  Serial.write(0x7C);
  Serial.write(0x19);//CTRL y
  Serial.write(posY);

}
//-------------------------------------------------------------------------------------------
void LCD::setHome()
{
  Serial.write(0x7C);
  Serial.write(0x18);
  Serial.write((byte)0);//set x back to 0

  Serial.write(0x7C);
  Serial.write(0x19);
  Serial.write((byte)0);//set y back to 0
}
//-------------------------------------------------------------------------------------------
void LCD::setPixel(byte x, byte y, byte set)
{
  Serial.write(0x7C);
  Serial.write(0x10);//CTRL p
  Serial.write(x);
  Serial.write(y);
  Serial.write(0x01);
  delay(10);
}
//-------------------------------------------------------------------------------------------
void LCD::drawLine(byte x1, byte y1, byte x2, byte y2, byte set)
{
  //draws a line from two given points. You can set and reset just as the pixel function.
  Serial.write(0x7C);
  Serial.write(0x0C);//CTRL l
  Serial.write(x1);
  Serial.write(y1);
  Serial.write(x2);
  Serial.write(y2);
  Serial.write(0x01);
  delay(10);

}
//-------------------------------------------------------------------------------------------
void LCD::drawBox(byte x1, byte y1, byte x2, byte y2, byte set)
{
  //draws a box from two given points. You can set and reset just as the pixel function.
  Serial.write(0x7C);
  Serial.write(0x0F);//CTRL o
  Serial.write(x1);
  Serial.write(y1);
  Serial.write(x2);
  Serial.write(y2);
  Serial.write(0x01);
  delay(10);

}
//-------------------------------------------------------------------------------------------
void LCD::drawCircle(byte x, byte y, byte rad, byte set)
{
//draws a circle from a point x,y with a radius of rad.
//Circles can be drawn off-grid, but only those pixels that fall within the
//display boundaries will be written.
  Serial.write(0x7C);
  Serial.write(0x03);//CTRL c
  Serial.write(x);
  Serial.write(y);
  Serial.write(rad);
  Serial.write(0x01);
  delay(10);

}
//-------------------------------------------------------------------------------------------
void LCD::eraseBlock(byte x1, byte y1, byte x2, byte y2)
{
  //This is just like the draw box command, except the contents of the box are erased to the background color
  Serial.write(0x7C);
  Serial.write(0x05);//CTRL e
  Serial.write(x1);
  Serial.write(y1);
  Serial.write(x2);
  Serial.write(y2);
  delay(10);

}
/*
 *   ***************************************************************
 *   ***************************************************************
 *   *********************Nuevas funciones**************************
 *   ***************************************************************
 *   ***************************************************************
 */
