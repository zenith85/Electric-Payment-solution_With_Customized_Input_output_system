#ifndef SYSLOG_H
#define SYSLOG_H


enum DeviceName
{
    NFCSENSOR,
    OLEDLCD,
    GPS,
    MEMORYLOAD,
};

//ICS stands for innder connecetion status
//DS stands for devices status
typedef struct Devices_ICS
{
    bool NFCSENSOR;
    bool OLEDLCD;
    bool GPS;
    int MEMORYLOAD;
}Device_ICS;

namespace syslog_namespace
{
    class syslog
    {
        public:
            void syslog_init();
            void getsyslog();
            void setsyslog(DeviceName dn,Device_ICS s);
    };
}


#endif