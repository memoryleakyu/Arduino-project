
#include <Pixy2.h>
#include <Servo.h>
#include "CytronMotorDriver.h"

// Configure the motor driver.
CytronMD motor(PWM_DIR, 3, 2); // PWM = Pin 4, DIR = Pin 3.

Servo myservo;
// This is the main Pixy object
Pixy2 pixy;
int carSpeed = 0;
void setup()
{
    Serial.begin(115200);
    myservo.attach(6);
    myservo.write(70);

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
        case 1:
            carSpeed = 40;
            myservo.write(70);
            break;

        case 2:
            motor.setSpeed(35);
            myservo.write(25);
            delay(1800);
            break;

        case 3:
            motor.setSpeed(35);
            myservo.write(115);
            delay(1000);
            myservo.write(70);
            break;

        case 4:
            motor.setSpeed(40);
            myservo.write(115);
            delay(3600);
            break;

           
        case 5:
            carSpeed = 0;
            myservo.write(70);
            break;

        default:
            break;
        }
    }
    motor.setSpeed(carSpeed);
    myservo.write(70);
}