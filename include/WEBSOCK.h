#ifndef WEBSOCK_H
#define WEBSOCK_H

struct USER_DATA{
    String CARDUID;
    String UNITID;
    String TOTALTIME;
};

enum WEBSOCKEvent
{
    cardUID_REGISTER,
    cardUID_RELEASE,
    cardUID_RECORD,
    cardUID_POST_OFFLINE,
    cardUID_REG_STARTUP
};

enum WEBSOCKErrorType
{        
    registering_problem,
    Successfully_register,
    Unknown_error,
    Successfully_recorded
};

struct WSET_WSEM
{
    WEBSOCKErrorType errortype;
    String statusMsg;
    String errorMsg;
};

class WEBSOCK_Class
{
    public:        
        void websockpost();
        void WEBSOCK_setURL(const char *val);
        String WEBSOCK_getURL();
        WSET_WSEM OnlinePost(String cardUID, WEBSOCKEvent);
        WSET_WSEM OfflinePost(String cardUID);
        WSET_WSEM OfflinePost(String cardUID,String duration);
        WSET_WSEM WebSockPost(String cardUID, WEBSOCKEvent event, String offlineduration);
        static String msg;
    private:
        static USER_DATA user_data;

};



#endif // RESTAPI_H
