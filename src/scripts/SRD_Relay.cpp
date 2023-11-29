#include <Arduino.h>
#include "SRD_Relay.h"

SRD_Relay_class SRD_Relay_class_;

boolean state = 0;
int SRD_Relay_pin = 32;

void SRD_Relay_class::SRD_Relay_Init()
{
    pinMode(SRD_Relay_pin, OUTPUT);
    digitalWrite(SRD_Relay_pin, LOW);
}
void SRD_Relay_class::SRD_Relay_ON()
{
    digitalWrite(SRD_Relay_pin, HIGH);
    state = ON_STATE;
}
void SRD_Relay_class::SRD_Relay_OFF()
{
    digitalWrite(SRD_Relay_pin, LOW);
    state = OFF_STATE;
}
