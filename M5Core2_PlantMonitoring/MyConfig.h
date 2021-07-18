#include <M5Core2.h>

//page
#define PAGENUM 3

//wifi
#include <WiFi.h>
#define SSID_NAME "●●●●●●●●"
#define SSID_PASSWORD "●●●●●●●●"


//ENVII
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BMP280.h"
#include "SHT3X.h"

//TVOC
#include "Adafruit_SGP30.h"

//time
#define JST (3600L * 9)

//Weather
#include "WeatherJMA.h"
#define TIMEOUT_COUNT 60

// Ambient
#include "Ambient.h"

class MyConfig {
private:

  //font
  String gd_16 = "/font/Gen Shin Gothic Regular16";
 
  //page
  int num = 0;

  //wifi
  void wifiConnect();

  //ENVII
  SHT3X sht30;
  Adafruit_BMP280 bme;
  float tmp = 0.0;
  float hum = 0.0;
  float pressure = 0.0;
  void ENVIIConnect();
  void updateENVII();

  //TVOC
  Adafruit_SGP30 sgp;
  int TVOC = 0; 
  int eCO2 = 0;
  void TVOCConnect();
  void updateTVOC();

  //time
  struct tm tm;
  char ts[20];//文字格納用
  portMUX_TYPE mutex = portMUX_INITIALIZER_UNLOCKED;
  volatile int intrGetCount = TIMEOUT_COUNT;  // 初回で必ず取得するようにする
  unsigned long last_Anvi_millis;
  void updateTime();
  void drawTime();
  void IRAM_ATTR getCountIntr()
  {
    portENTER_CRITICAL_ISR(&mutex);
    intrGetCount++;
    portEXIT_CRITICAL_ISR(&mutex);
  }
  
  //weather
  void WeatherConnect();
  void updateWeather();
  
  //Ambient https://ambidata.io/
  WiFiClient client;
  Ambient ambient;
  unsigned int channelId =  ●●●●●●●●; // AmbientのチャネルID
  const char* writeKey = "●●●●●●●●"; // ライトキー　※書き込むほうのキー
  void AmbientConnect();
  void sendData();

  //graph
  int Ycoordinate;
  int height;
  TFT_eSprite graph1 = TFT_eSprite(&M5.Lcd);
  int j = 0;
  int z = 0;
  void drawGraphics();
  void print_graph(int co2, int j, int y, int h);
  void spiffsWriteBaseline(uint16_t eCO2_new, uint16_t TVOC_new);

  //
  void drawMsg();
  void updateDraw();
 
public:
  MyConfig();
  
  void setup();
  bool wifiIsConnect();
  void show();

  //ChangePage
  void pageUp();
  void pageDown();
  void pageTurn0();
  void change();


};

extern MyConfig myConfig;
