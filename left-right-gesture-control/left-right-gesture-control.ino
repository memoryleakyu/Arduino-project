#include <Wire.h>
#include <Math.h>
#include "Grove_Human_Presence_Sensor.h"

AK9753 movementSensor;

float ir2, ir4;       //variables to store your sensor data
float diff24;         //variable to store the difference between the left and right sensor
float tempDiff = 0.0; //variable to store the current diff24. 
                      //This variable is used to test whether the diff24 is going up or going down.
float temp;
float mov;            //variable to store the difference of 2 diff24

void setup()  //set up movement sensor
{
    Serial.begin(9600);

    Wire.begin();

    //Turn on sensor
    if (movementSensor.initialize() == false)
    {
        Serial.println("Device not found. Check wiring.");
        while (1)
            ;
    }
}

void loop()
{

    if (movementSensor.dataReady())
    {
        ir2 = movementSensor.getIR2(); 
        ir4 = movementSensor.getIR4();       //get sensor data
        temp = movementSensor.getTMP();

        movementSensor.startNextSample();

        diff24 = ir2 - ir4;
        Serial.println(diff24);
        float mov = diff24 - tempDiff; 
        if (abs(mov) > 60)                   // Determine whether there is a movement
        {
            if (mov > 60)                    //Determine the movement direction
            {
                Serial.println("right");
            }
            if (mov < -60)
            {
                Serial.println("left");
            }
            delay(500);                       //We don't want to trigger multiple signals during one hand waving.
                                              //So once the detection was triggered we will delay the sensor reading data for 0.5 second.
            if (movementSensor.dataReady())   //As the sensor is delayed, so the diff24 value is still the one we calculated 0.5 seconds before.
                                              //So we use the following code to refresh the diff24 data.
            {
                ir2 = movementSensor.getIR2();
                ir4 = movementSensor.getIR4();
                temp = movementSensor.getTMP();

                movementSensor.startNextSample();
                diff24 = ir2 - ir4;
            }
            tempDiff = diff24;
        }
        delay(10);
    }
}
