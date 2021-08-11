boolean Num_Array[10][7]={
{1,1,1,1,1,1,0}, //0
{0,1,1,0,0,0,0}, //1
{1,1,0,1,1,0,1}, //2
{1,1,1,1,0,0,1}, //3
{0,1,1,0,0,1,1}, //4
{1,0,1,1,0,1,1}, //5
{1,0,1,1,1,1,1}, //6
{1,1,1,0,0,1,0}, //7
{1,1,1,1,1,1,1}, //8
{1,1,1,1,0,1,1} //9
};
//LED表示関数を定義
void NumPrint(int Number){
  for (int w=0; w<=7; w++){
    digitalWrite(w+2,-Num_Array[Number][w]);
  }
}

void off7SegLED(){
digitalWrite(2,LOW);
digitalWrite(3,LOW);
digitalWrite(4,LOW);
digitalWrite(5,LOW);
digitalWrite(6,LOW);
digitalWrite(7,LOW);
digitalWrite(8,LOW);
}
void setup(){
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
}

void loop(){
  while(digitalRead(9) != LOW){
    
    }
  for(int i=0;i<10;i++){
    NumPrint(9- i);
    delay(1000);
    off7SegLED();
    }

  

}
