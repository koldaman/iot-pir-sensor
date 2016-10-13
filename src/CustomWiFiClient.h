/**************************************************************
Zabaleni funkcionality pro WiFiClient (odesilani dat pres HTTPS)
**************************************************************/

#include <WiFiClientSecure.h>
#include <LedIndicator.h>

class CustomWiFiClient {
public:
   CustomWiFiClient();
   void init();
   void sendData(String title, String message);
private:
   char* _host;
   int   _httpPort;
   char* _apiKey;
   WiFiClientSecure _client;
   LedIndicator     _ledIndicator;
   double getVbat();
};
