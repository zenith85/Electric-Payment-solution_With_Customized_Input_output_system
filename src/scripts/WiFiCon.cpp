/*
 *  This sketch demonstrates how to scan WiFi networks.
 *  The API is almost the same as with the WiFi Shield library,
 *  the most obvious difference being the different file you need to include:
 */
#include "WiFi.h"
#include "WiFiCon.h"
#include <ESP32Ping.h>
#include "LCD_Manager.h"
#include "MCIOS.h"

using namespace WiFi_CON;
using namespace LCD_DISPLAY;
using namespace MCIOS_namespace;

// IPAddress ipp(192,168,45,149);    
// IPAddress smask(255,255,255,0);
// IPAddress gww(192,168,45,1);
// IPAddress dnsp(8,8,8,8);  

LCD_DISPLAY_class WiFi_CON_LCD1602_class;
MCIOS_class WiFi_CON_MCIOS_class;
boolean wifiinited=false;

void WiFiCon_class::WiFiCon_init(bool dhcp, const char *ssid, const char *passwd, const char *ip, const char *subnet, const char *defgw, const char *dns)
{
    if (ssid != "")
    {
        WiFi.mode(WIFI_STA);
        //WiFi.setSleep(WIFI_PS_NONE);
        WiFi.begin(ssid, passwd);
        Serial.println(ssid);
        Serial.println(passwd);
        unsigned long startAttemptTime = millis();
        while (WiFi.status()!=WL_CONNECTED && millis() - startAttemptTime < 20000)
        {
            Serial.print(".");
            vTaskDelay(100/portTICK_PERIOD_MS);
        }
        if (WiFi.status()!=WL_CONNECTED)
        {
            Serial.println("Failed");            
        }else{
            Serial.print("Connected!");
            Serial.println(WiFi.localIP());
        }
        if (WiFi.setAutoConnect(true)){Serial.println("wifi is in auto-connect mode");};
        //WiFi.setAutoConnect(true);
    }
  
    // WiFi.config(ipp,gww,smask,dnsp);
}

void WiFiCon_class::Net_state()
{        
    String state;
    WiFi.status()!=WL_CONNECTED?state="Not-Connected":state="Connected";
    Serial.println("Network status:" + state);
    Serial.println("Network SSID:" + WiFi.SSID());
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("ESP Mac Address: ");
    Serial.println(WiFi.macAddress());
    Serial.print("Subnet Mask: ");
    Serial.println(WiFi.subnetMask());
    Serial.print("Gateway IP: ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("DNS: ");
    Serial.println(WiFi.dnsIP());
}

boolean WiFiCon_class::WifiCon_Scan_Task()
{    
    // WiFi.scanNetworks will return the number of networks found
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(200);
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0)
    {
        Serial.println("no networks found");
    }
    else
    {
        Serial.print(n);
        Serial.println(" Networks Available");
        Serial.println("");
        for (int i = 0; i < n; ++i)
        {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print("      (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(" dBi)");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "Open" : "Encrypted! ");
            delay(10); // we used delay not vtaskdelay because we will freeze the whole processor until the scan mission is finished
        }
    }
    Serial.println("");
    return true;
    // Wait a bit before scanning again
    vTaskDelay(5000 / portTICK_PERIOD_MS);
}

boolean WiFiCon_class::wificonnected()
{
    if (WiFi.status()!=WL_CONNECTED){return false;}else{return true;}
}


boolean WiFiCon_class::pingdest(String destination,int count)
{
    bool success = Ping.ping(destination.c_str(),count);
    return success;
}

void WiFiCon_class::wifi_recon_after_disc()
{
    //this class has been debricated due to that WiFi 2.0.x has the ability to reconnect WiFi.setAutoReconnect(true)
    if (!wificonnected())
    {        
        WiFi.reconnect();
    }    
}