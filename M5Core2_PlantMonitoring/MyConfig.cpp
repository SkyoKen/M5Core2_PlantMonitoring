#include "MyConfig.h"


//private


//---------------------------------------------------------------------------------------------
//wifi
//---------------------------------------------------------------------------------------------
void 
MyConfig::wifiConnect() {
  
  M5.Lcd.setTextSize(2);
  WiFi.begin(SSID_NAME, SSID_PASSWORD);  // Wi-Fi APに接続する
    while (WiFi.status() != WL_CONNECTED) {  //  Wi-Fi AP接続待ち
        delay(500);
        M5.Lcd.print('.');
    }
    M5.Lcd.print("\r\nWiFi connected\r\nIP address: ");
    M5.Lcd.println(WiFi.localIP());
    delay(500);
    configTime(JST, 0,  "ntp.nict.jp", "time.google.com","ntp.jst.mfeed.ad.jp");
    
}

//---------------------------------------------------------------------------------------------
//ENVII
//---------------------------------------------------------------------------------------------
void 
MyConfig::ENVIIConnect() {
  
  //ENVII
  M5.Lcd.setTextColor(WHITE,TFT_BLACK);
  M5.Lcd.print("BMP280 sensor: ");
  if (!bme.begin(0x76)){  
    M5.Lcd.setTextColor(RED,TFT_BLACK);
    M5.Lcd.println("not found ");
  }else{
    M5.Lcd.setTextColor(GREEN,TFT_BLACK);
    M5.Lcd.println("OK ");
  } 
}

void
MyConfig::updateENVII(){
  pressure = bme.readPressure();
  if(sht30.get()==0){
    tmp = sht30.cTemp;
    hum = sht30.humidity;
  }
  Serial.printf("Temperatura: %2.2f*C  Humedad: %0.2f%%  Pressure: %0.2fPa\r\n", tmp, hum, pressure);
}

//---------------------------------------------------------------------------------------------
//TVOC
//---------------------------------------------------------------------------------------------
void
MyConfig::TVOCConnect(){
  
  //TVOC
  M5.Lcd.setTextColor(WHITE,TFT_BLACK);
  M5.Lcd.print("SGP30 sensor: ");
  if (! sgp.begin()){
    M5.Lcd.setTextColor(RED,TFT_BLACK);
    M5.Lcd.println("not found ");
  }else{
    M5.Lcd.setTextColor(GREEN,TFT_BLACK);
    M5.Lcd.println("OK ");
  }
}

void
MyConfig::updateTVOC(){
  if (! sgp.IAQmeasure()) {
    Serial.println("Measurement failed");
    return;
  }
  
  TVOC = sgp.TVOC;
  eCO2 = sgp.eCO2;

  Serial.print("TVOC "); Serial.print(TVOC); Serial.print(" ppb\t");
  Serial.print("eCO2 "); Serial.print(eCO2); Serial.println(" ppm");
 
  //delay(1000);
}
//---------------------------------------------------------------------------------------------
//time
//---------------------------------------------------------------------------------------------
void
MyConfig::updateTime(){
 getLocalTime(&tm); 
}

void
MyConfig::drawTime() {
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextColor(GREEN,TFT_BLACK);
  M5.Lcd.setCursor(60,120);
  M5.Lcd.printf("%d/%2d/%2d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
  M5.Lcd.setCursor(80,168);
  M5.Lcd.printf("%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
}

//---------------------------------------------------------------------------------------------
//Weather
//---------------------------------------------------------------------------------------------
void
MyConfig::WeatherConnect(){
  configTime(JST, 0,  "ntp.jst.mfeed.ad.jp");
  updateTime();
  updateWeather();
}
void
MyConfig::updateWeather(){
  int count = 0;
 
  portENTER_CRITICAL_ISR(&mutex);
  count = intrGetCount;
  portEXIT_CRITICAL_ISR(&mutex);

  // １時間に１回取得する
  if(count >= 60) {
    if(weatherJMA.getWeather() == false) {
      // もう一度行う
      delay(1000);
      return;
    }
    portENTER_CRITICAL_ISR(&mutex);
    intrGetCount = 0;
    portEXIT_CRITICAL_ISR(&mutex);

  }
}
//---------------------------------------------------------------------------------------------
//ambient
//---------------------------------------------------------------------------------------------
void
MyConfig::AmbientConnect(){
  ambient.begin(channelId, writeKey, &client);  //  チャネルIDとライトキーを指定してAmbientの初期化
}

void
MyConfig::sendData(){
  // Ambientデータセット
  ambient.set(1, String(tmp).c_str());
  ambient.set(2, String(hum).c_str());
  ambient.set(3, String(pressure/100).c_str());
  ambient.set(4, String(TVOC).c_str());
  ambient.set(5, String(eCO2).c_str());
      
  // Ambient送出
  ambient.send();
}
//---------------------------------------------------------------------------------------------
//graph
//---------------------------------------------------------------------------------------------
void
MyConfig::drawGraphics() {

  
  //数値の表示される部分が桁数増えると残像残るので定期的にクリアする
  M5.Lcd.fillRect(0, 0, 320, 29, BLACK);
  M5.Lcd.fillRect(0, 31, 320, 48, BLACK);
  M5.Lcd.fillRect(0, 91, 320, 28, BLACK);
  graph1.setTextColor(WHITE);
  graph1.setTextSize(2); 
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(WHITE,TFT_BLACK);
  M5.Lcd.drawNumber(sgp.eCO2, 90, 30, 7);
  M5.Lcd.drawString("ppm", 250, 50, 4);

  sprintf(ts, " %02d/%02d %02d:%02d", tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);
  M5.Lcd.drawString(ts,         5, 0, 4);
  M5.Lcd.drawNumber(sgp.TVOC, 230, 0, 4);
  M5.Lcd.drawString("ppb",    275, 0, 4);
  M5.Lcd.drawFloat(tmp, 2,    40, 90, 4);
  M5.Lcd.drawString("C",      110, 90, 4);
  M5.Lcd.drawFloat(hum, 2,    180, 90, 4);
  M5.Lcd.drawString("%",      250, 90, 4);

  M5.Lcd.drawLine(0, 25, 320, 25, LIGHTGREY);
  M5.Lcd.drawLine(0, 80, 320, 80, LIGHTGREY);// 下に温度・湿度を表示させる
  M5.Lcd.drawLine(0, 119, 320, 119, LIGHTGREY);// 以下、グラフ表示

  //graph
  //四角形の高さ　Co2計測値 * 120(グラフの最大高さ) / Co2最大値
  height = (sgp.eCO2 * 120) / 3000;
  //点のy位置 121(Display一番下から1Px上) - 四角形の高さ
  Ycoordinate = int(121 - height);
  graph1.pushSprite(0, 120);//グラフ表示範囲 横・縦
  //Serial.print(Ycoordinate);Serial.print("-");Serial.println(height);

  if (j < 33) {
    j += 1;
    print_graph(sgp.eCO2, j, Ycoordinate, height);
    delay(1000); // wait so things do not scroll too fast
    graph1.scroll(-1, 0);
  }
  if ( j >= 33) {
    print_graph(sgp.eCO2, j, Ycoordinate, height);
    graph1.scroll(-10, 0); // scroll graph 10 pixel left, 0 up/down
  }

}
//graph表示 Co2濃度ごとに色分けする
void
MyConfig::print_graph(int co2, int j, int y, int h){
  if(co2 < 600){
    graph1.fillRect(j * 9, y, 9, h, CYAN);//点のx位置,点のy位置,四角形の幅,四角形の高さ
  }else if(co2 > 600 && co2 < 800){
    graph1.fillRect(j * 9, y, 9, h, GREEN);
  }else if(co2 > 800 && co2 < 1000){
    graph1.fillRect(j * 9, y, 9, h, YELLOW);  
  }else if(co2 > 1000 && co2 < 1400){
    graph1.fillRect(j * 9, y, 9, h, TFT_ORANGE);    
  }else if(co2 > 1400 && co2< 1900){
    graph1.fillRect(j * 9, y, 9, h, TFT_MAGENTA);
  }else if(co2 > 1900){
    graph1.fillRect(j * 9, y, 9, h, TFT_RED);
  }
}


void
MyConfig::spiffsWriteBaseline(uint16_t eCO2_new, uint16_t TVOC_new) {
  // eCO2とTVOCのbaseline値を書き込む
  // uint16_tをuint8_tに分割する
  File fp = SPIFFS.open("/baseline", FILE_WRITE);
  uint8_t baseline[4] = { (eCO2_new & 0xFF00) >> 8, eCO2_new & 0xFF, (TVOC_new & 0xFF00) >> 8, TVOC_new & 0xFF };
  fp.write(baseline, 4);
  fp.close();
  Serial.printf("SPIFFS Wrote %x %x %x %x\n", baseline[0], baseline[1], baseline[2], baseline[3]);
}


void
MyConfig::drawMsg(){
  weatherJMA.drawWeather(tm);
 //line
  M5.Lcd.drawFastHLine(0, 156, 320, LIGHTGREY);
  M5.Lcd.drawFastHLine(0, 31, 200, LIGHTGREY);
  M5.Lcd.drawFastHLine(10, 106, 180, LIGHTGREY);
  M5.Lcd.drawFastVLine(200, 0, 156, LIGHTGREY);
  for(int i = 1; i < 4; i++) {
    M5.Lcd.drawFastVLine((80 * i), 168, 60, LIGHTGREY);
  }
 
  //env
  M5.Lcd.loadFont(gd_16,SD);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE,TFT_BLACK);
  M5.Lcd.setCursor(30, 21*2);
  M5.Lcd.fillRect(70, 21*2, 80, 21*2.75, TFT_BLACK);
  M5.Lcd.printf("温度: ");
  M5.Lcd.setTextColor((tmp<3.0?TFT_BLUE:(eCO2<10.0?TFT_GREEN:(eCO2<20.0?TFT_YELLOW:TFT_RED))),TFT_BLACK);
  M5.Lcd.printf("%2.2f", tmp);
  M5.Lcd.setTextColor(WHITE,TFT_BLACK);
  M5.Lcd.printf(" ℃\n");
  M5.Lcd.setCursor(30, 21*3);
  M5.Lcd.printf("湿度: %0.2f %%\n", hum);
  M5.Lcd.setCursor(30, 21*4);
  M5.Lcd.printf("気圧: %0.2f Pa\n", pressure/100);

  //TVOC
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE,TFT_BLACK);
  M5.Lcd.setCursor(30, 10 + 21*5);
  M5.Lcd.fillRect(75, 10 + 21*5, 75, 21*1.85, TFT_BLACK);
  M5.Lcd.printf("TVOC: %4d ppb\n", TVOC);
  M5.Lcd.setCursor(30, 10 + 21*6);
  
  M5.Lcd.printf("eCO2: ");
  M5.Lcd.setTextColor((eCO2<600?TFT_GREEN:(eCO2<1000?TFT_YELLOW:TFT_RED)), TFT_BLACK);
  M5.Lcd.printf("%4d", eCO2);
  M5.Lcd.setTextColor(WHITE,TFT_BLACK);
  M5.Lcd.printf(" ppm\n");

  //photo
  M5.Lcd.drawPngFile(SD, "/chili pepper.png", 0, 158);

  //text
  M5.Lcd.setCursor(80 + 10, 174);
  M5.Lcd.printf("発芽適温");
  M5.Lcd.setCursor(80 + 10, 198);
  M5.Lcd.printf("23~30度");

  
  M5.Lcd.setCursor(80*2 + 10, 174);
  M5.Lcd.printf("栽培適温");
  M5.Lcd.setCursor(80*2 + 10, 198);
  M5.Lcd.printf("15~25度");

  M5.Lcd.setCursor(80*3 + 10, 174);
  M5.Lcd.printf("栽培期間");
  M5.Lcd.setCursor(80*3 + 10, 198);
  M5.Lcd.printf(" 70~日");
  M5.Lcd.unloadFont();

}

void 
MyConfig::updateDraw(){
  //env
  M5.Lcd.loadFont(gd_16,SD);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE,TFT_BLACK);
  M5.Lcd.setCursor(30, 21*2);
  M5.Lcd.fillRect(70, 21*2, 80, 21*2.75, TFT_BLACK);
  M5.Lcd.printf("温度: ");
  M5.Lcd.setTextColor((tmp<3.0?TFT_BLUE:(eCO2<10.0?TFT_GREEN:(eCO2<20.0?TFT_YELLOW:TFT_RED))),TFT_BLACK);
  M5.Lcd.printf("%2.2f", tmp);
  M5.Lcd.setTextColor(WHITE,TFT_BLACK);
  M5.Lcd.printf(" ℃\n");
  M5.Lcd.setCursor(30, 21*3);
  M5.Lcd.printf("湿度: %0.2f %%\n", hum);
  M5.Lcd.setCursor(30, 21*4);
  M5.Lcd.printf("気圧: %0.2f Pa\n", pressure/100);

  //TVOC
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE,TFT_BLACK);
  M5.Lcd.setCursor(30, 10 + 21*5);
  M5.Lcd.fillRect(75, 10 + 21*5, 75, 21*1.85, TFT_BLACK);
  M5.Lcd.printf("TVOC: %4d ppb\n", TVOC);
  M5.Lcd.setCursor(30, 10 + 21*6);
  
  M5.Lcd.printf("eCO2: ");
  M5.Lcd.setTextColor((eCO2<600?TFT_GREEN:(eCO2<1000?TFT_YELLOW:TFT_RED)), TFT_BLACK);
  M5.Lcd.printf("%4d", eCO2);
  M5.Lcd.setTextColor(WHITE,TFT_BLACK);
  M5.Lcd.printf(" ppm\n");
  M5.Lcd.unloadFont();
}

//---------------------------------------------------------------------------------------------
//public
//---------------------------------------------------------------------------------------------

MyConfig::MyConfig() {

}


void 
MyConfig::setup() {
    
    Wire.begin();  
    wifiConnect();
    ENVIIConnect();
    TVOCConnect();
    WeatherConnect();
    ambient.begin(channelId, writeKey, &client);  //  チャネルIDとライトキーを指定してAmbientの初期化
    graph1.setColorDepth(8);
    graph1.createSprite(320, 120);
    graph1.fillSprite(BLACK);
    graph1.pushSprite(0, 120);
    
    drawMsg();
    
}

bool
MyConfig::wifiIsConnect() {
  
  return WiFi.status() == WL_CONNECTED;
  
}

void 
MyConfig::show(){

  switch(num){
    case 0:
      updateDraw();
      break;
    case 1:
      drawGraphics();
      break;
    case 2:
      M5.Lcd.clearDisplay(BLACK);
      drawTime();
      break;
    }
  delay(500);
  
  if(millis()- last_Anvi_millis> 1000) {
    last_Anvi_millis = millis();

      updateTime();
      updateENVII();
      updateTVOC();
      updateWeather();
      sendData();
      
  }
}
void 
MyConfig::pageUp(){
  
  num>=PAGENUM-1 ? num : num++;
  change();
  
}

void 
MyConfig::pageDown(){
  
  num==0 ? num : num--;
  change();
  
}

void 
MyConfig::pageTurn0(){
  
  num = 0;
  change();
  
}

void
MyConfig::change(){
  
   switch(num){
    case 0:
      M5.Lcd.fillScreen(BLACK);
      drawMsg();
      break;
    case 1:
      M5.Lcd.fillScreen(BLACK);
      drawGraphics();
      break;
    case 2:
      M5.Lcd.fillScreen(BLACK);
      drawTime();
      break;
    }
}











MyConfig myConfig;
