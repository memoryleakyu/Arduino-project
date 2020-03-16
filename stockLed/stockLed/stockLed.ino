#include <FastLED.h>

#define NUM_LEDS 30
#define DATA_PIN 6
CRGB leds[NUM_LEDS];
String dataStr;      // a variable to read incoming serial data into
int data;
int range;
void setup()
{
  Serial.begin(9600);
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(30);
  FastLED.show();
}
void loop() {
  if (Serial.available() > 0) {
    FastLED.clear();
    dataStr = Serial.readString();
    data = dataStr.toInt();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (data == 30 ) buy();
    if (data == -30) sell();
    if (data <= 0) {
      for (int i = 0 ; i <= abs(data) - 1 ; i++)
      {
        leds[i].setRGB(0, 255, 0);
        FastLED.show();
        delay(10);
      }
    }
    if (data > 0) {
      for (int i = 0 ; i <= abs(data) - 1 ; i++)
      {
        leds[i].setRGB(255, 0, 0);
        FastLED.show();
        delay(10);
      }
    }
  }
}

void sell()
{
  for (int i = NUM_LEDS - 1; i >= 0 ; i--)
  {
    leds[i].setRGB(0, 255, 0);
    FastLED.show(); // This sends the updated piaXel color to the hardware.
    fadeall();
    delay(10);
  }
}

void buy() {
  for (int i = 0; i < NUM_LEDS; i++)
  {

    leds[i].setRGB(255, 0, 0);
    FastLED.show(); // This sends the updated piaXel color to the hardware.
    fadeall();
    delay(10);
  }
}

void fadeall()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i].nscale8(250);
  }
}
