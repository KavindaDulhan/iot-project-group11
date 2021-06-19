// Initialize WiFi
void initWiFi()
{
  const char *ssid = "Dialog 4G";
  const char *password = "9871389389";

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
}

// // WiFiManager
// WiFiManager wifiManager;
// //  wifiManager.resetSettings();
// wifiManager.autoConnect("ESP8266_AP");

// void setup_wifi()
// {

//   wifi_station_get_config(&conf);
//   memcpy(old_ssid, conf.ssid, sizeof(conf.ssid));
//   old_ssid[32] = 0; //nullterm in case of 32 char ssid
//   Serial.print("Old SSID: ");
//   Serial.println(String(reinterpret_cast<char *>(old_ssid)));

//   // WiFiManager
//   WiFiManager wifiManager;
//   wifiManager.autoConnect("Select WiFi Access Point");
//   delay(1000);

//   wifi_station_get_config(&conf);
//   memcpy(new_ssid, conf.ssid, sizeof(conf.ssid));
//   new_ssid[32] = 0; //nullterm in case of 32 char ssid
//   Serial.print("New SSID: ");
//   Serial.println(String(reinterpret_cast<char *>(new_ssid)));

//   WiFi.mode(WIFI_AP_STA);
//   //Access point
//   Serial.print("\nConfiguring access point...\n");
//   /* You can remove the password parameter if you want the AP to be open. */
//   Serial.println(WiFi.softAP(ssid, password) ? "Access point deployed successfully!" : "Access point deployment failed!");

//   IPAddress myIP = WiFi.softAPIP();
//   Serial.print("AP IP address: ");
//   Serial.println(myIP);
//   Serial.println();

//   if (String(reinterpret_cast<char *>(old_ssid)) != String(reinterpret_cast<char *>(new_ssid)))
//   {
//     ESP.reset();
//     ESP.restart();
//   }
// }

// ICACHE_RAM_ATTR void button_press()
// {
//   Serial.println("Reconfiguring WiFI..");
//   WiFiManager wifiManager;
//   wifiManager.resetSettings();
//   ESP.reset();
//   ESP.restart();
// }
