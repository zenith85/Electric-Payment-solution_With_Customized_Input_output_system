#include <Arduino.h>
#include "TSP.h"
#include "LCD_Manager.h"
#include "TasksManager.h"

using namespace TSP_namespace;
using namespace LCD_DISPLAY;

LCD_DISPLAY_class TSP_to_LCD;
TaskHandle_t TSP_Task_counter_handle = NULL; // this line is to turn the TASK off when the count is finished
TimeDigitView TDV = {.s_1 = 0, .s_2 = 0, .m_1 = 0, .m_2 = 0, .h_1 = 0, .h_2 = 0};
int TSP_class::total_time = 0;
String TSP_class::msg = "";

void TSP_Task_counter(void *parameters)
{
    for (;;)
    {
        TSP_class::total_time++;
        TDV.s_1++;
        if (TDV.s_1 > 9)
        {
            TDV.s_2++;
            TDV.s_1 = 0;
        }
        if (TDV.s_2 > 5)
        {
            TDV.m_1++;
            TDV.s_2 = 0;
        }
        if (TDV.m_1 > 9)
        {
            TDV.m_2++;
            TDV.m_1 = 0;
        }
        if (TDV.m_2 > 5)
        {
            TDV.h_1++;
            TDV.m_2 = 0;
        }
        if (TDV.h_1 > 9)
        {
            TDV.h_2++;
            TDV.h_1 = 0;
        }
        if (TDV.h_2 > 5)
        {
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        TSP_to_LCD.TS_Display("Timer : " + String(TDV.h_2) + String(TDV.h_1) + ":" + String(TDV.m_2) + String(TDV.m_1) + ":" + String(TDV.s_2) + String(TDV.s_1), THIRDROW, NFC_PAGE);
        // TSP_to_LCD.TS_Display("Timer : " + String(TDV.h_2) + String(TDV.h_1) + ":" + String(TDV.m_2) + String(TDV.m_1) + ":" + String(TDV.s_2) + String(TDV.s_1), THIRDROW,state);
        TSP_class::msg = "Timer : " + String(TDV.h_2) + String(TDV.h_1) + ":" + String(TDV.m_2) + String(TDV.m_1) + ":" + String(TDV.s_2) + String(TDV.s_1);
        // Serial.println("Time : " + String(TDV.h_2) + String(TDV.h_1) + ":" + String(TDV.m_2) + String(TDV.m_1) + ":" + String(TDV.s_2) + String(TDV.s_1));
    }
}

int TSP_class::TSP_Get_Time()
{
    return TSP_class::total_time;
}

void TSP_class::TSP_Task(TimerTask TimerTask_)
{
    switch (TimerTask_.status)
    {
    case TSP_START:
        xTaskCreate(
            TSP_Task_counter,
            TimerTask_.UID,
            15000,
            NULL,
            1,
            &TSP_Task_counter_handle);
        break; // optional
    case TSP_END:
        // kill the task and return the total time and reset values
        vTaskDelete(TSP_Task_counter_handle);
        TDV = {.s_1 = 0, .s_2 = 0, .m_1 = 0, .m_2 = 0, .h_1 = 0, .h_2 = 0};
        TSP_class::total_time = 0;
        // return values of count
        TSP_to_LCD.TS_Display("                    ", SECONDROW, NFC_PAGE);
        TSP_class::msg = "                    ";
        break; // optional
    case TSP_AUTH_ERROR:
        Serial.println("TSP_error_register");        
        break;
    // you can have any number of case statements.
    default: // Optional
    break;
    }


}