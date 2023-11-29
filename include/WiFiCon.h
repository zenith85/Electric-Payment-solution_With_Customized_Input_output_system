#ifndef WIFICON_H
#define WIFICON_H

namespace WiFi_CON
{
    class WiFiCon_class
    {
    public:                
        void WiFiCon_init(bool dhcp,const char* ssid,const char* psswrd,const char* ip,const char* subnet,const char* defgw,const char* dns);
        boolean WifiCon_Scan_Task();
        void Net_state();
        boolean pingdest(String,int count);
        boolean wificonnected();
        void wifi_recon_after_disc();
        //void WifiCon_LCD_Update();        
    private:
        /* data */
    };
}

#endif