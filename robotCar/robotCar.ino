//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//
// This sketch is a good place to start if you're just getting started with
// Pixy and Arduino.  This program simply prints the detected object blocks
// (including color codes) through the serial console.  It uses the Arduino's
// ICSP SPI port.  For more information go here:
//
// https://docs.pixycam.com/wiki/doku.php?id=wiki:v2:hooking_up_pixy_to_a_microcontroller_-28like_an_arduino-29
//

#include <Pixy2.h>
#include <Servo.h>
#include "CytronMotorDriver.h"

// Configure the motor driver.
CytronMD motor(PWM_DIR, 3, 2); // PWM = Pin 4, DIR = Pin 3.

Servo myservo;
// This is the main Pixy object
Pixy2 pixy;

void setup()
{
    Serial.begin(115200);
    Serial.print("Starting...\n");
    myservo.attach(6);
    pixy.init();
    pixy.changeProg("color_connected_components");
}

void loop()
{
    float swingOffset;
    // grab blocks!
    pixy.ccc.getBlocks();

    // If there are detect blocks, print them!
    if (pixy.ccc.numBlocks)
    {
        swingOffset = (int32_t)pixy.frameWidth / 2 - (int32_t)pixy.ccc.blocks[0].m_x;
        float angle = (abs(swingOffset - 150) / 300 * 90) + 25;
        float area = (int32_t)pixy.ccc.blocks[0].m_width * (int32_t)pixy.ccc.blocks[0].m_height;

        //Serial.print(area);
        Serial.print("\t");
        myservo.write(angle);
        if (area <= 500)
        {
            Serial.println("forward");
            motor.setSpeed(128);
            delay(10);
        }
        else if (area >= 8000)
        {
            Serial.println("backward");
            motor.setSpeed(-128);
            delay(10);
        }
        else
            Serial.println("stop");
            motor.setSpeed(0);
        delay(10);
    }
    else{
        Serial.println("stop");
        motor.setSpeed(0);
        myservo.write(70);
    }
        
}
