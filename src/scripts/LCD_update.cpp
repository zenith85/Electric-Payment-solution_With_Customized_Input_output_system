#include "Arduino.h"
#include "LCD_update.h"
#include "LCD_Manager.h"
#include "WiFiCon.h"
#include "NFCPN532.h"
#include "TSP.h"
#include "WiFi.h"
#include "MCIOS.h"
#include "ChargingPort.h"
#include "DEF_TECH_INT.h"

using namespace LCD_DISPLAY;
using namespace WiFi_CON;
using namespace MCIOS_namespace;
using namespace NFCPN532_namespace;
using namespace TSP_namespace;

LCD_DISPLAY_class LCD_update_LCD_DISPLAY_class;
MCIOS_class LCD_update_MCIOS_class;
WiFiCon_class LCD_update_WiFiCon_class;
NFCPN532_class LCD_update_NFCPN532_class;
TSP_class LCD_update_TSP_class;
ChargingPort_class LCD_update_ChargingPort_class;

#ifdef LCD_1602
void LCD_update_class::LCD_UPDATE_USER()
{
    String status;
    String charging;
    // WiFi.status()==WL_CONNECTED?status="State:Connected":status="State:Not-connected";
    LCD_update_WiFiCon_class.wificonnected() ? status = "State:Connected     " : status = "State:Not-connected ";
    LCD_update_LCD_DISPLAY_class.TS_Display(status, FIRSTROW, state, 0);
    LCD_update_ChargingPort_class.ChargingPort() ? charging = "C" : charging = "D";
    LCD_update_LCD_DISPLAY_class.TS_Display("Name:" + LCD_update_MCIOS_class.getunitid(), SECONDROW, state, 0);
    LCD_update_LCD_DISPLAY_class.TS_Display("CS:" + charging, SECONDROW, state, 16);
    LCD_update_LCD_DISPLAY_class.TS_Display(LCD_update_TSP_class.msg, THIRDROW, state);
    LCD_update_LCD_DISPLAY_class.TS_Display(LCD_update_NFCPN532_class.msg, FOURTHROW, state);
}
#endif

#ifdef SSD1306
static String NameBuff;
static String TSPmsgbuff;
static String NFCmsgbuff;

void T_delay(int v){
    vTaskDelay(v / portTICK_PERIOD_MS);
}
//the following sub-private functions uses the negation of ! to render string compare between two const char*
//always return 0 if x=y. Another benefit is when it is zero no need to use !, because we will ommit the Else 
//condition, and that will release some thread processing pwoer.
void update_charging_symbol()
{
    //private function to check the charging indicater, then it communication with LCD_Manager.pp to notify
    //to show the charging indicator
    if (LCD_update_ChargingPort_class.ChargingPort())
    {
        LCD_update_LCD_DISPLAY_class.Charging_Symbol(true);
    }
    else
    {
        LCD_update_LCD_DISPLAY_class.Charging_Symbol(false);
    }
}
    //private function to check the wifi connectivity, then it communication with LCD_Manager.pp to notify
    //to show the wifi indicator
void update_wifi_status()
{
    if (LCD_update_WiFiCon_class.wificonnected())
    {
        LCD_update_LCD_DISPLAY_class.Wifi_Symbol(true);
    }else{
        LCD_update_LCD_DISPLAY_class.Wifi_Symbol(false);
    }
}
    //private function to check the Unit ID name indicater, then it communication with LCD_Manager.pp to notify
    //to show the ID name
void update_unit_name()
{
    if (strcmp(LCD_update_MCIOS_class.getunitid().c_str(),NameBuff.c_str())){
        LCD_update_LCD_DISPLAY_class.TS_Display("ID:"+NameBuff, TS_stretched_small, FIRSTROW, state, 0, false);
        T_delay(200);
        NameBuff=LCD_update_MCIOS_class.getunitid(); 
        LCD_update_LCD_DISPLAY_class.TS_Display("ID:"+NameBuff, TS_stretched_small, FIRSTROW, state, 0, true);       
    }
}
    //private function to check the update_timer indicater, then it communication with LCD_Manager.pp to notify
    //to show the update_timer indicator
void update_timer()
{
    //if they are not equal
    if (strcmp(LCD_update_TSP_class.msg.c_str(),TSPmsgbuff.c_str())){
        LCD_update_LCD_DISPLAY_class.TS_Display(TSPmsgbuff, TS_stretched_small, THIRDROW, state, 0, false);
        TSPmsgbuff=LCD_update_TSP_class.msg; 
        LCD_update_LCD_DISPLAY_class.TS_Display(TSPmsgbuff, TS_stretched_small, THIRDROW, state, 0, true);       
    }
}
    //private function to check the update_availability_msgs indicater, then it communication with LCD_Manager.pp to notify
    //to show the void update_availability_msgs() indicator
void update_availability_msgs()
{
    //if they are not equal
    if (strcmp(LCD_update_NFCPN532_class.msg.c_str(),NFCmsgbuff.c_str())){
        LCD_update_LCD_DISPLAY_class.TS_Display(NFCmsgbuff, TS_regular_small, FOURTHROW, state, 0, false);
        T_delay(200);
        NFCmsgbuff=LCD_update_NFCPN532_class.msg; 
        LCD_update_LCD_DISPLAY_class.TS_Display(NFCmsgbuff, TS_regular_small, FOURTHROW, state, 0, true);       
    }
}
void LCD_update_class::LCD_UPDATE_USER()
{
    //this Public function is being called by the task manager over and over on a thread callback.
    update_wifi_status();
    update_charging_symbol();
    update_unit_name();
    update_timer();
    update_availability_msgs();
}
#endif
