// Initialize WiFi
void initWiFi()
{
  // WiFiManager
  initWiFiManager();
  delay(1000);

  WiFi.mode(WIFI_AP_STA);
  initSoftAP();
}

// Initialize WiFi Manager
void initWiFiManager()
{
  wifiManager.setClass("invert");
  wifiManager.autoConnect(config_ssid);
}

// Initialize soft access point
void initSoftAP()
{
  Serial.println("\nConfiguring Soft AP ...\n");
  Serial.print("Access Point Deployment ");
  Serial.println(WiFi.softAP(ssid, password) ? "Success !!" : "Failed !!");

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP : ");

  String ssid = WiFi.softAPSSID();
  Serial.print("AP SSID : ");
  Serial.println(ssid);
}

// Attach interrupt to reset button
void initRButton()
{
  attachInterrupt(digitalPinToInterrupt(WIFI_R_PIN), pressRButton, FALLING);
}

// Actions for reset button press
ICACHE_RAM_ATTR void pressRButton()
{
  Serial.println("Button Pressed");
  wifiManager.resetSettings();
  ESP.reset();
  ESP.restart();
}

// Sleep
// if (now % 900000 == 0){
//     timeClient.update();
//     time_hour = timeClient.getHours();
//     if (time_hour >=0 || time_hour <=3){
//       time_minute = timeClient.getMinutes();
//       time_second = timeClient.getSeconds();
//       sleep_time = (3-time_hour)*60*60 + (59-time_minute)*60 + (59-time_second);
//       ESP.deepSleep(sleep_time * 1e6);
//     }
//   }
// }

// void initWiFi()
// {
//   const char *ssid = "Dialog 4G";
//   const char *password = "9871389389";

//   Serial.println();
//   Serial.print("Connecting to ");
//   Serial.println(ssid);

//   WiFi.begin(ssid, password);

//   while (WiFi.status() != WL_CONNECTED)
//   {
//     delay(500);
//     Serial.print(".");
//   }

//   randomSeed(micros());

//   Serial.println("");
//   Serial.println("WiFi Connected");
//   Serial.println("IP Address: ");
//   Serial.println(WiFi.localIP());
// }

// WiFiManager
// WiFiManager wifiManager;
// //  wifiManager.resetSettings();
// wifiManager.autoConnect("ESP8266_AP");
