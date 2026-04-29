#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 23
#define LED_COUNT 1

Adafruit_NeoPixel rgb(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// 表示したい色のリスト (R, G, B)
// 0-255で指定しますが、眩しすぎないよう最大50に抑えています
int color_list[8][3] = {
    {1, 0, 0},   // 赤
    {1, 1, 0},   // 黄
    {0, 1, 0},   // 緑
    {0, 1, 1},   // 水色
    {0, 0, 1},   // 青
    {1, 0, 1},   // 紫
    {1, 1, 1},   // 白
    {0, 0, 0}    // 消灯
};

int current_color_index = 0;

void setup() {
  pinMode(25, OUTPUT); // YD-RP2040の青色LED
  pinMode(23, OUTPUT); // RGB LEDの電源/信号線（一応）
  rgb.begin();       // NeoPixel 初期化
  rgb.setBrightness(50); // 明るさ（0〜255）
}

void RGB_LED_OnOff() {
  // RGB LEDの色を更新
  rgb.setPixelColor(0, rgb.Color(
          color_list[current_color_index][0]*255, 
          color_list[current_color_index][1]*255, 
          color_list[current_color_index][2]*255
  ));
  rgb.show();
  current_color_index = (current_color_index + 1) % 8; // 色のインデックスを更新
  delay(500); // 500ms待機
  rgb.setPixelColor(0, rgb.Color(0, 0, 0));
  rgb.show();
}

void loop() {
  digitalWrite(23, HIGH);
  delay(100);
  digitalWrite(23, LOW);
  delay(100);

  // RGB LEDの色を更新
  RGB_LED_OnOff();
}