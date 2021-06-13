#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <WiFiManager.h>

const char* ssid = "Dialog 4G";
const char* password = "9871389389";
//const byte DNS_PORT = 53;

ESP8266WebServer server(80);
//DNSServer dnsServer;

//void dnsInit() {
//  dnsServer.setTTL(300);
//  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
//  // start DNS server for a specific domain name
//  dnsServer.start(DNS_PORT, "www.esp8266.local", WiFi.localIP());
//}

void mDNSInit() {
  //   Activate mDNS this is used to be able to connect to the server
  //   with local DNS hostmane esp8266.local
  if (!MDNS.begin("esp8266")) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");
}

// Serving Hello world
void getHelloWord() {
  server.send(200, "text/json", "{\"name\": \"Hello world\"}");
}

// Define routing
void restServerRouting() {
  server.on("/", HTTP_GET, []() {
    server.send(200, F("text/html"),
                F("Welcome to the REST Web Server"));
  });
  server.on(F("/helloWorld"), HTTP_GET, getHelloWord);
}

// Manage not found URL
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {
  Serial.begin(115200);
  //  WiFi.mode(WIFI_AP_STA);
  //  WiFi.begin(ssid, password);
  //  Serial.println("");
  //
  //  // Wait for connection
  //  while (WiFi.status() != WL_CONNECTED) {
  //    delay(500);
  //    Serial.print(".");
  //  }
  //  Serial.println("");
  //  Serial.print("Connected to ");
  //  Serial.println(ssid);
  //  Serial.print("IP address: ");
  //  Serial.println(WiFi.localIP());

  // WiFiManager
  WiFiManager wifiManager;
  wifiManager.resetSettings();
  wifiManager.autoConnect("ESP8266_AP");

  //  dnsInit();
  mDNSInit();

  // Set server routing
  restServerRouting();
  // Set not found response
  server.onNotFound(handleNotFound);
  // Start server
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  //  dnsServer.processNextRequest();
  MDNS.update();
  server.handleClient();
}
