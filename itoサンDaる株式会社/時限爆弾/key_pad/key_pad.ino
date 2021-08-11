/*
  NAME:
  Demo of keypad pressing processing with the library gbj_tm1638

  DESCRIPTION:
  The sketch performs some visual effects for various click actions on a key and
  prints particular action name to the serial monitor.
  - Connect controller's pins to Arduino's pins as follows:
    - TM1638 pin CLK to Arduino pin D2
    - TM1638 pin DIO to Arduino pin D3
    - TM1638 pin STB to Arduino pin D4
    - TM1638 pin Vcc to Arduino pin 5V
    - TM1638 pin GND to Arduino pin GND
  - The sketch is configured to work with all hardware elements, i.e., 8 digital
    tubes, 8 red LEDs, and 8 keys.
  - By single clicking on a key, the sketch turns on corresponding red LED.
  - By double clicking on a key, the sketch turns off corresponding red LED.
  - By single holding a key pressed, the sketch turns on corresponding tube.
  - By double holding a key pressed, the sketch turns off corresponding tube.

  LICENSE:
  This program is free software; you can redistribute it and/or modify
  it under the terms of the MIT License (MIT).

  CREDENTIALS:
  Author: Libor Gabaj
*/
#include "gbj_tm1638.h"
#include "../extras/font7seg_basic.h"
#define SKETCH "GBJ_TM1638_KEYPAD 1.0.0"
int my_millis;
int m;
int m2;
int m3=0;
const unsigned int PERIOD_TEST = 2000;  // Time in miliseconds between tests
const unsigned int PERIOD_VALUE = 300; // Time delay in miliseconds for displaying a value
const unsigned char PIN_TM1638_CLK = 2;
const unsigned char PIN_TM1638_DIO = 3;
const unsigned char PIN_TM1638_STB = 4;
unsigned int TEST_LIMIT = 60 * 2;
char textBuffer[17];
int true_music;
gbj_tm1638 Sled = gbj_tm1638(PIN_TM1638_CLK, PIN_TM1638_DIO, PIN_TM1638_STB);






void errorHandler()
{
  if (Sled.isSuccess()) return;
  Serial.print("Error: ");
  Serial.println(Sled.getLastResult());
  Serial.println(Sled.getLastCommand());
}


void keyHandler(uint8_t key, uint8_t action)
{
  m=key;

  switch (action)
  {
    case gbj_tm1638::KEY_CLICK:
//      Sled.printLedOnRed(key);
      break;

    case gbj_tm1638::KEY_HOLD:
//      Serial.println("KEY_HOLD");
//      Sled.printDigitOn(key);
      break;

    case gbj_tm1638::KEY_CLICK_DOUBLE:
//      Serial.println("KEY_CLICK_DOUBLE");
//      Sled.printLedOff(key);
      break;

    case gbj_tm1638::KEY_HOLD_DOUBLE:
//      Serial.println("KEY_HOLD_DOUBLE");
//      Sled.printDigitOff(key);
      break;
  }
  if (Sled.display()) errorHandler();
}


void displayTest()
{
  if (Sled.display()) errorHandler();
  delay(PERIOD_TEST);
}

//void music(int music) {
//int  BEATTIME=5; //音を出している時間(msec)
//int SPEAKER=12; //スピーカーの出力ピン番号
//switch(music){
//  case 1:
//    tone(SPEAKER,262,BEATTIME); // ド
//    delay(BEATTIME) ;
//    break;
//  
//  case 2:
//    tone(SPEAKER,294,BEATTIME); // レ
//    delay(BEATTIME) ;
//    break;
//  case 3:
//    tone(SPEAKER,330,BEATTIME); // ミ
//    delay(BEATTIME) ;
//    break;
//  case 4:
//    tone(SPEAKER,349,BEATTIME); // ファ
//    delay(BEATTIME) ;
//    break;
//  case 5:
//    tone(SPEAKER,392,BEATTIME); // ソ
//    delay(BEATTIME) ;
//    break;
//  case 6:
//    tone(SPEAKER,440,BEATTIME); // ラ
//    delay(BEATTIME) ;
//    break;
//  case 7:
//    tone(SPEAKER,494,BEATTIME); // シ
//    delay(BEATTIME);
//    break;
//  case 8:
//    tone(SPEAKER,523,BEATTIME); // ド
//    delay(BEATTIME);
//    break;
//}
//}

void setup()
{
  Serial.begin(9600);
  Serial.println(SKETCH);
  Serial.println("Libraries:");
  Serial.println(gbj_tm1638::VERSION);
  Serial.println("---");
  Serial.println("Waiting for keypad...");
  // Initialize controller
  Sled.begin();
  if (Sled.isError())
  {
    errorHandler();
    return;
  }
  Sled.registerHandler(keyHandler);
  Sled.setFont(gbjFont7segTable, sizeof(gbjFont7segTable));
}


void loop()
{
  m=10;

  unsigned char valueMin1 = (TEST_LIMIT) / 60;
  unsigned char valueSec1 = (TEST_LIMIT) % 60;


  sprintf(textBuffer, "%02u:%02u", valueMin1, valueSec1);
  Sled.printText(textBuffer, 4);
  Sled.display();
  Sled.run();
  if(m==1){
    
    TEST_LIMIT+=60;
    }
  if(m==2){
     TEST_LIMIT-=60;
    }
  
  if(m==4){
     Sled.printText("        ",0);
     Sled.display();
     while(1){
       m=100;
       Sled.run();
       
       if(m!=100){
        break;
        }
      }
    }
  if(m==0){
    true_music=0;
    if (Sled.isError()) return;

    
    for (unsigned int i = 0; i < TEST_LIMIT; i++)
    {
      if(m3==1){
        m3=0;
        break;
        }
      valueMin1 = (TEST_LIMIT - i) / 60;
      valueSec1 = (TEST_LIMIT - i) % 60;


      sprintf(textBuffer, "%02u:%02u", valueMin1, valueSec1);
      Sled.printText(textBuffer, 4);
      Sled.display();
      my_millis = millis() / 1000 -0.01;
      
      while(millis() /1000 - my_millis <= 1){//1秒間
          Sled.run();
          Serial.println(m);
          if(m==3){
            m2=3;
            }
          while(m2==3){
             m=0;
             Sled.printText(textBuffer, 4);
             Sled.run();
             if(m==3){
              m2=0;
              m=100;
              }
             
            }

          if(m==7){
            m3=1;
            true_music = 1;
            break;
            }
           
    }

    
  }

  int s=0;
  //タイマー終わった処理
  while(true_music!=1){
      m = 100;
      Sled.run();


     //music
     
    int i=0;
    while(m==100){
      
     tone(12,339,500);

      Sled.run();
      tone(12,339.5,200);
      delay(240);
      tone(12,330,200);
      delay(267);
      tone(12,330,200);
      delay(267);
      tone(12,262,200);
      delay(267);
      tone(12,330,200);
      delay(267);
      tone(12,392,200);
      delay(267);
      tone(12,262,200);
      delay(267);
      tone(12,392,200);
      delay(267);
      tone(12,330,200);
      delay(267);
      tone(12,440,200);
      delay(267);
      tone(12,494,200);
      delay(267);
      tone(12,440,200);
      delay(267);
      tone(12,440,200);
      delay(267);
      tone(12,392,200);
      delay(267);
      tone(12,330,200);
      delay(267);
      tone(12,392,200);
      delay(267);
      tone(12,440,200);
      delay(267);
      tone(12,349,200);
      delay(267);
      tone(12,349,200);
      delay(267);
      tone(12,392,200);
      delay(267);
      tone(12,330,200);
      delay(267);
      tone(12,262,200);
      delay(267);
      tone(12,294,200);
      delay(267);
      tone(12,494,200);
      delay(267);
      tone(12,262,200);
      delay(267);
      tone(12,392,200);
      delay(267);
      tone(12,330,200);
      delay(267);
      tone(12,440,200);
      delay(267);
      tone(12,494,200);
      delay(267);
      tone(12,440,200);
      delay(267);
      tone(12,440,200);
      delay(267);
      tone(12,392,200);
      delay(267);
      tone(12,330,200);
      delay(267);
      tone(12,392,200);
      delay(267);
      tone(12,440,200);
      delay(267);
      tone(12,349,200);
      delay(267);
      tone(12,349,200);
      delay(267);
      tone(12,392,200);
      delay(267);
      tone(12,330,200);
      delay(267);
      tone(12,262,200);
      delay(267);
      tone(12,294,200);
      delay(267);
      tone(12,494,200);
      delay(267);
      tone(12,392,200);
      delay(267);
      tone(12,349,200);
      delay(267);
      tone(12,349,200);
      delay(267);
      tone(12,349,200);
      delay(267);
      tone(12,349,200);
      delay(267);
      tone(12,294,200);
      delay(267);
      tone(12,330,200);
      delay(267);
      tone(12,392,200);
      delay(267);
      tone(12,440,200);
      delay(267);
      tone(12,262,200);
      delay(267);
      tone(12,440,200);
      delay(267);
      tone(12,262,200);
      delay(267);
      tone(12,494,200);
      delay(267);
      tone(12,392,200);
      delay(267);
      tone(12,349,200);
      delay(267);
      tone(12,349,200);
      delay(267);
      tone(12,349,200);
      delay(267);
      tone(12,349,200);
      delay(267);
      tone(12,294,200);
      delay(267);
      tone(12,330,200);
      delay(267);
      tone(12,262,200);
      delay(267);
      tone(12,262,200);
      delay(267);
      tone(12,262,200);
      delay(267);
      tone(12,392,200);
      delay(267);
      tone(12,349,200);
      delay(267);
      tone(12,349,200);
      delay(267);
      tone(12,349,200);
      delay(267);
      tone(12,349,200);
      delay(267);
      tone(12,294,200);
      delay(267);
      tone(12,330,200);
      delay(267);
      tone(12,392,200);
      delay(267);
      tone(12,440,200);
      delay(267);
      tone(12,262,200);
      delay(267);
      tone(12,440,200);
      delay(267);
      tone(12,262,200);
      delay(267);
      tone(12,294,200);
      delay(267);
      tone(12,294,200);
      delay(267);
      tone(12,294,200);
      delay(267);
      tone(12,262,200);
      delay(267);
    } 
    
    break;
    

    }
  
  }

}
