#ifndef DEFTECH_H
#define DEFTECH_H

//define tech board that is used:
#define                         Esp32_32U 
//#define                       Esp32_32

//define tech LCD that is used:
//#define                       LCD_1602
#define                         SSD1306 


#ifdef                          Esp32_32
    //GPS interfaces
    #define                     RXD2 16
    #define                     TXD2 17
    //NFCPN5322 interfaces
    #define                     PN532_SCK (18)
    #define                     PN532_MOSI (23)
    #define                     PN532_SS (5)
    #define                     PN532_MISO (19)
    //LCD_Manager Interrupt button interfaces
    #define                     pagerPin (34)
    //busser peizo electric sound beeper
    #define                     buzzerPin 2
    //charge indication
    #define                     chargePin (12)
#endif

#ifdef                          Esp32_32U
    //GPS interfaces
    #define                     RXD2 16
    #define                     TXD2 4
    //NFCPN5322 interfaces
    #define                     PN532_SCK (18)
    #define                     PN532_MOSI (23)
    #define                     PN532_SS (14)
    #define                     PN532_MISO (19)
    //LCD_Manager Interrupt button interfaces
    #define                     pagerPin (35)
    //busser peizo electric sound beeper
    #define                     buzzerPin 2
    //charge indication
    #define                     chargePin (27)
#endif

    #define                     MEMSIZE 380
    #define                     MEMBUZ 377
    #define                     MEMSSIDLOC 3
    #define                     MEMDESTIPLOC 36
    #define                     MEMWIFIPASSLOC 53
    #define                     MEMUDPPORTLOC 118
    #define                     MEMUNITID 124
    #define                     MEMWIFIDHCP 132
    #define                     MEMSTATICIP 134
    #define                     MEMSUBMASKLOC 150
    #define                     MEMDEFGATELOC 166
    #define                     MEMDNSLOC 183
    #define                     MEMSERVERNAME 200
    #define                     MEMLSC 280
    #define                     MEMLSID 282
    #define                     MEMLSTIME 291
    #define                     MEMCIEN 1
#endif