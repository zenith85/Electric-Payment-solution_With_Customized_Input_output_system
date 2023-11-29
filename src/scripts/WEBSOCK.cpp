#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <MCIOS.h>
#include <WEBSOCK.h>
#include "TSP.h"
#include <sstream>

using namespace std;
using namespace MCIOS_namespace;
using namespace TSP_namespace;

TSP_class WEBSOCK_TSP_class;
MCIOS_class WEBSOCK_MCIOS_class;
// initiate data enum
static USER_DATA user_data;
// server port is 80
WebServer server(80);
// server location, later it become part of the MCIOS eeprom data
// const char* servername="http://140.82.34.191:2008/api/Request/ScooterSignIn";
//                         Http://10.10.14.200:2080/api/Scooter/ScooterSignIn
const char *servername = "";
String WEBSOCK_Class::msg = "";

void WEBSOCK_Class::WEBSOCK_setURL(const char *val)
{
  servername = val;
}

String WEBSOCK_Class::WEBSOCK_getURL()
{
  return (String)servername;
}

USER_DATA dtc(String cardUID)
{
  user_data.CARDUID = cardUID;
  user_data.UNITID = WEBSOCK_MCIOS_class.getunitid();
  int a = WEBSOCK_TSP_class.TSP_Get_Time(); // old version is .totaltime
  stringstream ss;
  ss << a;
  string s;
  ss >> s;
  user_data.TOTALTIME = s.c_str();
  // String postbuffer="{\"nfc\": \""+user_data.CARDUID+",\"Duration\": \""+user_data.TOTALTIME+"\",\"id\": \""+user_data.CARDUID+"\",\"Event\":\""+"Session_request"+"\"}";
  return user_data;
}

DynamicJsonDocument JSONPARSE(String input)
{

  /* code */
  // json objects (status,message)
  DynamicJsonDocument doc(300);
  DeserializationError error = deserializeJson(doc, input);
  // Serial.println("reached here before crash");
  if (error)
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
  }

  return doc;
}

WSET_WSEM WEBSOCK_Class::WebSockPost(String ID, WEBSOCKEvent event, String offlineduration)
{
  // data orientation
  WSET_WSEM AFP_struct;
  WiFiClient client;
  HTTPClient http;
  http.begin(client, servername);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode;
  // Event (start,stop)
  // status (Success,Rejected)
  // message (Enjoy the ride, User is Anauthorized, Out of service, insufficient funds)
  switch (event)
  {
  case cardUID_REGISTER:
    /* code */
    httpResponseCode = http.POST("{\"nfc\": \"" + dtc(ID).CARDUID + "\",\"Duration\": \"" + "0" + "\",\"id\": \"" + dtc(ID).UNITID + "\",\"Event\":\"" + "Start" + "\"}");
    break;
  case cardUID_RELEASE:
    /* code */
    httpResponseCode = http.POST("{\"nfc\": \"" + dtc(ID).CARDUID + "\",\"Duration\": \"" + dtc(ID).TOTALTIME + "\",\"id\": \"" + dtc(ID).UNITID + "\",\"Event\":\"" + "Stop" + "\"}");
    break;
  case cardUID_RECORD:
    return (OfflinePost(ID));
    /* code */
    break;
  case cardUID_POST_OFFLINE:
    httpResponseCode = http.POST("{\"nfc\": \"" + ID + "\",\"Duration\": \"" + offlineduration + "\",\"id\": \"" + dtc(ID).UNITID + "\",\"Event\":\"" + "Stop" + "\"}");
    /* code */
    break;
  case cardUID_REG_STARTUP:
    /* code */
    httpResponseCode = http.POST("{\"id\": \"" + ID + "\",\"event\":\"" + "ScooterRestarted" + "\"}");
    break;
  default:
    break;
  }
  //Serial.println("reached here");
  String httpgetterbuffer = http.getString();
  Serial.println(httpgetterbuffer);
  if (httpgetterbuffer != NULL)
  {
    const char *statusbuff = JSONPARSE(httpgetterbuffer)["status"];
    const char *msgbuff = JSONPARSE(httpgetterbuffer)["message"];
    AFP_struct.statusMsg = String(statusbuff);
    AFP_struct.errorMsg = String(msgbuff);
  }
  else
  {
    AFP_struct.statusMsg = "Network Failure     ";
    AFP_struct.errorMsg =  "Network Failure     ";
  }

  if (AFP_struct.statusMsg == "Success")
  {
    AFP_struct.errortype = Successfully_register;
    http.end();
    return AFP_struct;
  }
  else
  {
    AFP_struct.errortype = registering_problem;
    http.end();
    return AFP_struct;
  }
  http.end();
  return AFP_struct;
}

// WSET_WSEM WEBSOCK_Class::OnlinePost(String cardUID, WEBSOCKEvent event)
// {
//   WSET_WSEM AFP_struct;
//   WiFiClient client;
//   HTTPClient http;
//   http.begin(client, servername);
//   http.addHeader("Content-Type", "application/json");
//   if (event == cardUID_REGISTER)
//   {
//     int httpResponseCode = http.POST("{\"nfc\": \"" + dtc(cardUID).CARDUID + "\",\"Duration\": \"" + "0" + "\",\"id\": \"" + dtc(cardUID).UNITID + "\",\"Event\":\"" + "Start" + "\"}");
//   }
//   if (event == cardUID_RELEASE)
//   {
//     int httpResponseCode = http.POST("{\"nfc\": \"" + dtc(cardUID).CARDUID + "\",\"Duration\": \"" + dtc(cardUID).TOTALTIME + "\",\"id\": \"" + dtc(cardUID).UNITID + "\",\"Event\":\"" + "Stop" + "\"}");
//   }
//   // Event (start,stop)
//   // status (Success,Rejected)
//   // message (Enjoy the ride, User is Anauthorized, Out of service, insufficient funds)

//   String httpgetterbuffer = http.getString();
//   Serial.println(httpgetterbuffer);
//   if (httpgetterbuffer != NULL)
//   {
//     const char *statusbuff = JSONPARSE(httpgetterbuffer)["status"];
//     const char *msgbuff = JSONPARSE(httpgetterbuffer)["message"];
//     AFP_struct.statusMsg = String(statusbuff);
//     AFP_struct.errorMsg = String(msgbuff);
//   }
//   else
//   {
//     AFP_struct.statusMsg = "NULL";
//     AFP_struct.errorMsg = "NULL";
//   }

//   if (AFP_struct.statusMsg == "Success")
//   {
//     AFP_struct.errortype = Successfully_register;
//     http.end();
//     return AFP_struct;
//   }
//   else
//   {
//     AFP_struct.errortype = registering_problem;
//     http.end();
//     return AFP_struct;
//   }
//   http.end();
// }
// post
// WSET_WSEM WEBSOCK_Class::OfflinePost(String cardUID, String duration)
// {
//   WSET_WSEM AFP_struct;
//   WiFiClient client;
//   HTTPClient http;
//   http.begin(client, servername);
//   http.addHeader("Content-Type", "application/json");
//   int httpResponseCode = http.POST("{\"nfc\": \"" + cardUID + "\",\"Duration\": \"" + duration + "\",\"id\": \"" + dtc(cardUID).UNITID + "\",\"Event\":\"" + "Stop" + "\"}");
//   String httpgetterbuffer = http.getString();
//   Serial.println(httpgetterbuffer);
//   if (httpgetterbuffer != NULL)
//   {
//     const char *statusbuff = JSONPARSE(httpgetterbuffer)["status"];
//     const char *msgbuff = JSONPARSE(httpgetterbuffer)["message"];
//     AFP_struct.statusMsg = String(statusbuff);
//     AFP_struct.errorMsg = String(msgbuff);
//   }
//   else
//   {
//     AFP_struct.statusMsg = "NULL";
//     AFP_struct.errorMsg = "NULL";
//   }
//   if (AFP_struct.statusMsg == "Success")
//   {
//     AFP_struct.errortype = Successfully_register;
//     http.end();
//     return AFP_struct;
//   }
//   else
//   {
//     AFP_struct.errortype = registering_problem;
//     http.end();
//     return AFP_struct;
//   }
//   http.end();
// }

// prepost
WSET_WSEM WEBSOCK_Class::OfflinePost(String cardUID)
{
  WSET_WSEM AFP_struct;
  if (WEBSOCK_MCIOS_class.LSrecorder(true, cardUID, dtc(cardUID).TOTALTIME))
  {
    AFP_struct.errorMsg = "Session recorded    ";
    AFP_struct.errortype = Successfully_recorded;
  }
  else
  {
    AFP_struct.errorMsg = "Session Not-recorded";
    AFP_struct.errortype = registering_problem;
  }
  return AFP_struct;
}

// only for testing
void WEBSOCK_Class::websockpost()
{
  WiFiClient client;
  HTTPClient http;
  http.begin(client, servername);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST("{\"nfc\": \"B567ACAD\",\"Duration\": \"5\",\"id\": \"string\",\"Event\":\"string\"}");
  if (httpResponseCode > 0)
  {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
  }
  else
  {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // free resources
  http.end();
}
