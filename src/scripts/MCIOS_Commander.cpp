#include "Arduino.h"
#include <EEPROM.h>
#include <iostream>
#include <string>
#include <map>
#include <functional>
#include "MCIOS.h"
#include "WiFiCon.h"
#include "MCIOS_Commander.h"
#include "IIC_Scanner.h"
#include "WEBSOCK.h"

std::map<std::string, std::function<boolean()>> ROOTmap;
std::map<std::string, std::function<boolean()>> BASICmap;
std::map<std::string, std::function<boolean()>> WIFImap;
std::map<std::string, std::function<boolean()>> UNITmap;

using namespace MCIOS_namespace;
// using namespace MCIOS_Commander_namespace;
using namespace WiFi_CON;
using namespace i2cscanner;

WiFiCon_class MCIOS_COMMANDER_WiFiCon_class;
MCIOS_class MCIOS_COMMANDER_MCSIO_class;
WEBSOCK_Class MCIOS_WEBSOCK_class;
i2cscanner_class MCIOS_I2C_Scanner;

//----ROOT commands
String returnfunc()
{
    String outcome = "";
    if (MCIOS_COMMANDER_MCSIO_class.codnav == WIFI_SEL)
    {
        outcome = "Wifi>";
    }
    if (MCIOS_COMMANDER_MCSIO_class.codnav == UNIT_SEL)
    {
        outcome = "Unit>";
    }
    if (MCIOS_COMMANDER_MCSIO_class.codnav == BASIC_SEL)
    {
        outcome = ">";
    }
    return outcome;
}
boolean shcommands()
{
    Serial.println("?                                   show commands");
    Serial.println("..                                  return");
    Serial.println("cls                                 clear screen");
    Serial.println("config_show                         show the current device configuration");
    if (MCIOS_COMMANDER_MCSIO_class.codnav == BASIC_SEL)
    {
        Serial.println("config_write                        save the configuration to the memory");
        Serial.println("config_show                         show the current device configuration");
        Serial.println("config_erase                        erase all the configuration from EPROM");
        Serial.println("scan_i2c                            scans i2c connected devices");
        Serial.println("reboot                              reboot the device");
        Serial.println("buzzon                              turn on the buzzer");
        Serial.println("buzzoff                             turn off the buzzer");
        Serial.println("wifi                                access wifi advanced network configuration");
        Serial.println("unit                                access this device advanced unit configuration");
        Serial.println("CI_en                               Enable the charing indicator");
        Serial.println("");
    }
    if (MCIOS_COMMANDER_MCSIO_class.codnav == WIFI_SEL)
    {
        Serial.println("wifi_scan                           scan the area for nearby wifi networks");
        Serial.println("ssid_set                            set the network ssid to connect to");        
        Serial.println("set_unit_ip                         set this device IP address, leave empty if wifi network offers DHCP");
        //Serial.println("set_server_name                     set the URL for the reporting destination server");
        Serial.println("set_destination_ip                  set the data collecting server IP address");
        Serial.println("set_url                             set the URL for the destination server");
        Serial.println("set_udp_port                        set the UDP port in case of UDP is needed");
        Serial.println("network_show                        show the running network configuration of the wifi");
        Serial.println("ping                                issues an ICMP reachability check, response (1) = reachable, 0=(not-reachable)");
        Serial.println("");
    }
    if (MCIOS_COMMANDER_MCSIO_class.codnav == UNIT_SEL)
    {
        Serial.println("id_set                              set the ID (identity) of this device");
        Serial.println("id_show                             show the current ID of this device");
        Serial.println("");
    }
    return true;
}
boolean goback()
{
    MCIOS_COMMANDER_MCSIO_class.codnav = BASIC_SEL;
    return true;
}
boolean cls()
{
    // works with putty only
    Serial.write(27);    // ESC command
    Serial.print("[2J"); // clear screen command
    Serial.write(27);
    Serial.print("[H"); // cursor to home command
    return true;
}
//----basic commands
boolean config_show()
{
    MCIOS_COMMANDER_MCSIO_class.SHOWMEMORY();
    Serial.println(returnfunc());
    return true;
}
boolean scan_i2c(){
    MCIOS_I2C_Scanner.IIC_Scan();
    return true;
}
boolean CI_en(){
    MCIOS_COMMANDER_MCSIO_class.setCI_en();
    return true;
}
boolean config_erase()
{
    MCIOS_COMMANDER_MCSIO_class.ERASEMEMORY();
    return true;
}
boolean config_write()
{
    MCIOS_COMMANDER_MCSIO_class.WRITEMEMORY();    
    return true;
}
boolean reboot()
{
    Serial.println("rebooted is being called");
    ESP.restart();
    return true;
}
boolean buzzon()
{
    MCIOS_COMMANDER_MCSIO_class.setBuzzer(true);
    MCIOS_COMMANDER_MCSIO_class.BUZZER(500, 800, 4);
    return true;
}
boolean buzzoff()
{
    MCIOS_COMMANDER_MCSIO_class.setBuzzer(false);
    return true;
}
boolean wifi()
{
    MCIOS_COMMANDER_MCSIO_class.codnav = WIFI_SEL;
    return true;
}
boolean unit()
{
    MCIOS_COMMANDER_MCSIO_class.codnav = UNIT_SEL;
    return true;
}
//-----wifi commands
boolean ssid_set()
{
    Serial.println("Please enter the wifi SSID (Note:Use write memory in root mode, then reset the device after changing the SSID): ");
    MCIOS_COMMANDER_MCSIO_class.setssid(MCIOS_COMMANDER_MCSIO_class.inputread());
    Serial.println("Selected Network:" + MCIOS_COMMANDER_MCSIO_class.getssid());
    Serial.println("Input password (leave empty if the wifi is unsecure): ");
    MCIOS_COMMANDER_MCSIO_class.setpassword(MCIOS_COMMANDER_MCSIO_class.inputread());
    Serial.println();
    return true;
}
boolean wifi_scan()
{
    MCIOS_COMMANDER_WiFiCon_class.WifiCon_Scan_Task();
    return true;
}
boolean set_unit_ip()
{
    Serial.println("Activate DHCP?: (yes/no)");
    String tempinput=MCIOS_COMMANDER_MCSIO_class.inputread();
    if (tempinput == "yes")
    {
        MCIOS_COMMANDER_MCSIO_class.setdhcp(true);
    }
    else if (tempinput == "no")
    {
        MCIOS_COMMANDER_MCSIO_class.setdhcp(false);
        Serial.println("Please enter the unit static IP: ");
        MCIOS_COMMANDER_MCSIO_class.setunitipaddress(MCIOS_COMMANDER_MCSIO_class.inputread());
        Serial.println("network Subnet mask?: ");
        MCIOS_COMMANDER_MCSIO_class.setsubnetmask(MCIOS_COMMANDER_MCSIO_class.inputread());
        Serial.println("default-gateway IP address?: ");
        MCIOS_COMMANDER_MCSIO_class.setdefaultgateway(MCIOS_COMMANDER_MCSIO_class.inputread());
        Serial.println("DNS IP address?: ");
        MCIOS_COMMANDER_MCSIO_class.setdns(MCIOS_COMMANDER_MCSIO_class.inputread());
    }else{
        Serial.println("Invalid value, please enter (Yes or no)");
    }

    return true;
}
// boolean set_server_name()
// {
//     Serial.println("Please enter URL of the destination server: ");
//     MCIOS_COMMANDER_MCSIO_class.setservername(MCIOS_COMMANDER_MCSIO_class.inputread());
//     Serial.println("Destination URL is set to:"+MCIOS_COMMANDER_MCSIO_class.getservername());
//     return true;
// }
boolean set_destination_ip()
{
    Serial.println("Please enter the desired destination server IP address ex:10.0.0.1: ");
    MCIOS_COMMANDER_MCSIO_class.setdestip(MCIOS_COMMANDER_MCSIO_class.inputread());
    Serial.println("Destination IP address is set to:" + MCIOS_COMMANDER_MCSIO_class.getdestip());
    return true;
}
boolean set_udp_port()
{
    Serial.println("Please enter the desired udp port: ");
    MCIOS_COMMANDER_MCSIO_class.setudpport(MCIOS_COMMANDER_MCSIO_class.inputread());
    Serial.println("UDP port is set to:" + MCIOS_COMMANDER_MCSIO_class.getudpport());
    return true;
}
//-------UNIT commands
boolean id_set()
{
    Serial.println("Please enter the Unit ID: ");
    MCIOS_COMMANDER_MCSIO_class.setunitid(MCIOS_COMMANDER_MCSIO_class.inputread());
    Serial.println("Unit ID is set to:" + MCIOS_COMMANDER_MCSIO_class.getunitid());    
    return true;
}
boolean id_show()
{
    Serial.print("Unit ID:                    ");
    //Serial.println(MCIOS_COMMANDER_MCSIO_class.READSTRINGFMEM(MEMUNITID));//deprecated for in which memory stack in different header
    Serial.println(MCIOS_COMMANDER_MCSIO_class.getunitid());
    return true;
}

boolean network_show()
{
    MCIOS_COMMANDER_WiFiCon_class.Net_state();
    return true;
}

boolean pingnet()
{
    Serial.println("Address? ");
    Serial.println(MCIOS_COMMANDER_WiFiCon_class.pingdest(MCIOS_COMMANDER_MCSIO_class.inputread(),5));
    return true;
}

boolean set_url()
{
    Serial.println("Please enter the desired URL destination server maximum 78 characters");
    MCIOS_COMMANDER_MCSIO_class.seturlservername(MCIOS_COMMANDER_MCSIO_class.inputread());
    Serial.println("Destination URL is set to:" + MCIOS_COMMANDER_MCSIO_class.geturlservername());
    return true;
}

boolean tester()
{
    MCIOS_WEBSOCK_class.websockpost();
    return true;
}

void MCIOS_Commander_class::COMMANDS_INIT()
{
    ROOTmap = {
        {"?", shcommands},
        {"..", goback},
        {"cls", tester},
        {"config_show", config_show}};
    BASICmap = {
        {"tester", tester},
        {"config_show", config_show},
        {"config_erase", config_erase},
        {"config_write", config_write},
        {"reboot", reboot},
        {"buzzon", buzzon},
        {"buzzoff", buzzoff},
        {"wifi", wifi},
        {"unit", unit},
        {"scan_i2c", scan_i2c},
        {"CI_en", CI_en}};
    WIFImap = {
        {"ssid_set", ssid_set},
        {"wifi_scan", wifi_scan},
        {"set_unit_ip", set_unit_ip},
        //{"set_server_name", set_server_name},
        {"set_destination_ip", set_destination_ip},
        {"set_url", set_url},
        {"set_udp_port", set_udp_port},
        {"network_show",network_show},
        {"ping",pingnet}};
    UNITmap = {
        {"id_set", id_set},
        {"id_show", id_show}};
}

String MCIOS_Commander_class::commander(String command)
{
    // sort string to char
    char arr[command.length() + 1];
    for (int i = 0; i < sizeof(arr); i++)
    {
        arr[i] = command[i];
    }
    // //seek command in maps
    if (BASICmap[arr] && (MCIOS_COMMANDER_MCSIO_class.codnav == BASIC_SEL))
    {
        BASICmap[arr]();
        Serial.println(returnfunc()); // end of the command execution
    }
    else if (WIFImap[arr] && MCIOS_COMMANDER_MCSIO_class.codnav == WIFI_SEL)
    {
        WIFImap[arr]();
        Serial.println(returnfunc()); // end of the command execution
    }
    else if (UNITmap[arr] && MCIOS_COMMANDER_MCSIO_class.codnav == UNIT_SEL)
    {
        UNITmap[arr]();
        Serial.println(returnfunc()); // end of the command execution
    }
    else if (ROOTmap[arr])
    {
        ROOTmap[arr]();
        Serial.println(returnfunc()); // end of the command execution
    }
    else
    {
        Serial.println("Uknown Command");
    }

    return "";
}
