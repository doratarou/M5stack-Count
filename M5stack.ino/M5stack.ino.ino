#include <M5Stack.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>

#define WIFI_SSID "mirai-base-g"
#define WIFI_PASSWORD "justforfun"

//スプレっとシート
const char *host ="https://script.google.com/macros/s/AKfycbxSEPyXGV3sGZuI3yCbWrs40eXv6ZiUjmP9dTNfYPcYcjWgRxbep2LU/exec";//一文字ずつlistへ cherは1文字
//json設定
StaticJsonDocument<255> json_request;//jsonさんが予約 data領域を予約 json_request名前 辞書
char buffer[255];//list指定　２５５個分

//カウント初期化
int count=0;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  //wifi
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);//wifi接続
  
  Serial.println("conecting");
  while(WiFi.status() != WL_CONNECTED){//print      どっちも１
    Serial.print(".");
    delay(500);
    }

    
  Serial.println();
  //wifi conected
  Serial.println("\nWiFi Conected.");
  Serial.println(WiFi.localIP());//ip表示
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(10,100);
  M5.Lcd.println("Button crick Now");
  
}


void sendCount(){
  json_request["count"] = count;//辞書　新しいのを付ける
  serializeJson(json_request, buffer, sizeof(buffer));//翻訳　Json を　キャラ型でバッファーに入れる　何個入れるか
  HTTPClient http;//おぶじぇくと（HTTPClient型)
  http.begin(host);//通信開始命令
  http.addHeader("Content-type", "application/json") ;//jsonだよ
  int status_code = http.POST( (uint8_t*) buffer , strlen(buffer));//序盤は削ぎ落とし(space消し)　変換　何文字分送るか　
  Serial.println(status_code);
  if (status_code > 0){
      if(status_code == HTTP_CODE_FOUND){
        String payload = http.getString();//レスポンスが返ってくる
        Serial.println(payload);

        M5.Lcd.setCursor(10, 100);
        m5.Lcd.fillScreen(BLACK);
        M5.Lcd.setTextSize(3);
        M5.Lcd.println ("Send Done");
        
        }
      
    }else{
      Serial.printf("[HTTP] GET...failed, error: %s\n",http.errorToString(status_code).c_str());//status_code言葉に変換　NULL文字にしてデータにゴールをツくっている詳しくはウェブで
      }
  http.end();//終わりの始まり
  
    
  }
void loop() {
  M5.update();//もう一回見るやつ　状態を更新

  //新しいキーボードゲットだぜ；

  if(M5.BtnA.wasReleased()){
    count++;

    M5.Lcd.setCursor(10, 100);
    M5.Lcd.fillScreen(RED);
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.setTextSize(3);
    M5.Lcd.printf("count Up: %d", count);
    }

    
    if(M5.BtnC.wasReleased()){
      if(count<=0) count=0;
      count--;

      M5.Lcd.setCursor(10, 100);
      M5.Lcd.fillScreen(GREEN);
      M5.Lcd.setTextColor(BLACK);
      M5.Lcd.setTextSize(3);
      M5.Lcd.printf("count Down: %d", count);
    }

   if(M5.BtnB.wasReleased()){

    M5.Lcd.setCursor(10, 100);
    M5.Lcd.fillScreen(BLUE);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.printf("count Send: %d", count);

    sendCount();//関数
    }

}
