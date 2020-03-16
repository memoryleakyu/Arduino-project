// NeoPiaXel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPiaXel library

#include <FastLED.h>

#include "SparkFunLSM6DS3.h"
#include "Wire.h"
#include "math.h"

// Which pin on the Arduino is connected to the NeoLEDS?
// On a Trinket or Gemma we suggest changing this to 1
#define NUM_LEDS 30
#define DATA_PIN 6
CRGB leds[NUM_LEDS];
LSM6DS3 myIMU(I2C_MODE, 0X6A); //I2C device address 0aX6A
float aX, aY, aZ, gX, gY, gZ;
int R, G, B;
int brightness;
int strength = 1;
int maxBright = 2;
int frequency = 10;
int maXAccel, secAccel;

void setup()
{
    Serial.begin(9600);
    myIMU.begin();
    FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
}

void loop()
{
    aX = abs(myIMU.readFloatAccelX());
    aY = abs(myIMU.readFloatAccelY());
    aZ = abs(myIMU.readFloatAccelZ());

    if (aX >= aY && aX >= aZ)
    {
        maXAccel = aX;
    }

    if (aY >= aX && aY >= aZ)
    {
        maXAccel = aY;
    }

    if (aZ >= aY && aZ >= aX)
    {
        maXAccel = aZ;
    }
    if (maXAccel >= strength)
    {
        brightness = accelToBright(maXAccel);
        FastLED.setBrightness(brightness);
            forward();
            backward();
    }
}

void forward()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        gX = abs(myIMU.readFloatGyroX());
        gY = abs(myIMU.readFloatGyroY());
        gZ = abs(myIMU.readFloatGyroZ());
        R = gyroToRGB(gX);
        G = gyroToRGB(gY);
        B = gyroToRGB(gZ);
        leds[i].setRGB(R, G, B);
        FastLED.show(); // This sends the updated piaXel color to the hardware.
        fadeall();
        delay(frequency);
    }
}

void backward()
{
    for (int i = NUM_LEDS - 1; i >=0 ; i--)
    {
        gX = abs(myIMU.readFloatGyroX());
        gY = abs(myIMU.readFloatGyroY());
        gZ = abs(myIMU.readFloatGyroZ());
        R = gyroToRGB(gX);
        G = gyroToRGB(gY);
        B = gyroToRGB(gZ);
        leds[i].setRGB(R, G, B);
        FastLED.show(); // This sends the updated piaXel color to the hardware.
        fadeall();
        delay(frequency);
    }
}

void fadeall()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i].nscale8(250);
    }
}

int accelToBright(float accel_1)
{
    float bright;
    if (accel_1 < maxBright)
    {
        bright = accel_1 / maxBright * 255;
    }
    if (floor(accel_1) >= maxBright)
        bright = 255;
    return floor(bright);
}

int gyroToRGB(float gyro)
{
    float tempRGB = floor(gyro / 300 * 255);
    if (tempRGB >= 255)
        return 255;
    else
        return tempRGB;
}
