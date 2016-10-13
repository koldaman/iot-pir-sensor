/**************************************************************
  Zabaleni funkcionality pro WiFiClient (odesilani dat pres HTTPS)
 **************************************************************/
#include "Arduino.h"

#include <WiFiClientSecure.h>
#include <CustomWiFiClient.h>
#include <Ticker.h>
#include <LedIndicator.h>
#include <Constants.h>

const int LED_INDICATOR_PIN = 14;   // D4

CustomWiFiClient::CustomWiFiClient() {
   WiFiClientSecure _client;
   LedIndicator _ledIndicator;
   _host = "api.pushbullet.com";
   _httpPort = 443;
   // FIXME zmenit na cilove API_KEY
   _apiKey = Constants::PUSHBULLET_API_KEY();
}

void CustomWiFiClient::init() {
  _ledIndicator.init(LED_INDICATOR_PIN);
}

void CustomWiFiClient::sendData(String title, String message) {
   // zablikej behem requestu
   _ledIndicator.start(0.5);

   // volame zabezpecene - WiFiClientSecure, pro obycejne HTTP by stacil WiFiClient
   if (!_client.connect(_host, _httpPort)) {
     Serial.println("connection failed");
     _ledIndicator.stop();
     return;
   }

   // konstrukce url
   String url = "/v2/pushes";

   Serial.print("Requesting URL: ");
   Serial.println(url);

   String postData = String("type=note&") + "title=" + title + "&" + "body=" + message;

   // posli request
   _client.print(String("POST ") + url + " HTTP/1.1\r\n" +
                "Host: " + _host + "\r\n" +
                "Authorization: Bearer " + _apiKey + "\r\n" +
                "Connection: close\r\n" +
                "Content-Type: application/x-www-form-urlencoded;\r\n" +
                "Content-Length: " + postData.length() + "\r\n" +
                "\r\n" +
                postData + "\n");

    unsigned long timeout = millis();
    while (_client.available() == 0) {
      if (millis() - timeout > 8000) {
        Serial.println(">>> Client Timeout !");
        _client.stop();
        _ledIndicator.stop();
        return;
      }
    }

    // precteni vystupu volani skriptu
    while (_client.available()){
      String line = _client.readStringUntil('\r');
      Serial.print(line);
    }

    Serial.println();
    Serial.println("closing connection");

    // konec indikace posilani requestu
    _ledIndicator.stop();
}
