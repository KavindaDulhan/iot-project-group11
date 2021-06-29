// Imports
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include "_Variables.h"
#include "_Definitions.h"
#include "_Pins.h"

// Initializations
void setup(void)
{
  Serial.begin(BAUD_RATE);
  initLED();
  initWiFi();
  initRButton();
  initMQTT();
  initLocation();
  initTimeZone();
  initServer();
}

// Main code
void loop(void)
{
  // MQTT
  if (!mqttClient.connected())
  {
    reconnectMQTT();
  }
  mqttClient.loop();

  // Web server
  handleServerClients();

  // Location
  // getLocationSerial();
  // publishLocationRec();
  demoLocationChange();

  // Sleep
  enterDeepSleep();
}
