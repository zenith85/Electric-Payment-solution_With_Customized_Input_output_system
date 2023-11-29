#include <Wire.h>
#include <TinyGPS++.h>
#include <Arduino.h>
#include <HardwareSerial.h>
#include "GPSTiny.h"
#include "LCD_Manager.h"
#include "DEF_TECH_INT.h"

HardwareSerial SerialGPS(1);
TinyGPSPlus gps;

using namespace GPS_Neo6_namespace;
using namespace LCD_DISPLAY;

//Display_gps Display_Obj_;
LCD_DISPLAY_class LCD_DISPLAY__;

void GPS_Neo6_class::GPS_init()
{
    SerialGPS.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void GPS_Neo6_class::GPS_scan_TASK(boolean critical_allowed)
{

    for (unsigned long start = millis(); millis() - start < 500;)
    {
        while (SerialGPS.available() > 0)
        {
            if (gps.encode(SerialGPS.read()))
            {                
                if (gps.location.isValid())
                {
                    // Take semaphore rights to publish on lcd
                    if (critical_allowed)
                    {                        
                        LCD_DISPLAY__.TS_Display("Lat: "+String(gps.location.lat(), 6), THIRDROW,GPS_PAGE);
                        LCD_DISPLAY__.TS_Display("Lng: "+String(gps.location.lng(), 6), FOURTHROW,GPS_PAGE);
                    }
                    vTaskDelay(1000 / portTICK_PERIOD_MS);
                }
                else
                {
                    if (critical_allowed)
                    {
                        LCD_DISPLAY__.TS_Display("   GPS Satellites   ", THIRDROW,GPS_PAGE);
                        vTaskDelay(500 / portTICK_PERIOD_MS);
                        LCD_DISPLAY__.TS_Display("                    ", FOURTHROW,GPS_PAGE);
                        vTaskDelay(500 / portTICK_PERIOD_MS);
                        LCD_DISPLAY__.TS_Display("  Allocating.....   ", FOURTHROW,GPS_PAGE);                      
                    }
                   // vTaskDelay(1000 / portTICK_PERIOD_MS);
                }
                 vTaskDelay(500 / portTICK_PERIOD_MS);
            }
            // Serial.print("gps testing");
        }
        {
            LCD_DISPLAY__.TS_Display("  GPS Chip error!!  ", THIRDROW,GPS_PAGE);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            LCD_DISPLAY__.TS_Display("No GPS Serial data!!", FOURTHROW,GPS_PAGE);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
       
    }
}
