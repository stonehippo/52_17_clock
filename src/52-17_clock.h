#include <Arduino.h>
#include <RTClib.h>

void display(int x, int y, char* text);
void drawSession();
void drawCurrentCounter(uint16_t color);
void drawStartButton();
String formattedTime(DateTime now);
String formattedDate(DateTime date);
void drawMainView();
