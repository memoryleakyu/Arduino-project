#include <Grove_LED_Bar.h>

Grove_LED_Bar bar(6, 5, 1, LED_BAR_10); // Clock pin, Data pin, Orientation
int leds = 0;
int dropTime = 0;
int ticker = 0;
void setup() {
    Serial.begin(9600);
    bar.begin();
}

void loop() {
    // Walk through the levels
    int lightValue = analogRead(A0);

    if (lightValue <= 250) {
        dropTime += 50;
    } else
    {
        Serial.println(dropTime);
        dropTime = 0;
    }
    leds = dropTime /1000;
    bar.setLevel(leds);
    if ( leds >= 10)
    {
        Serial.println("Nicedone!");
        dropTime = 0;
    }
    
    delay(50);
}