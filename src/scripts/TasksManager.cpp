#include <Arduino.h>
#include "TasksManager.h"
#include "LCD_Manager.h"
#include "Test.h"
#include "GPSTiny.h"
#include "NFCPN532.h"
#include "TSP.h"
#include "SRD_Relay.h"
#include "MCIOS.h"
#include "LCD_update.h"
#include "WiFiCon.h"

// name spaces
using namespace Blink_Test_Task_namespace;
using namespace GPS_Neo6_namespace;
using namespace NFCPN532_namespace;
using namespace LCD_DISPLAY;
using namespace MCIOS_namespace;
using namespace WiFi_CON;

TaskHandle_t GPSTiny_handle     = NULL;
TaskHandle_t NFCPN532_handle    = NULL;
TaskHandle_t Test_handle        = NULL;
TaskHandle_t LCD_update         = NULL;

// classes
Blink_Test_Task_class    TasksManager_Blink_Test_Task_class;
GPS_Neo6_class                  TasksManager_GPS_Neo6_class;
NFCPN532_class                  TasksManager_NFCPN532_class;
LCD_DISPLAY_class                  TasksManager_LCD_DISPLAY_class;
SRD_Relay_class                TasksManager_SRD_Relay_class; 
LCD_update_class              TasksManager_LCD_update_class;
MCIOS_class                        TasksManager_MCIOS_class;
WiFiCon_class                    TasksManager_WiFiCon_class;


void Test_cpp(void *parameters)
{
    for (;;)
    {
        TasksManager_Blink_Test_Task_class.BlinkTask(ALLOW_CRITICAL);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void GSPTiny_cpp(void *parameters)
{
    for (;;)
    {
        TasksManager_GPS_Neo6_class.GPS_scan_TASK(ALLOW_CRITICAL);
             vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void NFCPN532_cpp(void *parameters)
{
    for (;;)
    {
        TasksManager_NFCPN532_class.NFCPN532_Task(ALLOW_CRITICAL);
             vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void LCD_update_cpp(void *parameters)
{
    for(;;)
    {
        TasksManager_LCD_update_class.LCD_UPDATE_USER();
            //if (TasksManager_WiFiCon_class.WIFI_IS)
            vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void pageselector(void *parameters)
{
    for (;;)
    {
        TasksManager_LCD_DISPLAY_class.Page_selector();
             vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

void sOfflineData(void *parameters)
{
    for (;;)
    {
        TasksManager_MCIOS_class.LSofflinedatareleasertask();
        TasksManager_WiFiCon_class.wifi_recon_after_disc();
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}

void TasksManager_class::TasksManager_init()
{
    TasksManager_SRD_Relay_class.SRD_Relay_Init();
    //TasksManager_Blink_Test_Task_class.Test_Task_init();
    TasksManager_GPS_Neo6_class.GPS_init();
    TasksManager_NFCPN532_class.NFCPN532_init();
    //wifi is already initated
}

void TasksManager_class::TasksManager_Create_Tasks()
{
    //xTaskCreate(Test_cpp, "sith", 1000, NULL, 1, &Test_handle);
    xTaskCreate(GSPTiny_cpp, "GPS scan loop", 15000, NULL, 1, &GPSTiny_handle);
    xTaskCreate(NFCPN532_cpp, "loop NFC scanning", 20000, NULL, 1, &NFCPN532_handle);
    xTaskCreate(LCD_update_cpp, "LCD Screen Updating", 15000, NULL, 1, &LCD_update);
    xTaskCreate(pageselector, "loop to click select page", 2000, NULL, 1, NULL);
    xTaskCreate(sOfflineData,"send the lost data",10000,NULL,1,NULL);
}

void TasksManager_class::TasksManager_Suspend_Tasks()
{
    vTaskSuspend(GPSTiny_handle);
    vTaskSuspend(NFCPN532_handle);
    //vTaskSuspend(Test_handle);
    vTaskSuspend(LCD_update);
}

void TasksManager_class::TasksManager_Resume_Tasks()
{
    vTaskResume(GPSTiny_handle);
    vTaskResume(NFCPN532_handle);
    //vTaskResume(Test_handle);
    vTaskResume(LCD_update);
}