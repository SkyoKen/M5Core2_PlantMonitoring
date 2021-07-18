#include "MyConfig.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "WeatherJMA.h"

const char* host = "https://www.drk7.jp/weather/json/";
/* 下記の情報から選択して設定する */
const char* pref = "13.js";
const char* areaName = "東京地方";

/***********************/
/* 都道府県（地域）情報  */
/***********************/
/*
    【北海道】  pref : "01.js"
        【地域名】 areaName :
            "胆振地方", "北見地方", "釧路地方", "根室地方", "渡島地方", "日高地方", "上川地方", "十勝地方",
            "石狩地方", "宗谷地方", "後志地方", "留萌地方", "網走地方", "紋別地方", "空知地方", "檜山地方"

    【青森県】  pref : "02.js"
        【地域名】 areaName :
            "津軽", "下北", "三八上北"

    【岩手県】  pref : "03.js"
        【地域名】 areaName :
            "沿岸北部", "沿岸南部", "内陸"

    【宮城県】  pref : "04.js"
        【地域名】 areaName :
            "西部", "東部"

    【秋田県】  pref : "05.js"
        【地域名】 areaName :
            "沿岸", "内陸"

    【山形県】  pref : "06.js"
        【地域名】 areaName :
            "置賜", "村山", "庄内", "最上"

    【福島県】  pref : "07.js"
        【地域名】 areaName :
            "中通り", "浜通り", "会津"

    【茨城県】  pref : "08.js"
        【地域名】 areaName :
            "北部", "南部"

    【栃木県】  pref : "09.js"
        【地域名】 areaName :
            "北部", "南部"

    【群馬県】  pref : "10.js"
        【地域名】 areaName :
            "北部", "南部"

    【埼玉県】  pref : "11.js"
        【地域名】 areaName :
            "秩父地方", "北部", "南部"

    【千葉県】  pref : "12.js"
        【地域名】 areaName :
            "北東部", "北西部", "南部"

    【東京都】  pref : "13.js"
        【地域名】 areaName :
            "東京地方", "伊豆諸島北部", "伊豆諸島南部", "小笠原諸島"

    【神奈川県】  pref : "14.js"
        【地域名】 areaName :
            "東部", "西部"

    【新潟県】  pref : "15.js"
        【地域名】 areaName :
            "上越", "中越", "下越", "佐渡"

    【富山県】  pref : "16.js"
        【地域名】 areaName :
            "東部", "西部"

    【石川県】  pref : "17.js"
        【地域名】 areaName :
            "加賀", "能登"

    【福井県】  pref : "18.js"
        【地域名】 areaName :
            "嶺北", "嶺南"

    【山梨県】  pref : "19.js"
        【地域名】 areaName :
            "中・西部", "東部・富士五湖"

    【長野県】  pref : "20.js"
        【地域名】 areaName :
            "北部", "中部", "南部"

    【岐阜県】  pref : "21.js"
        【地域名】 areaName :
            "飛騨地方", "美濃地方"

    【静岡県】  pref : "22.js"
        【地域名】 areaName :
            "伊豆", "東部", "中部", "西部"

    【愛知県】  pref : "23.js"
        【地域名】 areaName :
            "東部", "西部"

    【三重県】  pref : "24.js"
        【地域名】 areaName :
            "北中部", "南部"

    【滋賀県】  pref : "25.js"
        【地域名】 areaName :
            "北部", "南部"

    【京都府】  pref : "26.js"
        【地域名】 areaName :
            "北部", "南部"

    【大阪府】  pref : "27.js"
        【地域名】 areaName :
            ""

    【兵庫県】  pref : "28.js"
        【地域名】 areaName :
            "北部", "南部"

    【奈良県】  pref : "29.js"
        【地域名】 areaName :
            "北部", "南部"

    【和歌山県】  pref : "30.js"
        【地域名】 areaName :
            "北部", "南部"

    【鳥取県】  pref : "31.js"
        【地域名】 areaName :
            "東部", "中・西部"

    【島根県】  pref : "32.js"
        【地域名】 areaName :
            "東部", "西部", "隠岐"

    【岡山県】  pref : "33.js"
        【地域名】 areaName :
            "北部", "南部"

    【広島県】  pref : "34.js"
        【地域名】 areaName :
            "北部", "南部"

    【山口県】  pref : "35.js"
        【地域名】 areaName :
            "北部", "東部", "中部", "西部"

    【徳島県】  pref : "36.js"
        【地域名】 areaName :
            "北部", "南部"

    【香川県】  pref : "37.js"
        【地域名】 areaName :
            ""

    【愛媛県】  pref : "38.js"
        【地域名】 areaName :
            "東予", "中予", "南予"

    【高知県】  pref : "39.js"
        【地域名】 areaName :
            "東部", "中部", "西部"

    【福岡県】  pref : "40.js"
        【地域名】 areaName :
            "北九州地方", "福岡地方", "筑豊地方", "筑後地方"

    【佐賀県】  pref : "41.js"
        【地域名】 areaName :
            "北部", "南部"

    【長崎県】  pref : "42.js"
        【地域名】 areaName :
            "北部", "南部", "壱岐・対馬", "五島"

    【熊本県】  pref : "43.js"
        【地域名】 areaName :
            "熊本地方", "阿蘇地方", "天草・芦北地方", "球磨地方"

    【大分県】  pref : "44.js"
        【地域名】 areaName :
            "北部", "中部", "西部", "南部"

    【宮崎県】  pref : "45.js"
        【地域名】 areaName :
            "北部平野部", "北部山沿い", "南部平野部", "南部山沿い"

    【鹿児島県】  pref : "46.js"
        【地域名】 areaName :
            "薩摩地方", "大隅地方", "種子島地方・屋久島地方", "奄美地方"

    【沖縄県】  pref : "47.js"
        【地域名】 areaName :
            "本島北部", "本島中南部", "宮古島地方", "久米島", "石垣島地方", "大東島地方", "与那国島地方"

*/

WEATHER_JMA_DEF wether_jma[] = {
  {"晴れ",						"/WeatherIcon/100.png"},
  {"晴れ時々くもり",				"/WeatherIcon/101.png"},
  {"晴れ一時雨",					"/WeatherIcon/102.png"},
  {"晴れ時々雨",					"/WeatherIcon/103.png"},
  {"晴れ一時雪",					"/WeatherIcon/104.png"},
  {"晴れ時々雪",					"/WeatherIcon/105.png"},
  {"晴れ一時雨か雪",				"/WeatherIcon/106.png"},
  {"晴れ時々雨か雪",				"/WeatherIcon/107.png"},
  {"晴れ一時雨か雷雨",			"/WeatherIcon/108.png"},
  {"晴れのち時々くもり",			"/WeatherIcon/110.png"},
  {"晴れのちくもり",				"/WeatherIcon/111.png"},
  {"晴れのち一時雨",				"/WeatherIcon/112.png"},
  {"晴れのち時々雨",				"/WeatherIcon/113.png"},
  {"晴れのち雨",					"/WeatherIcon/114.png"},
  {"晴れのち一時雪",				"/WeatherIcon/115.png"},
  {"晴れのち時々雪",				"/WeatherIcon/116.png"},
  {"晴れのち雪",					"/WeatherIcon/117.png"},
  {"晴れのち雨か雪",				"/WeatherIcon/118.png"},
  {"晴れのち雨か雷雨",			"/WeatherIcon/119.png"},
  {"晴れ朝夕一時雨",				"/WeatherIcon/120.png"},
  {"晴れ朝の内一時雨",			"/WeatherIcon/121.png"},
  {"晴れ夕方一時雨",				"/WeatherIcon/122.png"},
  {"晴れ山沿い雷雨",				"/WeatherIcon/123.png"},
  {"晴れ山沿い雪",				"/WeatherIcon/124.png"},
  {"晴れ午後は雷雨",				"/WeatherIcon/125.png"},
  {"晴れ昼頃から雨",				"/WeatherIcon/126.png"},
  {"晴れ夕方から雨",				"/WeatherIcon/127.png"},
  {"晴れ夜は雨",					"/WeatherIcon/128.png"},
  {"晴れ夜半から雨",				"/WeatherIcon/129.png"},
  {"朝の内霧後晴れ",				"/WeatherIcon/130.png"},
  {"晴れ明け方霧",				"/WeatherIcon/131.png"},
  {"晴れ朝夕くもり",				"/WeatherIcon/132.png"},
  {"晴れ時々雨で雷を伴う",		"/WeatherIcon/140.png"},
  {"晴れ一時雪か雨",				"/WeatherIcon/160.png"},
  {"晴れ時々雪か雨",				"/WeatherIcon/170.png"},
  {"晴れのち雪か雨",				"/WeatherIcon/181.png"},
  {"くもり",						"/WeatherIcon/200.png"},
  {"くもり時々晴れ",				"/WeatherIcon/201.png"},
  {"くもり一時雨",				"/WeatherIcon/202.png"},
  {"くもり時々雨",				"/WeatherIcon/203.png"},
  {"くもり一時雪",				"/WeatherIcon/204.png"},
  {"くもり時々雪",				"/WeatherIcon/205.png"},
  {"くもり一時雨か雪",			"/WeatherIcon/206.png"},
  {"くもり時々雨か雪",			"/WeatherIcon/207.png"},
  {"くもり一時雨か雷雨",			"/WeatherIcon/208.png"},
  {"霧",							"/WeatherIcon/209.png"},
  {"くもりのち時々晴れ",			"/WeatherIcon/210.png"},
  {"くもりのち晴れ",				"/WeatherIcon/211.png"},
  {"くもりのち一時雨",			"/WeatherIcon/212.png"},
  {"くもりのち時々雨",			"/WeatherIcon/213.png"},
  {"くもりのち雨",				"/WeatherIcon/214.png"},
  {"くもりのち一時雪",			"/WeatherIcon/215.png"},
  {"くもりのち時々雪",			"/WeatherIcon/216.png"},
  {"くもりのち雪",				"/WeatherIcon/217.png"},
  {"くもりのち雨か雪",			"/WeatherIcon/218.png"},
  {"くもりのち雨か雷雨",			"/WeatherIcon/219.png"},
  {"くもり朝夕一時雨",			"/WeatherIcon/220.png"},
  {"くもり朝の内一時雨",			"/WeatherIcon/221.png"},
  {"くもり夕方一時雨",			"/WeatherIcon/222.png"},
  {"くもり日中時々晴れ",			"/WeatherIcon/223.png"},
  {"くもり昼頃から雨",			"/WeatherIcon/224.png"},
  {"くもり夕方から雨",			"/WeatherIcon/225.png"},
  {"くもり夜は雨",				"/WeatherIcon/226.png"},
  {"くもり夜半から雨",			"/WeatherIcon/227.png"},
  {"くもり昼頃から雪",			"/WeatherIcon/228.png"},
  {"くもり夕方から雪",			"/WeatherIcon/229.png"},
  {"くもり夜は雪",				"/WeatherIcon/230.png"},
  {"くもり海上海岸は霧か霧雨",	"/WeatherIcon/231.png"},
  {"くもり時々雨で雷を伴う",		"/WeatherIcon/240.png"},
  {"くもり時々雪で雷を伴う",		"/WeatherIcon/250.png"},
  {"くもり一時雪か雨",			"/WeatherIcon/260.png"},
  {"くもり時々雪か雨",			"/WeatherIcon/270.png"},
  {"くもりのち雪か雨",			"/WeatherIcon/281.png"},
  {"雨",							"/WeatherIcon/300.png"},
  {"雨時々晴れ",					"/WeatherIcon/301.png"},
  {"雨時々止む",					"/WeatherIcon/302.png"},
  {"雨時々雪",					"/WeatherIcon/303.png"},
  {"雨か雪",						"/WeatherIcon/304.png"},
  {"大雨",						"/WeatherIcon/306.png"},
  {"風雨共に強い",				"/WeatherIcon/307.png"},
  {"雨で暴風を伴う",				"/WeatherIcon/308.png"},
  {"雨一時雪",					"/WeatherIcon/309.png"},
  {"雨のち晴れ",					"/WeatherIcon/311.png"},
  {"雨のちくもり",				"/WeatherIcon/313.png"},
  {"雨のち時々雪",				"/WeatherIcon/314.png"},
  {"雨のち雪",					"/WeatherIcon/315.png"},
  {"雨か雪のち晴れ",				"/WeatherIcon/316.png"},
  {"雨か雪のちくもり",			"/WeatherIcon/317.png"},
  {"朝の内雨のち晴れ",			"/WeatherIcon/320.png"},
  {"朝の内雨のちくもり",			"/WeatherIcon/321.png"},
  {"雨朝晩一時雪",				"/WeatherIcon/322.png"},
  {"雨昼頃から晴れ",				"/WeatherIcon/323.png"},
  {"雨夕方から晴れ",				"/WeatherIcon/324.png"},
  {"雨夜は晴",					"/WeatherIcon/325.png"},
  {"雨夕方から雪",				"/WeatherIcon/326.png"},
  {"雨夜は雪",					"/WeatherIcon/327.png"},
  {"雨一時強く降る",				"/WeatherIcon/328.png"},
  {"雨一時みぞれ",				"/WeatherIcon/329.png"},
  {"雪か雨",						"/WeatherIcon/340.png"},
  {"雨で雷を伴う",				"/WeatherIcon/350.png"},
  {"雪か雨のち晴れ",				"/WeatherIcon/361.png"},
  {"雪か雨のちくもり",			"/WeatherIcon/371.png"},
  {"雪",							"/WeatherIcon/400.png"},
  {"雪時々晴れ",					"/WeatherIcon/401.png"},
  {"雪時々止む",					"/WeatherIcon/402.png"},
  {"雪時々雨",					"/WeatherIcon/403.png"},
  {"大雪",						"/WeatherIcon/405.png"},
  {"風雪強い",					"/WeatherIcon/406.png"},
  {"暴風雪",						"/WeatherIcon/407.png"},
  {"雪一時雨",					"/WeatherIcon/409.png"},
  {"雪のち晴れ",					"/WeatherIcon/411.png"},
  {"雪のちくもり",				"/WeatherIcon/413.png"},
  {"雪のち雨",					"/WeatherIcon/414.png"},
  {"朝の内雪のち晴れ",			"/WeatherIcon/420.png"},
  {"朝の内雪のちくもり",			"/WeatherIcon/421.png"},
  {"雪昼頃から雨",				"/WeatherIcon/422.png"},
  {"雪夕方から雨",				"/WeatherIcon/423.png"},
  {"雪夜半から雨",				"/WeatherIcon/424.png"},
  {"雪一時強く降る",				"/WeatherIcon/425.png"},
  {"雪のちみぞれ",				"/WeatherIcon/426.png"},
  {"雪一時みぞれ",				"/WeatherIcon/427.png"},
  {"雪で雷を伴う",				"/WeatherIcon/450.png"},
  {"",									""},
};

DynamicJsonDocument m_WeatherInfo(5120);

String ff_16 = "font/ipa-gothic-16"; // without Ext
String ff_24 = "font/ipa-gothic-24"; // without Ext

WeatherJMA::WeatherJMA()
{
    // URLを作成する
    m_URL = host;
    m_URL += pref;
}

// JSONP形式からJSON形式に変える
String
WeatherJMA::Jsonp2Json(String jsonString)
{
    jsonString.replace("drk7jpweather.callback(","");
    return jsonString.substring(0,jsonString.length()-2);
}

bool
WeatherJMA::getWeather()
{
    bool ret = true;

    // ネットワーク接続状態確認
    if (myConfig.wifiIsConnect() != true) {
        Serial.printf("WiFi.status() not connect\n");
        return false;
    }

    HTTPClient http;

    http.begin(m_URL);

    int httpCode = http.GET();
    if (httpCode > 0)
    {
        //jsonオブジェクトの作成
        String jsonString = Jsonp2Json(http.getString());
        StaticJsonDocument<200> filter;

        // areaNameの有無でfilterの設定方法が異なる(取得できるJsonに差があるため)
        if(strlen(areaName) > 0) {
            filter["pref"]["area"][areaName]["info"][0]["rainfallchance"] = true;
            filter["pref"]["area"][areaName]["info"][0]["weather"] = true;
            filter["pref"]["area"][areaName]["info"][0]["date"] = true;
            filter["pref"]["area"][areaName]["info"][0]["temperature"] = true;
        }
        else {
            filter["pref"]["area"]["info"][0]["rainfallchance"] = true;
            filter["pref"]["area"]["info"][0]["weather"] = true;
            filter["pref"]["area"]["info"][0]["date"] = true;
            filter["pref"]["area"]["info"][0]["temperature"] = true;
        }
        // デシリアライズ（フィルタ付き）する
        deserializeJson(m_WeatherInfo, jsonString, DeserializationOption::Filter(filter));
    }
    else
    {
        Serial.println("Error on HTTP request");
        ret = false;
    }
    http.end(); //リソースを解放

    return ret;
}

String
WeatherJMA::getWeatherInfoJson()
{
    if(strlen(areaName) > 0) {
        String info = m_WeatherInfo["pref"]["area"][areaName];
        return info;
    }
    else {
        String info = m_WeatherInfo["pref"]["area"];
        return info;
    }
}

String
WeatherJMA::getWeatherDayJson()
{
    String info = getWeatherInfoJson();

    DynamicJsonDocument doc(4096);
    deserializeJson(doc, info);

    String day = doc["info"][m_select_day_idx];
    return day;
}


void
WeatherJMA::drawDay(struct tm st_tm)
{
    char date[64] = {0};
    const char *wday[] = {"日","月","火","水","木","金","土"};

    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(5, 5);

    snprintf(date, sizeof(date), "%4d/%02d/%02d(%s)", st_tm.tm_year + 1900, st_tm.tm_mon + 1, st_tm.tm_mday, wday[st_tm.tm_wday]);

    M5.Lcd.print(date);
}

void
WeatherJMA::drawWeatherIcon()
{
    int i;
    char *p_fname = NULL;

    String day = getWeatherDayJson();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, day);

    for(i = 0; strlen(wether_jma[i].str) != 0 ; i++) {
        if(String(wether_jma[i].str) == doc["weather"]) {
            p_fname = (char*)wether_jma[i].fname;
            break;
        }
    }

    if(p_fname != NULL) {
        M5.Lcd.drawPngFile(SD, p_fname, 225, 34);
    }else{
        M5.Lcd.drawPngFile(SD, "/WeatherIcon/100.png", 225, 34);
    }

    int str_len = strlen(wether_jma[i].str) / 3; // 3byte文字しか無いため、固定で3で除算
    int x_pos;

    /* 左余白を8, 文字表示領域を192, 右余白を8 として、真ん中表示位置を決める */
    /* フォントサイズは 16 固定、最大12文字とする */
    str_len = 12 - str_len;
    x_pos = floor(str_len / 2) * 16;
    if(str_len % 2 == 1) {
        // 奇数
        x_pos += 8;
    }
    x_pos += 8;

    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(x_pos, 138);
    M5.Lcd.print(wether_jma[i].str);
}

void
WeatherJMA::drawTemperature()
{
    int i = 0, j, z, x_pos;
    char *temp_unit = "℃";

    String day = getWeatherDayJson();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, day);

    // 左右余白  20
    // 表示領域  60 で右詰めとする 
    M5.Lcd.setTextColor(RED);
    x_pos = 215 + 45;
    for(i = 0; !doc["temperature"]["range"][i].isNull(); i++) {
        if(String("max") == doc["temperature"]["range"][i]["centigrade"]) {
            String max_str = doc["temperature"]["range"][i]["content"];
            x_pos += (3 - max_str.length()) * 12;
            max_str += temp_unit;

            M5.Lcd.setCursor(x_pos, 90);
            M5.Lcd.print(max_str);
            break;
        }
    }

    M5.Lcd.drawFastVLine(265, 90, 20, LIGHTGREY);

    M5.Lcd.setTextColor(BLUE);
    x_pos = 215 - 15;
    for(i = 0; !doc["temperature"]["range"][i].isNull(); i++) {
        if(String("min") == doc["temperature"]["range"][i]["centigrade"]) {
            String min_str = doc["temperature"]["range"][i]["content"];
            x_pos += (3 - min_str.length()) * 12;
            min_str += temp_unit;

            M5.Lcd.setCursor(x_pos, 90);
            M5.Lcd.print(min_str);
            break;
        }
    }
}

void
WeatherJMA::drawRainfall()
{
    char *temp_unit = "%";
    int i = 0, sum = 0, x_pos;

    String day = getWeatherDayJson(), rain = "";
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, day);

    M5.Lcd.setTextColor(DARKGREY);
    
    for(i = 0; i < 4; i++){
      String msg = doc["rainfallchance"]["period"][i]["content"];
      sum += msg.toInt();
    }
    rain = String(sum/4);
    x_pos = 215 + 40;
    M5.Lcd.setCursor(x_pos, 115);
    rain += temp_unit;
    M5.Lcd.print(rain);
}

void
WeatherJMA::drawWeather(struct tm st_tm)
{
     char date[16] = {0};

    // 更新した日付で時刻情報を再取得する（標準のtime関数を使用すると、月またぎなどの考慮をしてくれる）
    //m_disp_time = mktime(&st_tm);
    //localtime_r(&m_disp_time, &st_tm);
    
    snprintf(date, sizeof(date), "%4d/%02d/%02d", st_tm.tm_year + 1900, st_tm.tm_mon + 1, st_tm.tm_mday);
    String str_date = date;
    String info = getWeatherInfoJson();

    DynamicJsonDocument doc(4096);
    deserializeJson(doc, info);

    int i;
    // 指定した日付のデータを検索する
    for(i = 0; !doc["info"][i].isNull(); i++) {
        if( str_date == doc["info"][i]["date"]) {
            Serial.printf("Found date. %s\n", date);
            break;
        }
    }
    // 日付のデータがなかった
    if(doc["info"][i].isNull()) {
        Serial.printf("Not found date. %s\n", date);
        return;
    }

    // 日付のデータがあった
    m_select_day_idx = i;

    M5.Lcd.clearDisplay(BLACK);

    M5.Lcd.loadFont(ff_16, SD);
  
    drawDay(st_tm);
    drawWeatherIcon();

    M5.Lcd.unloadFont();

    M5.Lcd.loadFont(ff_24, SD);

    drawTemperature();
    drawRainfall();

    M5.Lcd.unloadFont();

}

WeatherJMA weatherJMA;
