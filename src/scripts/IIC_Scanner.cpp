#include <Arduino.h>
#include <Wire.h>
#include "IIC_Scanner.h"

using namespace i2cscanner;

void i2cscanner_class::IIC_Scan()
{
    Wire.begin();
    byte error, address;
    int I2CDevices;

    Serial.println("Scanning for I2C Devices…");

    I2CDevices = 0;
    for (address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            if (address < 16)
            {
                Serial.print("0");
            }
            Serial.print(address, HEX);
            Serial.println(" !");

            I2CDevices++;
        }
        else if (error == 4)
        {
            Serial.print("Unknown error at address 0x");
            if (address < 16)
            {
                Serial.print("0");
            }
            Serial.println(address, HEX);
        }
    }
    if (I2CDevices == 0)
    {
        Serial.println("No I2C devices found\n");
    }
    else
    {
        Serial.println("****\n");
    }    
}