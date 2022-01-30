/*
 * SLAVE CONFIG
 */

#include "Wire.h"
#include "SoftwareSerial.h"

#define SLAVE_ADDR 0x04
SoftwareSerial softSerial(2, 3); // RX, TX


int leng=0;
char cola[29];
char pos[14];
uint8_t sp01;

void receiveFunc()
{
   while (Wire.available() != 1);
}

void sendFunc()
{ 
  for(int i = 0;i<=29;i++){
    Wire.write(cola[i]); 
    Serial.print(cola[i]);
  }
  Serial.println();
  //Wire.write(cola[leng]); 
  //Serial.println(cola[leng]);
  
}



void setup()
{
   // put your setup code here, to run once:
   Serial.begin(115200);
   Wire.begin(SLAVE_ADDR);
   Wire.onReceive(receiveFunc);
   Wire.onRequest(sendFunc);
   
  
}

void loop()
{
  if(Serial.available()){
    cola[leng]=Serial.read();
    //Serial.print(cola[leng]);
    leng=leng+1;
    if(leng==30 || cola[leng-1]=='p' ){
      leng=0; 
    }
  }
  //Serial.print(cola[29]);
  int p=0;
  for(int i=0; i<=31;i++){   
    if(cola[i]=='p'){
      for(int q=0;i<=31;i++){
        pos[q]=cola[i];
        i=i+1;
      }

      
      
      //Serial.print(pos[p]);
      p=p+1;
      if(p==15){
        p=0; 
      }
    }
    //fin de la matris de pos
    
   }
 
      
    

  }
  //Serial.println();

  

 /*
  while(!Serial.available());
    cola[leng]= Serial.read();  
    leng=leng+1;
    if(leng==25){
      leng=0; 
    }
    */  
