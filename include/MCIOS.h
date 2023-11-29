#ifndef MCIOS_H
#define MCIOS_H

// command code selector
enum COMMAND_SELECTOR
{
    BASIC_SEL = 0,
    WIFI_SEL = 1,
    UNIT_SEL = 2
};

namespace MCIOS_namespace
{
    class MCIOS_class
    {
    public:
        void INITIATEMCIOS();           void INITIATEMEMORY();        
        void INITIATEWIFI();            void BANNER();        
        void LOADCONFIG();              void UPDATEDISPLAY();        
        void ZEROIS();                  void ERASEMEMORY();        
        void SHOWMEMORY();              void WRITEMEMORY();                
        void SERIALINPUT();             void INITIATEWEBSOCK();
        void LSofflinedatareleasertask();
        String READSTRINGFMEM(int _address);
        void BUZZER(int period, int frequency, int times);
        void WRITESTRINGFMEM(int _address, String _str);    bool LSrecorder(boolean LSavailable, String CARDUID, String TOTALTIME);
        
        int codnav;
        String inputread();
        // setters
        void setBuzzer(boolean val);                            bool getBuzzer();
        void setCI_en();                                        bool getCI_en();
        void setssid(String val);                               String getssid();        
        void setdestip(String val);                             String getdestip();
        void setpassword(String val);                           String getpassword();
        void setudpport(String val);                            String getudpport();
        void setunitid(String val);                             String getunitid();
        void setdhcp(boolean val);                              bool getdhcp();
        void setunitipaddress(String val);                      String getunitipaddress();
        void setsubnetmask(String val);                         String getsubnetmask();
        void setdefaultgateway(String val);                     String getdefaultgateway();
        void setdns(String val);                                String getdns();
        void seturlservername(String val);                      String geturlservername();
        // set the network info const char
        const char *_ssid;
        const char *_destIP;        
        const char *_password;
        unsigned int _udpPort;
        const char *_unit_ID;
        const char *_staticIP;
        const char *_subnetmask;
        const char *_defaultgateway;
        const char *_dynamicdns;
        const char *_URLservername; 
        // set the network info as string values
        
    private:
        static String _ssid_;
        static String _password_;        
        static String _destIP_;        
        static String _udpPort_;
        static String _unit_ID_;
        static String _staticIP_;
        static String _subnetmask_;
        static String _defaultgateway_;
        static String _dynamicdns_;
        static String _URLservername_;        
        static String _LastCARDUID_;        
        static String _LastTime_;
        static bool buzzer;  
        static bool CI_en;      
        static bool dhcp;
    };
}

#endif // MCIOS_H
