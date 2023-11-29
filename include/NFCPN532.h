#ifndef NFCPN532_H
#define NFCPN532_H

namespace NFCPN532_namespace
{
    /// This is the NFCPN532 class
    ///
    /// This class allows the board to purely communicate with mission critical parameter and with the NFC card reader module specific libraries
    /// @attention IMPORTANT NOTE: don't forget to change the 1000000 to 100000 in the Adafruit_PN532.cpp
    ///  Adafruit_PN532::Adafruit_PN532(uint8_t ss) {
    ///    spi_dev =
    ///        //new Adafruit_SPIDevice(ss, 1000000, SPI_BITORDER_LSBFIRST, SPI_MODE0);
    ///       new Adafruit_SPIDevice(ss, 100000, SPI_BITORDER_LSBFIRST, SPI_MODE0);
    ///  }
    class NFCPN532_class
    {
    public:
        void NFCPN532_init();
        /// Main NFCPN532_Task class
        ///
        /// @param critical_allowed Preprocess defined boolean always stands for 1 or 0, to allow critical missions or deny them
        void NFCPN532_Task(boolean critical_allowed);
        bool Release_card_offline(String uid, String duration);
        static String msg;
        static String MEM;
    private:

    };
}

#endif