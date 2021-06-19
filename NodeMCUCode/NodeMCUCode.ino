#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "_Variables.h"
#include "_Definitions.h"
#include "_Pins.h"

void setup(void)
{
  Serial.begin(BAUD_RATE);
  initLED();
  initWiFi();
  initMQTT();
  initLocation();
}

void loop(void)
{
  if (!mqttClient.connected())
  {
    reconnectMQTT();
  }
  mqttClient.loop();

  getLocation();
  publishLocation();
  adjustLED();
}
