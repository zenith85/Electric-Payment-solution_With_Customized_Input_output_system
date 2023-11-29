#include <Arduino.h>
#include "syslog.h"


Device_ICS *Device_ICS_;
void syslog_init()
{
   //currenlty is not implemented
}

Device_ICS * getsyslog()
{
    return Device_ICS_;
}

void setsyslog(DeviceName dn, Device_ICS s)
{
    switch(dn)
    {
        case(NFCSENSOR):
            Serial.println("legal call");
        break;
        case(OLEDLCD):
            Serial.println("legal call");
        break;
        case(GPS):
            Serial.println("legal call");
        break;
        case(MEMORYLOAD):
            Serial.println("legal call");
        break;
        default:
            Serial.println("illegal call");
        break;
    }    
}