#include <FastLED.h>

#include "SparkFunLSM6DS3.h"
#include "Wire.h"
#include "math.h"

// Which pin on the Arduino is connected to the NeoLEDS?
// On a Trinket or Gemma we suggest changing this to 1
#define NUM_LEDS 30
#define DATA_PIN 6
CRGB leds[NUM_LEDS];

int r, g, b;

void setup()
{
  Serial.begin(9600);
  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(100);
}

void loop()
{
  int arr[NUM_LEDS];
  for (int j = 0; j < NUM_LEDS; j++)
  {
    int i = random(NUM_LEDS);
    arr[j] = i;
    setColor(i, j);
  }
  quickSort(arr, 0, 29);
      exit(0);
}

void quickSort(int num[], int l, int r)
{
  if (l >= r) //先检查左右条件
    return;
  int m = l, n = r, x = num[l];
  while (m < n)
  {
    while (m < n && num[n] >= x) //从右向左找到第一个小于x的
      n--;
    if (m < n)
    {
      setColor(num[n], m);
      num[m++] = num[n]; //填坑之后i++
    }

    while (m < n && num[m] <= x) //从左向右找第一个大于x的数
      m++;
    if (m < n)
    {
      setColor(num[m], n);
      num[n--] = num[m];
    }
  }
  num[m] = x;               //把最开始取出来的x放到i处
  setColor(x, m);
  quickSort(num, l, m - 1); //以i为中间值，分左右两部分递归调用
  quickSort(num, m + 1, r);
}
void setColor(int color, int led)
{
  if (color < NUM_LEDS / 3)
  {
    r = 255;
    g = floor(250 * 3 * color / NUM_LEDS);
    b = 0;
  }
  else if (color < NUM_LEDS / 2)
  {
    r = floor(750 - color * (250 * 6 / NUM_LEDS));
    g = 255;
    b = 0;
  }
  else if (color < NUM_LEDS * 2 / 3)
  {
    r = 0;
    g = 255;
    b = floor(color * (250 * 6 / NUM_LEDS) - 750);
  }
  else if (color < NUM_LEDS * 5 / 6)
  {
    r = 0;
    g = floor(1250 - color * (250 * 6 / NUM_LEDS));
    b = 255;
  }
  else
  {
    r = floor(150 * color * (6 / NUM_LEDS) - 750);
    g = 0;
    b = 255;
  }
  leds[led].setRGB(g, r, b);
  FastLED.show(); // This sends the updated piaXel color to the hardware.
  delay(30);
}
