#include <M5Stack.h>
int JoyStick_X = 0; //x
int JoyStick_Y = 1; //y
int JoyStick_Z = 3; //key
  void setup() 
{
  M5.begin();
  pinMode(JoyStick_Z, INPUT); 
  pinMode(JoyStick_X, INPUT);
  pinMode(JoyStick_y, INPUT);
  Serial.begin(9600); // 9600 bps
}
void loop() 
{
  int x,y,z;
  x=analogRead(JoyStick_X);
  y=analogRead(JoyStick_Y);
  z=digitalRead(JoyStick_Z);
  Serial.print(x ,DEC);
  Serial.print(",");
  Serial.print(y ,DEC);
  Serial.print(",");
  Serial.println(z ,DEC);
  delay(100);
}
