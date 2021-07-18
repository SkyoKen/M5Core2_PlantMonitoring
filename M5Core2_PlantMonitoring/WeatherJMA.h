#ifndef WEATHER_JMA_H
#define WEATHER_JMA_H

#include <M5Core2.h>
#include "time.h"
#include <ArduinoJson.h>

typedef struct {
  const char * str;
  const char * fname;
} WEATHER_JMA_DEF;

typedef enum {
  WEATHER_DAY_NONE = -1,
  WEATHER_TODAY = 0,
  WEATHER_TOMORROW,
  WEATEHR_DAY_AFTER_TOMORROW
} WEATHER_DAY;

class WeatherJMA {
private:
  String m_URL;
  int m_select_day_idx;
  time_t m_disp_time;

  String Jsonp2Json(String jsonString);

  String getWeatherInfoJson();
  String getWeatherDayJson();


  void drawDay(struct tm st_tm);
  void drawWeatherIcon();
  void drawTemperature();
  void drawRainfall();

public:
  WeatherJMA();

  bool getWeather();
  void drawWeather(struct tm st_tm);

};

extern WeatherJMA weatherJMA;

#endif // WEATHER_JMA_H
