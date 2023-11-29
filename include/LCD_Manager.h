#ifndef LCD_MANAGER_H
#define LCD_MANAGER_H

// enumerator for trouble shooting
// feed error means location LCD row will inidcate error if the feed is cut etc.
enum LCDPage
{
    LCDPage_begin,  
    state,
    GPS_PAGE,  
    NFC_PAGE,        
    LCDPage_end,    
};

enum TS_Code
{
    FIRSTROW = 0,
    SECONDROW = 1,
    THIRDROW = 2,
    FOURTHROW = 3    
};

typedef uint8_t TS_FontStyle;
//font styles for the 1603 settext function
 static TS_FontStyle TS_regular_small[2] = {1,1};
 static TS_FontStyle TS_stretched_small[2] = {1,2};
 static TS_FontStyle TS_regular_medium[2] = {2,2};
 static TS_FontStyle TS_stretched_medium[2] = {2,3};


enum TS_Font_size
{
    FontSmall = 1,
    FontMedium = 2,
    FontLarge = 3,
    FontExtraLarge = 4
};


namespace LCD_DISPLAY
{
    /// This is the LCD 1602 class
    ///
    /// This class allows us to display any troubleshooting and data information and error messages to the clients
    class LCD_DISPLAY_class
    {
    public:
        /// Main TTS_Display class
        ///
        /// @param text String that holds the content that supposed to be displayed, 20 characters
        /// @param TSC TS_Code enumerator data type that points to the location of the display (first row, second row, third row etc.)
        /// @param PAGE_ LCDPage enumerator data type that points out to witch page the display yields to, (GPS NFC, Wifi, etc.)
        void TS_Display(String text, TS_Code TSC, LCDPage PAGE_);
        void TS_Display(String text, TS_Code TSC, LCDPage PAGE_, uint8_t curloc);
        void TS_Display(String text, TS_FontStyle fontstyle[], TS_Code TSC, LCDPage PAGE_, uint8_t curloc,boolean WRORDEL);
        void Task_LCD_init();
        void LCD_init();     
        void fullerase();
        bool Loading_Bar(uint8_t v);
        void Page_selector();
        void Charging_Symbol(boolean v);
        void Wifi_Symbol(boolean v);

    private:
    };
}

#endif