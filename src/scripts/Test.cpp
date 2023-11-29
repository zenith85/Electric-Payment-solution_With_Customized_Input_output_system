
#include <Arduino.h>
#include "Test.h"

using namespace Blink_Test_Task_namespace;

void Blink_Test_Task_class::Test_Task_init()
{
    pinMode(15, OUTPUT);
}

void Blink_Test_Task_class::BlinkTask(boolean critical_allowed)
{
    if (critical_allowed)
    {
        digitalWrite(15, LOW);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        digitalWrite(15, HIGH);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        
    }
    else
    {
        digitalWrite(15, HIGH);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        
        // different task like same task without display?
    }

}