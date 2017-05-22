#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <Fonts/SourceCodePro_Regular6pt7b.h>
#include <Fonts/SourceCodePro_Regular12pt7b.h>
#include <Fonts/SourceCodePro_Bold9pt7b.h>
#include <Fonts/SourceCodePro_Bold12pt7b.h>

#define TFT_CS  10
#define TFT_RST 9
#define TFT_DC  8

RTC_DS1307 rtc;
uint8_t lastMinute;
uint8_t lastDay;
char time[10];
char today[10];

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  Serial.begin(57600);
  if (!rtc.begin()) {
    Serial.println(F("No RTC!"));
    while(1);
  }
  if (!rtc.isrunning()) {
    Serial.println(F("RTC not running/set"));
    while(1);
  }
  Serial.println(F("RTC ready to rock!"));
  tft.initR(INITR_BLACKTAB);
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(3);
}

void loop() {
//  tft.fillScreen(ST7735_BLACK);
  DateTime now = rtc.now();
  if (lastDay != now.day()) {
    formattedDate(now).toCharArray(today, 10);
  }
  if (lastMinute != now.minute()) {
    formattedTime(now).toCharArray(time, 10);
    tft.fillScreen(ST7735_BLACK);
    drawMainView();
    drawSession();
    lastMinute = now.minute();
  }
}

void display(int x, int y, char* text) {
  int16_t x1, y1;
  uint16_t w, h;

  tft.getTextBounds(text, 0, 0,&x1, &y1, &w, &h);
  
  tft.setCursor(x - w/2, y + h/2);
  tft.setTextColor(ST7735_WHITE);
  tft.print(text);
}

void drawSession() {
  drawStartButton();
}

void drawCurrentCounter(uint16_t color) {
  tft.fillCircle(0,0,40,color);
}

void drawStartButton() {
  uint8_t r = 36;
  tft.drawCircle(50, 50, r, ST7735_WHITE);
  tft.drawCircle(50, 50, r - 1, ST7735_WHITE);
  tft.setFont(&SourceCodePro_Bold9pt7b);
  display(50, 50, "Start");
  tft.setFont(&SourceCodePro_Regular6pt7b);
  display(50, 92, "begin a new");
  display(50, 108, "work session");
}

void drawPlayButton() {
  
}

void drawPauseButton() {
  
}

void drawCancelButton() {
  
}

void drawSettingsButton() {
  
}

String formattedTime(DateTime now) {
  String fTime;
  uint8_t hr;
  
 if (now.hour() == 0) {
    hr = 12;
  } else if (now.hour() < 12 ) {
    hr = now.hour();
  } else {
    hr = now.hour() - 12;
  }
  if (hr < 10) {
    fTime += "0";
  }
  fTime += hr;
  fTime += ":";
  if (now.minute() < 10) {
    fTime += "0";
  }
  fTime += now.minute();
  if (now.hour() < 12) {
    fTime += " AM";
  } else {
    fTime += " PM";
  }
  return fTime;
}

String formattedDate(DateTime date) {
  String fDate;
  if (date.month() < 10) {
    fDate += "0";
  }
  fDate += date.month();
  fDate += "/";
  if (date.day() < 10) {
    fDate += "0";
  }
  fDate += date.day();
  fDate += "/";
  fDate += (date.year() - 2000);
  return fDate;
}

void drawMainView() {
  tft.setFont(&SourceCodePro_Regular6pt7b);
  display(124,16,"TODAY");
  tft.setFont();
  display(124,20, "4 Sessions");
  tft.setFont(&SourceCodePro_Regular6pt7b);
  display(124,48, time);
  display(124,62, today);
  tft.drawFastHLine(104,38,40,ST7735_WHITE);
}
