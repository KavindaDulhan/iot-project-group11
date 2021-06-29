// Access point credentials
const char *config_ssid = "AirQI Config";
const char *config_password = "12345678";

const char *ssid = "AirQI AP";
const char *password = "12345678";

// MQTT server
const char *mqtt_server = "test.mosquitto.org";

const char *hello_topic = "entc/group11/project/hello";
const char *AQI_topic = "entc/group11/project/aqi";
const char *location_topic = "entc/group11/project/location";
const char *time_zone_topic = "entc/group11/project/tz";

// DNS names
const char *mdns_hostname = "esp8266";
const char *dns_hostname = "esp8266.local";

// LED color
unsigned long LEDColor;

// Serial input
String serialInput = ""; // a String to hold incoming data

// MQTT message
String mqttMsg = "";

// Buffers
#define BUF_SIZE 100
char _mqtt_buf[BUF_SIZE];
char _server_buf[BUF_SIZE];

// WiFi configs #TODO
struct station_config conf;
char old_ssid[33]; // SSID can be up to 32chars, => plus null term
char new_ssid[33];

// Location
float latVal;
float longVal;
String locationMsg;
DynamicJsonDocument jsonLocation(1024);

// AQI
int AQI;
String AQIMsg;
DynamicJsonDocument jsonAQI(1024);

// Time zone
int tzSign;
int tzHours;
int tzMinutes;
String timeZone;
long UTCOffset; // In seconds

// Previous times
unsigned long preLocMillis = 0;
unsigned long preSleepMillis = 0;

// WiFi manaager
WiFiManager wifiManager;

// Web server
ESP8266WebServer server(80);

// MQTT
WiFiClient espClient;
PubSubClient mqttClient(espClient);

// DNS server
DNSServer dnsServer;

// UDP client
WiFiUDP ntpUDP;

// Demo location change
int loc_iter = 0;

// American
const char *loc_array[] = {"San Jose", "San Salvador", "Guatemala City", "Merida", "Veracruz", "Hidalgo"}; // 6
const float lat_array[] = {9.9347, 13.7151, 14.6069, 20.9732, 18.0056, 20.0066};
const float long_array[] = {-84.0875, -89.1548, -90.5169, -89.6248, -94.5553, -99.2188};

// Indian
// char *loc_array[] = {"Vasai West India", "Bolivei East", "Vile Pale West", "Coloba", "Bandra Mumbai"}; // 5
// float lat_array[] = {19.3665, 19.2307, 19.1071, 18.9067, 19.0596};
// float long_array[] = {72.8155, 72.8567, 72.8368, 72.8147, 72.8295};
