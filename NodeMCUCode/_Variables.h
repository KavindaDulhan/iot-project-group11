// Access point credentials
const char *config_ssid = "AirQI Config";
const char *config_password = "12345678";

const char *ssid = "AirQI AP";
const char *password = "12345678";

// WiFi configs
// struct station_config conf;
// ssid can be up to 32chars, => plus null term
// char old_ssid[33];
// char new_ssid[33];

// MQTT server
const char *mqtt_server = "test.mosquitto.org";

const char *hello_topic = "entc/group11/project/hello";
const char *AQI_topic = "entc/group11/project/aqi";
const char *location_topic = "entc/group11/project/location";

// LED color
unsigned long LEDColor;

// Serial input
String serialInput = ""; // a String to hold incoming data

// MQTT message
String mqttMsg = "";

// Buffers
#define BUF_SIZE 50
char _mqtt_buf[BUF_SIZE];
char _server_buf[BUF_SIZE];

// Location
float latVal;
float longVal;
String locationMsg;
DynamicJsonDocument jsonLocation(1024);

// Predefined locations
char *loc_array[] = {"Vasai West India", "Bolivei East", "Vile Pale West", "Coloba", "Bandra Mumbai"};
int lat_array[] = {19.3665, 19.2307, 19.1071, 18.9067, 19.0596};
int long_array[] = {72.8155, 72.8567, 72.8368, 72.8147, 72.8295};

// AQI
int AQI;
String AQIMsg;
DynamicJsonDocument jsonAQI(1024);

// Time (Location)
unsigned long preLocMillis = 0;

// WiFi Manager
WiFiManager wifiManager;

// Web server
ESP8266WebServer server(80);

// MQTT
WiFiClient espClient;
PubSubClient mqttClient(espClient);

DNSServer dnsServer;
