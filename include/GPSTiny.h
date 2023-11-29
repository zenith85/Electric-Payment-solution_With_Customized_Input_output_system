#ifndef GPSTINY_H
#define GPSTINY_H

namespace GPS_Neo6_namespace
{
    /// This is the GPS detection allocation class
    ///
    /// This class allows the board to purely communicate with mission critical parameter and with the GPS module specific libraries
    class GPS_Neo6_class
    {
    public:
        void GPS_init();  
        /// Main GPS_scan_TASK class
        ///
        /// @param critical_allowed Preprocess defined boolean always stands for 1 or 0, to allow critical missions or deny them      
        void GPS_scan_TASK(boolean critical_allowed);
    private:        
    };
} // namespaceeo6_class

#endif
