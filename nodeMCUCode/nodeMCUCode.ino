#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* ssid = "Air Quality Index";
const char* password = "12345678";
ESP8266WebServer server(80);
//DNSServer dnsServer;

const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
char arq_char[100];
int arq_int;

/*
bool button_toggle = false;
bool old_button_toggle = false;
*/

struct station_config conf;
char old_ssid[33]; //ssid can be up to 32chars, => plus null term
char new_ssid[33]; //ssid can be up to 32chars, => plus null term

/*
StaticJsonDocument<300> JSONbuffer;
char JSONmessageBuffer[100];
JsonObject JSONencoder = JSONbuffer.createObject();
JSONencoder["longtitude"] = "80";
JSONencoder["latitude"] = "10";
JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
*/

const int capacity = JSON_OBJECT_SIZE(2);
DynamicJsonDocument gps_location(1024);

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

String long_val = "80";
String lat_val = "10";

char com_buf[100];

//void dnsInit() {
//  dnsServer.setTTL(300);
//  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
//  // start DNS server for a specific domain name
//  dnsServer.start(DNS_PORT, "www.esp8266.local", WiFi.localIP());
//}


ICACHE_RAM_ATTR void button_press(){
 Serial.println("Reconfiguring WiFI..");
 WiFiManager wifiManager;
 wifiManager.resetSettings();
 ESP.reset();
 ESP.restart();
}


void setup_wifi() {

  wifi_station_get_config(&conf);
  memcpy(old_ssid, conf.ssid, sizeof(conf.ssid));
  old_ssid[32] = 0; //nullterm in case of 32 char ssid
  Serial.print ("Old SSID: ");
  Serial.println(String(reinterpret_cast<char*>(old_ssid)));

  
  // WiFiManager
  WiFiManager wifiManager;
  wifiManager.autoConnect("Select WiFi Access Point");
  delay(1000);

  wifi_station_get_config(&conf);
  memcpy(new_ssid, conf.ssid, sizeof(conf.ssid));
  new_ssid[32] = 0; //nullterm in case of 32 char ssid
  Serial.print ("New SSID: ");
  Serial.println(String(reinterpret_cast<char*>(new_ssid)));
  
  WiFi.mode(WIFI_AP_STA);
  //Access point
  Serial.print("\nConfiguring access point...\n");
  /* You can remove the password parameter if you want the AP to be open. */
  Serial.println(WiFi.softAP(ssid, password) ? "Access point deployed successfully!" : "Access point deployment failed!");
  
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.println();

  if (String(reinterpret_cast<char*>(old_ssid))!=String(reinterpret_cast<char*>(new_ssid))){
    ESP.reset();
    ESP.restart();
  }
  
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    arq_char[i]=(char)payload[i];
  }
  arq_int = String(arq_char).toInt();
  Serial.print("ARQ of current location: ");
  Serial.print(arq_int);
  Serial.println();
  if (arq_int>=50){
    digitalWrite(BUILTIN_LED, LOW);
  }
  else {
    digitalWrite(BUILTIN_LED, HIGH);
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...\n");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("entcgroup11", "hello world");
      // ... and resubscribe
      client.subscribe("entc/group11/aqi");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    if (inChar==','){
      long_val = inputString;
      inputString = "";
    }
    else if (inChar == '\n' && long_val != "") {
      lat_val = inputString;
      inputString = "";
      stringComplete = true;
    }
    else{
      inputString += inChar;
    }
  }
}

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

void setCrossOrigin(){
    server.sendHeader(F("Access-Control-Allow-Origin"), F("*"));
    server.sendHeader(F("Access-Control-Max-Age"), F("600"));
    server.sendHeader(F("Access-Control-Allow-Methods"), F("PUT,POST,GET,OPTIONS"));
    server.sendHeader(F("Access-Control-Allow-Headers"), F("*"));
};

int receiveAQI() {
  return random(1, 100);
}

// Serving Hello world
void getAQI() {
  setCrossOrigin();
  int aqi = receiveAQI();
  snprintf(com_buf, 32, "{\"aqi\":%d}\r", aqi);
  server.send(200, "text/json", com_buf);
  Serial.print("Server Sent AQI of: ");
  Serial.println(aqi); 
}


// Define routing
void restServerRouting() {
  server.on("/", HTTP_GET, []() {
    server.send(200, F("text/html"),
                F("Welcome to the REST Web Server"));
  });
  server.on(F("/helloWorld"), HTTP_GET, getAQI);
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
  
  setup_wifi();

  //  dnsInit();
  mDNSInit();

  // Set server routing
  restServerRouting();
  // Set not found response
  server.onNotFound(handleNotFound);
  // Start server
  server.begin();
  Serial.println("HTTP server started\n");

  attachInterrupt(digitalPinToInterrupt(14),button_press,FALLING);  
  pinMode(BUILTIN_LED, OUTPUT); 
  digitalWrite(BUILTIN_LED, HIGH);
    
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // reserve 50 bytes for the inputString:
  inputString.reserve(50);
  
  gps_location["longtitude"]=long_val;
  gps_location["latitude"]=lat_val;
  serializeJson(gps_location , msg);
}

void loop(void) {
  //  dnsServer.processNextRequest();
  
  /*if (button_toggle != old_button_toggle){
    reconfig_wifi();

    //  dnsInit();
    mDNSInit();
  
    // Set server routing
    restServerRouting();
    // Set not found response
    server.onNotFound(handleNotFound);
    // Start server
    server.begin();
    Serial.println("HTTP server started");

    old_button_toggle = button_toggle;
    interrupts();
    }*/
  MDNS.update();
  server.handleClient();

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    gps_location["longtitude"]=long_val;
    gps_location["latitude"]=lat_val;
    serializeJson(gps_location , msg);
    long_val="";
    lat_val="";
    stringComplete = false;
  }
  
  unsigned long now = millis();
  if (now - lastMsg > 15000) {
    lastMsg = now;
    ++value;
    value=String("100").toInt();
    //snprintf (msg, MSG_BUFFER_SIZE, "I am awake");
    Serial.print("Current location: ");
    Serial.println(msg);
    client.publish("entc/group11/location",msg);
  }
    
}
