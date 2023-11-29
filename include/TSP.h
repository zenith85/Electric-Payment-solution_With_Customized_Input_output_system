#ifndef TSP_H
#define TSP_H

struct TimeDigitView
{
    int s_1;
    int s_2;
    int m_1;
    int m_2;
    int h_1;
    int h_2;
};

enum Timer_status{TSP_START,TSP_END,TSP_AUTH_ERROR};

struct TimerTask
{
    Timer_status status;    
    const char *UID;    
};

namespace TSP_namespace
{
    /// This is the Time service provider class
    ///
    /// This class allows the board to control the timings and calculate the over all service provision, it can recall back functions to help issuing server calls
    class TSP_class
    {
    public:
        /// Main Time service provider class
        ///
        /// @param TimerTask Data Structure that consist of (boolean status: true or false) (turn on, or turn off the timer), (const char pointer) (the NFC ID)
        void TSP_Task(TimerTask);
        int TSP_Get_Time();
        static int total_time;
        static String msg;

    private:
    };
}

#endif