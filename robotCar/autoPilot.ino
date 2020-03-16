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

#include <Pixy2.h>
#include <Servo.h>
#include "CytronMotorDriver.h"

// Configure the motor driver.
CytronMD motor(PWM_DIR, 3, 2); // PWM = Pin 4, DIR = Pin 3.

Servo myservo;
// This is the main Pixy object
Pixy2 pixy;
int carSpeed;
void setup()
{
    Serial.begin(115200);
    myservo.attach(6);

    pixy.init();
    // change to the line_tracking program.  Note, changeProg can use partial strings, so for example,
    // you can change to the line_tracking program by calling changeProg("line") instead of the whole
    // string changeProg("line_tracking")
    Serial.println(pixy.changeProg("line"));
}

void loop()
{
    pixy.line.getAllFeatures();

    if (pixy.line.barcodes)
    {
        int code = pixy.line.barcodes[0].m_code;
        switch (code)
        {
        case 0:
            carSpeed = 0;
            myservo.write(70);
            break;

        case 1:
            motor.setSpeed(40);
            myservo.write(115);
            delay(3600);
            break;

        case 3:
            motor.setSpeed(42);
            myservo.write(25);
            delay(1800);
            break;

        case 4:
            carSpeed = 32;
            myservo.write(70);
            break;

        default:
            break;
        }
    }
    motor.setSpeed(carSpeed);
    myservo.write(70);
}