#include <Arduino.h>
//#include "scripts/Test.h"
#include "Test.h"
#include "LCD_Manager.h"
#include "GPSTiny.h"
#include <SPI.h>
#include <Adafruit_SPIDevice.h>
#include <Wire.h>
#include "NFCPN532.h"
#include "TasksManager.h"
#include "WiFiCon.h"
#include "MCIOS.h"
#include "WEBSOCK.h"
#include "ChargingPort.h"

using namespace LCD_DISPLAY;
using namespace NFCPN532_namespace;
using namespace WiFi_CON;
using namespace MCIOS_namespace;

LCD_DISPLAY_class LCD_DISPLAY_;
WiFiCon_class WiFiCon_class_;
NFCPN532_class NFCPN532_class_;
TasksManager_class TM_;
MCIOS_class MCIOS_class_;
WEBSOCK_Class RESTAPI_class_;
ChargingPort_class ChargingPort_class_;

void setup()
{  
  // put your setup code here, to run once:
  Serial.begin(9600);
  ChargingPort_class_.CP_init();
  MCIOS_class_.BANNER();
  LCD_DISPLAY_.LCD_init();
  MCIOS_class_.INITIATEMCIOS();  
  TM_.TasksManager_init();
  TM_.TasksManager_Create_Tasks();  
  vTaskDelay(100 / portTICK_PERIOD_MS);

}

void loop()
{  
  // put your main code here, to run repeatedly:
  vTaskDelay(10 / portTICK_PERIOD_MS);
  MCIOS_class_.SERIALINPUT();
}