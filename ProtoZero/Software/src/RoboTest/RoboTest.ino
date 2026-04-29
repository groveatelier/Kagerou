#include <FastLED.h>

#define LED_PIN 23
#define NUM_LEDS 1

CRGB leds[NUM_LEDS];

void setup() {
    Serial.begin(115200);
    Serial.setTimeout(3000);  // タイムアウトを3秒に変更
    pinMode(25, OUTPUT);

    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(50);

    // 初期状態は消灯
    leds[0] = CRGB::Black;
    FastLED.show();
}

void loop() {
    if (Serial.available() > 0) {
        String cmd = Serial.readStringUntil('\n');
        cmd.trim();  // 改行や空白を除去

        Serial.println("CMD: " + cmd);  // 受信したコマンドを表示

        if (cmd.equalsIgnoreCase("RED")) {
            leds[0] = CRGB::Red;
        } else if (cmd.equalsIgnoreCase("GREEN")) {
            leds[0] = CRGB::Green;
        } else if (cmd.equalsIgnoreCase("BLUE")) {
            leds[0] = CRGB::Blue;
        } else if (cmd.equalsIgnoreCase("WHITE")) {
            leds[0] = CRGB::White;
        } else if (cmd.equalsIgnoreCase("OFF")) {
            leds[0] = CRGB::Black;
        } else {
            leds[0] = CRGB::DarkGreen;
            Serial.println("Unknown command");
        }

        FastLED.show();
    }
  
  digitalWrite(25, HIGH);
  delay(300);
  digitalWrite(25, LOW);
  delay(700);
}


//--------------------------------------------------
/*
#include <FastLED.h>

#define LED_PIN 23
#define NUM_LEDS 1

CRGB leds[NUM_LEDS];

void setup() {
    Serial.begin(115200);
    pinMode(25, OUTPUT);

    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(50);

    leds[0] = CRGB::Blue;
    FastLED.show();
}

void loop() {
  digitalWrite(25, HIGH);
  delay(300);
  digitalWrite(25, LOW);
  delay(300);

  Serial.println("alive");
}
*/
//--------------------------------------------------
/*
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 23
#define LED_COUNT 1

Adafruit_NeoPixel rgb(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  rgb.begin();
  rgb.setBrightness(50);
  rgb.setPixelColor(0, rgb.Color(255, 100, 50)); // 暖色
  rgb.show();
}

void loop() {}
*/
//--------------------------------------------------
