/**************************************************************************/
/*!
    @file     iso14443a_uid.pde
    @author   Adafruit Industries
    @license  BSD (see license.txt)

    This example will attempt to connect to an ISO14443A
    card or tag and retrieve some basic information about it
    that can be used to determine what type of card it is.

    Note that you need the baud rate to be 115200 because we need to print
    out the data and read from the card at the same time!

This is an example sketch for the Adafruit PN532 NFC/RFID breakout boards
This library works with the Adafruit NFC breakout
  ----> https://www.adafruit.com/products/364

Check out the links above for our tutorials and wiring diagrams
These chips use SPI or I2C to communicate.

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

*/
/**************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
#include <Arduino.h>
#include "NFCPN532.h"
#include "LCD_Manager.h"
#include "TSP.h"
#include "SRD_Relay.h"
#include "DEF_TECH_INT.h"
#include "MCIOS.h"
#include <WEBSOCK.h>
#include "WiFiCon.h"
#include "ChargingPort.h"

using namespace NFCPN532_namespace;
using namespace LCD_DISPLAY;
using namespace TSP_namespace;
using namespace MCIOS_namespace;
using namespace WiFi_CON;
// Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);
Adafruit_PN532 nfc(PN532_SS);
// Charging indicator

// to the lcd
LCD_DISPLAY_class NFC_to_LCD;
TSP_class NFC_to_TSP;
SRD_Relay_class NFC_SRD_Replay_class;
MCIOS_class NFC_MCIOS_class;
WEBSOCK_Class NFC_WEBSOCK_Class;
ChargingPort_class NFC_ChargingPort_Class;
WiFiCon_class NFC_WiFi_CON_Class;

// local parameters related to scan and release
static boolean REGMODE = false;
bool success = false;
TimerTask TimerTask_;
String NFCPN532_class::MEM = "";
uint8_t uid[] = {0, 0, 0, 0, 0, 0, 0}; // Buffer to store the returned UID
uint8_t uidLength;                     // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

String NFCPN532_class::msg = "";

void NFCPN532_class::NFCPN532_init()
{
    nfc.begin();
    uint32_t versiondata = nfc.getFirmwareVersion();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    if (!versiondata)
    {
        Serial.print("Didn't find PN53x board");
        NFCPN532_class::msg = "NFC Hardware Problem          ";
        // NFC_to_LCD.TS_Display("NFC Hardware Problem          ", FOURTHROW, NFC_PAGE);
        // NFC_to_LCD.TS_Display("NFC Hardware Problem          ", FOURTHROW, state);
        //  while (1)
        //      ; // halt
    }
    else
    {
        // Got ok data, print it out!
        Serial.print("Found chip PN5");
        Serial.println((versiondata >> 24) & 0xFF, HEX);
        Serial.print("Firmware ver. ");
        Serial.print((versiondata >> 16) & 0xFF, DEC);
        Serial.print('.');
        Serial.println((versiondata >> 8) & 0xFF, DEC);
    }

    // Set the max number of retry attempts to read from a card
    // This prevents us from waiting forever for a card, which is
    // the default behaviour of the PN532.
    nfc.setPassiveActivationRetries(0xFF);

    // configure board to read RFID tags
    nfc.SAMConfig();

    Serial.println("Waiting for an ISO14443A card");
}

bool chargerindicator()
{
    return NFC_ChargingPort_Class.ChargingPort();
}

void Waiting_Timer(int period)
{
    for (int i = 0; i < period; i++)
    {
        // NFC_to_LCD.TS_Display("Available in " + String(i) + " sec  ", FOURTHROW, NFC_PAGE);
        // NFC_to_LCD.TS_Display("Available in " + String(i) + " sec  ", FOURTHROW, state);
        // while(!msgpublisher("Available in " + String(i) + " sec  ", 1)){};
        NFCPN532_class::msg = "Available in " + String(i) + " sec  ";
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    // NFC_to_LCD.TS_Display("Available           ", FOURTHROW, NFC_PAGE);
    // NFC_to_LCD.TS_Display("Service:Available   ", FOURTHROW, state);
}

void Register_card(String cardUID)
{
    // Stick in loop if charging to be unplugged
    if (chargerindicator() && NFC_MCIOS_class.getCI_en())
    {
        // while(!msgpublisher("Unplug charger first", 3)){};
        NFCPN532_class::msg = "Unplug charger first";
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        NFCPN532_class::msg = "Service:Available   ";
    }
    else
    {
        if (NFC_WiFi_CON_Class.wificonnected())
        {
            // here we send details of the card via wifi
            // also retreave data of the user
            // populate the data
            // while(!msgpublisher("Register : " + cardUID, 1)){};
            NFCPN532_class::msg = "Register : " + cardUID;
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            //***************************
            //  do register functions
            //***************************
            TimerTask_.UID = cardUID.c_str();
            // WSET_WSEM postBuffer = NFC_WEBSOCK_Class.OnlinePost(cardUID, cardUID_REGISTER);
            WSET_WSEM postBuffer = NFC_WEBSOCK_Class.WebSockPost(cardUID, cardUID_REGISTER, "0");
            if (postBuffer.errortype == Successfully_register)
            {
                TimerTask_.status = TSP_START;
                Serial.println(cardUID + " is registered!");
                NFCPN532_class::msg = postBuffer.errorMsg;
                vTaskDelay(2000 / portTICK_PERIOD_MS);
                REGMODE = true;
                NFC_SRD_Replay_class.SRD_Relay_ON();
                NFCPN532_class::msg = "Register : " + cardUID;
            }
            else
            {
                Serial.println(cardUID + " is not registered!");
                TimerTask_.status = TSP_AUTH_ERROR;
                NFCPN532_class::msg = postBuffer.errorMsg;
                vTaskDelay(3000 / portTICK_PERIOD_MS);
                Waiting_Timer(2);
            }
            NFC_to_TSP.TSP_Task(TimerTask_);
            NFCPN532_class::msg = "Service:Available   ";
        }
        else
        {
            // while(!msgpublisher("Device is Offline   ", 2)){};
            NFCPN532_class::msg = "Device is Offline";
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            // while(!msgpublisher("Waiting for network ", 2)){};
            NFCPN532_class::msg = "Waiting for network";
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            NFCPN532_class::msg = "Service:Available   ";
        }
    }
}

void Release_card(String cardUID)
{
    // Stick in loop if charging to be plugged
    if (!chargerindicator() && NFC_MCIOS_class.getCI_en())
    {
        NFCPN532_class::msg = "Plug charger first  ";
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
    else
    {

        if (NFC_WiFi_CON_Class.wificonnected())
        {
            //***************************
            // do release server functions
            //***************************
            TimerTask_.UID = cardUID.c_str();
            // WSET_WSEM postBuffer = NFC_WEBSOCK_Class.OnlinePost(cardUID, cardUID_RELEASE);
            WSET_WSEM postBuffer = NFC_WEBSOCK_Class.WebSockPost(cardUID, cardUID_RELEASE, "0");
            if (postBuffer.errortype == Successfully_register)
            {
                TimerTask_.status = TSP_END;
                NFC_to_TSP.TSP_Task(TimerTask_);
                Serial.println(cardUID + " is released");
                NFCPN532_class::msg = "Release : " + cardUID;
                vTaskDelay(3000 / portTICK_PERIOD_MS);
                //  free the data
                NFCPN532_class::MEM = "";
                REGMODE = false;
                Waiting_Timer(2);
                NFC_SRD_Replay_class.SRD_Relay_OFF();
            }
            else
            {
                Serial.println(postBuffer.errorMsg);
                Serial.println(cardUID + " not released");
                NFCPN532_class::msg = "error :     " + cardUID;
                vTaskDelay(3000 / portTICK_PERIOD_MS);
                Waiting_Timer(2);
            }
        }
        else
        {
            if (!NFC_MCIOS_class.getCI_en())
            {
                NFCPN532_class::msg = "Device is Offline";
                vTaskDelay(2000 / portTICK_PERIOD_MS);
                NFCPN532_class::msg = "Waiting for network";
                vTaskDelay(2000 / portTICK_PERIOD_MS);
                NFCPN532_class::msg = "Service:Available   ";
            }
            else
            {
                // if (NFC_WEBSOCK_Class.OfflinePost(cardUID).errortype == Successfully_recorded)
                if (NFC_WEBSOCK_Class.WebSockPost(cardUID, cardUID_RECORD, "0").errortype == Successfully_recorded)
                {
                    TimerTask_.status = TSP_END;
                    NFC_to_TSP.TSP_Task(TimerTask_);
                    Serial.println(cardUID + " is released");
                    NFCPN532_class::msg = "Release : " + cardUID;
                    vTaskDelay(1500 / portTICK_PERIOD_MS);
                    NFCPN532_class::msg = "Session recorded    ";
                    vTaskDelay(1500 / portTICK_PERIOD_MS);
                    NFCPN532_class::MEM = "";
                    REGMODE = false;
                    Waiting_Timer(3);
                    NFC_SRD_Replay_class.SRD_Relay_OFF();
                }
                else
                {
                    NFCPN532_class::msg = "Uknown error        ";
                    vTaskDelay(2000 / portTICK_PERIOD_MS);
                }
            }
        }
    }
    NFCPN532_class::msg = "Service:Available   ";
}

bool NFCPN532_class::Release_card_offline(String uid, String duration)
{
    // WSET_WSEM postBuffer = NFC_WEBSOCK_Class.OfflinePost(uid, duration);
    WSET_WSEM postBuffer = NFC_WEBSOCK_Class.WebSockPost(uid, cardUID_POST_OFFLINE, duration);
    if (postBuffer.errortype == Successfully_register)
    {
        Serial.println("lost data handed successfully");
        return true;
    }
    else
    {
        // do nothing
        return false;
    }
}

void NFCPN532_class::NFCPN532_Task(boolean critical_allowed)
{
    Serial.println(success);
    if (success)
    {
        // local buzz
        NFC_MCIOS_class.BUZZER(200, 900, 2);
        Serial.println("Found a card!");
        Serial.print("UID Length: ");
        Serial.print(uidLength, DEC);
        Serial.println(" bytes");
        Serial.print("UID Value: ");
        for (uint8_t i = 0; i < uidLength; i++)
        {
            Serial.print(" 0x");
            Serial.print(uid[i], HEX);
        }
        Serial.println("");
        char rfiduid[uidLength];
        sprintf(rfiduid, "%02X%02X%02X%02X", uid[0], uid[1], uid[2], uid[3]);

        if (REGMODE)
        {
            Release_card(rfiduid);
        }
        else
        {
            NFCPN532_class::MEM = rfiduid;
            Register_card(NFCPN532_class::MEM);
        }
        //   Wait 1 second before continuing
        // vTaskDelay(200 / portTICK_PERIOD_MS);
    }
    else if (!success)
    {
        // PN532 probably timed out waiting for a card
        Serial.println("Timed out waiting for a card");
        // vTaskDelay(500 / portTICK_PERIOD_MS);
        if (critical_allowed)
        {
            NFCPN532_class::msg = "Service:Available";
            vTaskDelay(200 / portTICK_PERIOD_MS);
        }
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
    // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
    // 'uid' will be populated with the UID, and uidLength will indicate
    // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
    success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);
}
