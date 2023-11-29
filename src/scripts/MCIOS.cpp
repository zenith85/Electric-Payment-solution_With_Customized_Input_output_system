#include "Arduino.h"
#include <EEPROM.h>
#include "MCIOS.h"
#include <Wire.h>
#include "WiFiCon.h"
#include "MCIOS_Commander.h"
#include <DEF_TECH_INT.h>
#include "WEBSOCK.h"
#include "NFCPN532.h"
#include "LCD_Manager.h"
//#include <WebServer.h>
// namespaces
using namespace MCIOS_namespace;
using namespace WiFi_CON;
using namespace NFCPN532_namespace;
using namespace LCD_DISPLAY;
// classes
WiFiCon_class MCIOS_WiFiCon_class;
MCIOS_Commander_class MCIOS_Commander_class_;
WEBSOCK_Class MCIOS_WEBSOCK_Class_;
NFCPN532_class MCIOS_NFCPN532_class;
LCD_DISPLAY_class MCIOS_LCD_DISPLAY_class;

String MCIOS_class::_ssid_              = "";
String MCIOS_class::_password_          = "";
String MCIOS_class::_udpPort_           = "";
String MCIOS_class::_unit_ID_           = "";
String MCIOS_class::_staticIP_          = "";
String MCIOS_class::_subnetmask_        = "";
String MCIOS_class::_defaultgateway_    = "";
String MCIOS_class::_dynamicdns_        = "";
String MCIOS_class::_destIP_            = "";
String MCIOS_class::_URLservername_     = "";
String MCIOS_class::_LastCARDUID_       = "";        
String MCIOS_class::_LastTime_          = "";

bool MCIOS_class::dhcp=0;
bool MCIOS_class::buzzer=0;
bool MCIOS_class::CI_en=0;

void MCIOS_class::INITIATEMEMORY()
{
    EEPROM.begin(MEMSIZE);
}

void MCIOS_class::BANNER()
{
    // logger and company banner
    Serial.println("");
    // Serial.println("              .::==          ##+==::        ");
    // Serial.println("         +##%%#@@=-           :+@*+##%%     ");
    // Serial.println("     .-: ::   +@+              .#%:      += ");
    // Serial.println("     =@:     -@%.              .+@-      +@ ");
    // Serial.println("     =@  .::  :*@*-          =#%*:  :--::=@ ");
    // Serial.println("     =@%%##@%:   -%%-      :%%-   -%@+=+#%@ ");
    // Serial.println("     +@    .+@+-  .#@      -+   -#%+.    =@.");
    // Serial.println("     #+       =%%=    .+#=.   :%%-       .+:");
    // Serial.println("                -=  .+@%+@@+. .:            ");
    // Serial.println("               .=+  .+%%*@%+  :-.           ");
    // Serial.println("     @#      .+@%-     =#-    :%@=       .#:");
    // Serial.println("     +@    .+@+-  .#@      -+   -#%+.    =@.");
    // Serial.println("     =@***#@*:  :=%*:      :#%=.  :*@*+*##@ ");
    // Serial.println("     =@       -%@+:          -#@%:  .:.  =@ ");
    // Serial.println("     =@:     -@%.              .+@-      *@ ");
    // Serial.println("      :. ::   =@#              .%#.      =- ");
    // Serial.println("         +##%%#@@=-           :+@*+##%%     ");
    // Serial.println("");
    // Serial.println("           _     _                                 ");
    // Serial.println("     /|   | |   | |                                ");
    // Serial.println("    /  |  | |   | |_ __ _ _ __ ___   ___  ___ _ __ ");
    // Serial.println("   / /| | | |   | __/ _` | '_ ` _ | / _ || _ | '__|");
    // Serial.println("  / ____ || |___| | |(_| | | | | | |  __/  __/ |   ");
    // Serial.println(" /_/    |_|_____|___|__,_|_| |_| |_||___||___|_|  ©");
    // Serial.println("                                                   ");
    // Serial.println("                                                   ");
    Serial.println("Developed by:Dr. Ibraheem Altaha: ibrahimgate@gmail.com  ");
    Serial.println("");
    Serial.println("The configuration input out system CIOS Ver.1.0, is COPYRIGHT protected for Altameer co.,");
    Serial.println("Do not copy or redistrubute, Altameer do not allow any of it.");
    Serial.println("to begin! type ? to show all commands");
    Serial.println(">");
}

void MCIOS_class::ZEROIS()
{
    _ssid_ = "";
    _destIP_ = "";
    _URLservername_="";
    _password_ = "";
    _udpPort_ = "";
    _unit_ID_ = "";
    _staticIP_ = "";
    _subnetmask_ = "";
    _defaultgateway_ = "";
    _dynamicdns_ = "";
    _ssid = _ssid_.c_str();
    _destIP = _destIP_.c_str();
    _password = _password_.c_str();
    _udpPort = 0;
    dhcp = 0;
    buzzer=0;
    CI_en=0;
    _unit_ID = _unit_ID_.c_str();
    _staticIP = _staticIP_.c_str();
    _URLservername = _URLservername_.c_str();
    _subnetmask = _subnetmask_.c_str();
    _defaultgateway = _defaultgateway_.c_str();
    _dynamicdns = _dynamicdns_.c_str();

}
// setters
void MCIOS_class::setssid(String val)
{
    _ssid_ = val;
    _ssid = _ssid_.c_str();
}String MCIOS_class::getssid(){return _ssid_;};

void MCIOS_class::setdestip(String val)
{
    _destIP_ = val;
    _destIP = _destIP_.c_str();
}String MCIOS_class::getdestip(){return _destIP_;};

void MCIOS_class::setpassword(String val)
{
    _password_ = val;
    _password = _password_.c_str();
}String MCIOS_class::getpassword(){return _password_;}

void MCIOS_class::setudpport(String val)
{
    _udpPort_ = val;
    _udpPort = (int)_udpPort_.c_str();
}String MCIOS_class::getudpport(){return _udpPort_;};
void MCIOS_class::setunitid(String val)
{
    _unit_ID_ = val;
    _unit_ID = _unit_ID_.c_str();
}String MCIOS_class::getunitid(){return _unit_ID_;};
void MCIOS_class::setBuzzer(bool val)
{
    buzzer = val;
}bool MCIOS_class::getBuzzer() { return buzzer; };
void MCIOS_class::setCI_en(){
    CI_en=!CI_en;
}bool MCIOS_class::getCI_en(){return CI_en;}
void MCIOS_class::setdhcp(bool val) 
{
    dhcp = val;
}bool MCIOS_class::getdhcp() { return dhcp; };
void MCIOS_class::setunitipaddress(String val)
{
    _staticIP_ = val;
    _staticIP=_staticIP_.c_str();
}String MCIOS_class::getunitipaddress(){return _staticIP_;};
void MCIOS_class::setsubnetmask(String val)
{
    _subnetmask_ = val;
    _subnetmask=_subnetmask_.c_str();
}String MCIOS_class::getsubnetmask(){return _subnetmask_;};
void MCIOS_class::setdefaultgateway(String val)
{
    _defaultgateway_ = val;
    _defaultgateway=_defaultgateway_.c_str();
}String MCIOS_class::getdefaultgateway(){return _defaultgateway_;};
void MCIOS_class::setdns(String val)
{
    _dynamicdns_ = val;
    _dynamicdns=_dynamicdns_.c_str();
}String MCIOS_class::getdns(){return _dynamicdns_;};
void MCIOS_class::seturlservername(String val)
{
    _URLservername_ = val;
    _URLservername=_URLservername_.c_str();
}String MCIOS_class::geturlservername(){return _URLservername_;};


void MCIOS_class::BUZZER(int period, int frequency, int times)
{
    // Serial.println(READSTRINGFMEM(MEMBUZ));
    if (READSTRINGFMEM(MEMBUZ) == "1")
    {
        int i = 0;
        while (i != times)
        {
            ledcWriteTone(0, frequency);
            vTaskDelay(period / portTICK_PERIOD_MS);
            ledcWriteTone(0, 0);
            vTaskDelay(period / portTICK_PERIOD_MS);
            i++;
        }
    }
}
// erase memory function
void MCIOS_class::ERASEMEMORY()
{
    for (int i = 0; i < MEMSIZE; i++)
    {
        EEPROM.write(i, 0);
        Serial.print("!");
    }
    EEPROM.commit();
    ZEROIS();
    Serial.println("");
    Serial.println("MemoryErased!");
    // BUZZER();
    Serial.println(">");
}

void MCIOS_class::SHOWMEMORY()
{
    Serial.println("");
    Serial.print("Data Collection IP Address: ");
    Serial.println(READSTRINGFMEM(MEMDESTIPLOC));
    Serial.print("Destination server URL:     ");
    Serial.println(READSTRINGFMEM(MEMSERVERNAME));    
    Serial.print("SSID:                       ");
    Serial.println(READSTRINGFMEM(MEMSSIDLOC));
    Serial.print("UDP Port:                   ");
    Serial.println(READSTRINGFMEM(MEMUDPPORTLOC));
    Serial.print("Unit ID:                    ");
    Serial.println(READSTRINGFMEM(MEMUNITID));
    Serial.print("BUZZER:                     ");
    Serial.println(READSTRINGFMEM(MEMBUZ));
    Serial.print("CI_en:                      ");
    Serial.println(READSTRINGFMEM(MEMCIEN));
    Serial.println("IP address Configuration: ");
    READSTRINGFMEM(MEMWIFIDHCP) == "1" ? Serial.println("DHCP:Active") : Serial.println("DHCP:Not-Active");
    if (READSTRINGFMEM(MEMWIFIDHCP) == "0")
    {
        Serial.print("Static IP address:       ");
        Serial.println(READSTRINGFMEM(MEMSTATICIP));
        Serial.print("Subnet mask:             ");
        Serial.println(READSTRINGFMEM(MEMSUBMASKLOC));
        Serial.print("Default-gateway:         ");
        Serial.println(READSTRINGFMEM(MEMDEFGATELOC));
        Serial.print("DNS:                     ");
        Serial.println(READSTRINGFMEM(MEMDNSLOC));
    }
}

void MCIOS_class::WRITEMEMORY()
{
    WRITESTRINGFMEM(MEMBUZ, String(buzzer));
    WRITESTRINGFMEM(MEMCIEN, String(CI_en));
    WRITESTRINGFMEM(MEMWIFIDHCP, String(dhcp));
    WRITESTRINGFMEM(MEMSSIDLOC, _ssid_);
    WRITESTRINGFMEM(MEMDESTIPLOC, _destIP_);
    WRITESTRINGFMEM(MEMWIFIPASSLOC, _password_);
    WRITESTRINGFMEM(MEMUDPPORTLOC, _udpPort_);
    WRITESTRINGFMEM(MEMUNITID, _unit_ID_);
    WRITESTRINGFMEM(MEMSTATICIP, _staticIP_);
    WRITESTRINGFMEM(MEMSUBMASKLOC, _subnetmask_);
    WRITESTRINGFMEM(MEMDEFGATELOC, _defaultgateway_);
    WRITESTRINGFMEM(MEMDNSLOC, _dynamicdns_);
    WRITESTRINGFMEM(MEMSERVERNAME, _URLservername_);    
}

String MCIOS_class::READSTRINGFMEM(int _address)
{
    int len = EEPROM.read(_address);
    char data[len + 1];
    for (int i = 0; i < len; i++)
    {
        data[i] = EEPROM.read(_address + 1 + i);
        // vTaskDelay(5 / portTICK_PERIOD_MS);
        delay(5);
    }
    data[len] = '\0';
    // BUZZER();
    return String(data);
}

void MCIOS_class::WRITESTRINGFMEM(int _address, String _str)
{
    byte len = _str.length();
    EEPROM.write(_address, len);
    for (int i = 0; i < len; i++)
    {
        EEPROM.write(_address + 1 + i, _str[i]);
        // vTaskDelay(10 / portTICK_PERIOD_MS);
        delay(10);
        Serial.print("!");
        EEPROM.commit();
    }
}

void MCIOS_class::UPDATEDISPLAY()
{
}

void MCIOS_class::INITIATEMCIOS()
{
    buzzer = true;
    dhcp = true;
    pinMode(buzzerPin, OUTPUT);
    ledcSetup(0, 5000, 8);
    ledcAttachPin(buzzerPin, 0);
    INITIATEMEMORY();
    LOADCONFIG();
    INITIATEWIFI();
    INITIATEWEBSOCK();
    BUZZER(800, 800, 2);
    MCIOS_Commander_class_.COMMANDS_INIT();
    codnav = BASIC_SEL;
}

void MCIOS_class::LOADCONFIG()
{
    // Serial.println("data retreved");
    
    READSTRINGFMEM(MEMBUZ) == "0"?buzzer = false:buzzer = true;                                 MCIOS_LCD_DISPLAY_class.Loading_Bar(0);
    READSTRINGFMEM(MEMCIEN) == "0"?CI_en = false:CI_en = true;
    READSTRINGFMEM(MEMWIFIDHCP) == "0"? dhcp = false:dhcp = true;                               MCIOS_LCD_DISPLAY_class.Loading_Bar(1);                               
    _ssid_ = READSTRINGFMEM(MEMSSIDLOC);_ssid = _ssid_.c_str();                                 MCIOS_LCD_DISPLAY_class.Loading_Bar(2);                                 
    _destIP_ = READSTRINGFMEM(MEMDESTIPLOC);_destIP = _destIP_.c_str();                         MCIOS_LCD_DISPLAY_class.Loading_Bar(3);                         
    _password_ = READSTRINGFMEM(MEMWIFIPASSLOC);_password = _password_.c_str();                 MCIOS_LCD_DISPLAY_class.Loading_Bar(4);             
    _udpPort_ = READSTRINGFMEM(MEMUDPPORTLOC);_udpPort = (int)(_udpPort_.c_str());              MCIOS_LCD_DISPLAY_class.Loading_Bar(5);              
    _unit_ID_ = READSTRINGFMEM(MEMUNITID);_unit_ID = _unit_ID_.c_str();                         MCIOS_LCD_DISPLAY_class.Loading_Bar(6);                  
    _URLservername_ = READSTRINGFMEM(MEMSERVERNAME);_URLservername=_URLservername_.c_str();     
    
    if (READSTRINGFMEM(MEMLSC)=="1")
    {
        _LastCARDUID_       = READSTRINGFMEM(MEMLSID);        
        _LastTime_          = READSTRINGFMEM(MEMLSTIME);
    }
    if (MCIOS_LCD_DISPLAY_class.Loading_Bar(7)){MCIOS_LCD_DISPLAY_class.fullerase();}        
    UPDATEDISPLAY();
    vTaskDelay(100 / portTICK_PERIOD_MS);
}

void MCIOS_class::INITIATEWIFI()
{
    MCIOS_WiFiCon_class.WiFiCon_init(dhcp, _ssid, _password, _staticIP, _subnetmask, _defaultgateway, _dynamicdns);
}

void MCIOS_class::INITIATEWEBSOCK()
{
    MCIOS_WEBSOCK_Class_.WEBSOCK_setURL(_URLservername);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    MCIOS_WEBSOCK_Class_.WebSockPost(_unit_ID_,cardUID_REG_STARTUP,"0");
}

void MCIOS_class::LSofflinedatareleasertask()
{
    if (READSTRINGFMEM(MEMLSC)=="1")
    {
        _LastCARDUID_       = READSTRINGFMEM(MEMLSID);        
        _LastTime_          = READSTRINGFMEM(MEMLSTIME);
        if (MCIOS_NFCPN532_class.Release_card_offline(_LastCARDUID_,_LastTime_))
        {
            WRITESTRINGFMEM(MEMLSC,"0");
        }
    } 
}

bool MCIOS_class::LSrecorder(boolean LSavailable, String CARDUID, String TOTALTIME)
{
    //this method call happen only when a release operation is occured  
    WRITESTRINGFMEM(MEMLSC,String(LSavailable));
    WRITESTRINGFMEM(MEMLSID,CARDUID);
    WRITESTRINGFMEM(MEMLSTIME,TOTALTIME);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    Serial.println(READSTRINGFMEM(MEMLSC));
    Serial.println(READSTRINGFMEM(MEMLSID));
    Serial.println(READSTRINGFMEM(MEMLSTIME));
    return true;
}


void MCIOS_class::SERIALINPUT()
{
    String input;
    if (Serial.available())
    {
        vTaskDelay(2 / portTICK_PERIOD_MS);
        input = Serial.readStringUntil('\r').c_str();
        Serial.println(MCIOS_Commander_class_.commander(input));
        input = ""; // clear the input buffer
    }
}

String MCIOS_class::inputread()
{
    while (Serial.available() == 0)
    {
    }
    return Serial.readStringUntil('\r').c_str();
}
