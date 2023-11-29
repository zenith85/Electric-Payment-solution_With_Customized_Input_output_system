#include <Wire.h>
#include <SPI.h>
#include <Arduino.h>
#include "DEF_TECH_INT.h"
#include "ChargingPort.h"


void ChargingPort_class::CP_init()
{
    pinMode(chargePin, INPUT);
}

bool ChargingPort_class::ChargingPort(/* args */)
{
    //Serial.print("Charging port is called");
    if (digitalRead(chargePin)==HIGH){return true;}else{return false;}    
}

