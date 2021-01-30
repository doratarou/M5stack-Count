#include <M5Stack.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#define WIFI_SSID "mirai-base-g"
#define WIFI_PASSWORD "justforfun"

//素プレっとシート
const char * host ="https://script.google.com/macros/library/d/1paHM6V_LI3GeRnRjxS4Dvo3iAOr5Ivf23MX_-3L_KRc5X765gNmK_Cgy/1";
//json設定
StaticJsonDocument<255> json_repuest;
char buffer[255];

//カウント初期化
int count=0;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  //wifi
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.println("conecting");
  while(WiFi.status() != WL_CONECTED){
    Serial.print(".");
    delay(500);
    }
  Serial.println();
  //wifi conected
  Serial.println("\nWiFi Conected.");
  Serial.println(WiFi.localIP());
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(10,100);
  M5.Lcd.println("Button crick Now");
  
}
void sendCount(){
  json_repquest["count"] = count;
  serializeJson(json_repquest, buffer, sizeof(buffer));
  HTTPClient http;
  http.begin(host);
  http.addHeader("Content-type", "application/json") ; 
  int status_code = http.POST((unint8_t*)buffer, strlen(buffer));
  Serial.println(status_code);
  if (status_code > 0){
      if(status_code == HTTPO_CODE_FOUND){
        String payload = htpp.getString();
        Serial.println(payload);

        M5.Lcd.setCursor(10, 100);
        m5.Lcd.fillScreen(BLACK);
        M5.Lcd.setTextSize(3);
        M5.Lcd.println ("Send Done");
        
        }
      
    }else{
      Serial.printf("[HTTP] GET...failed, error: %s\n",http.errorToString(status_code).c_str());
      }
  http.end();
  
    
  }
void loop() {
  M5.update();

  //新しいキーボードゲットだぜ；

  if(M5.BtnA.wasReleased()){
    count++;

    M5.Lcd.setCursor(10, 100);
    M5.Lcd.fillScreen(RED);
    M5.Lcd.setTextColor(YELLOW);
    M5.Lcd.setTextSize(3);
    M5.Lcd.printf("count Up": %d, count);
    }

    
    if(M5.BtnC.wasReleased()){
      if(count<=0) count=0;
      count--;

      M5.Lcd.setCursor(10, 100);
      M5.Lcd.fillScreen(GREEN);
      M5.Lcd.setTextColor(BLACK);
      M5.Lcd.setTextSize(3);
      M5.Lcd.printf("count Down": %d, count);
    }

   if(M5.BtnB.wasReleased()){

    M5.Lcd.setCursor(10, 100);
    M5.Lcd.fillScreen(BLUE);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(3);
    M5.Lcd.printf("count Send: %d", count);

    sendCount();
    }

}
