// Initialize WiFi
void initWiFi()
{
  saveOldSSID();

  // WiFiManager
  initWiFiManager();
  delay(5000);

  saveNewSSID();
  initSoftAP();

  // Todo: Refactor this
  if (strcmp(old_ssid, new_ssid))
  {
    ESP.restart();
  }
}

// Save old SSID #ToDo
void saveOldSSID()
{
  wifi_station_get_config(&conf);
  memcpy(old_ssid, conf.ssid, sizeof(conf.ssid));
  old_ssid[32] = 0; // Nullterm in case of 32 char SSID
}

// Save new SSID #ToDo
void saveNewSSID()
{
  wifi_station_get_config(&conf);
  memcpy(new_ssid, conf.ssid, sizeof(conf.ssid));
  new_ssid[32] = 0; // Nullterm in case of 32 char SSID
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
  WiFi.mode(WIFI_AP_STA);
  Serial.println("\nConfiguring Soft AP...");
  Serial.print("Access Point Deployment : ");
  Serial.println(WiFi.softAP(ssid, password) ? "Success!" : "Failed!");

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP : ");
  Serial.println(myIP);

  String ssid = WiFi.softAPSSID();
  Serial.print("AP SSID : ");
  Serial.println(ssid);
  Serial.println();
}

// Attach interrupt to reset button
void initRButton()
{
  attachInterrupt(digitalPinToInterrupt(WIFI_R_PIN), pressRButton, FALLING);
}

// Actions for reset button press
ICACHE_RAM_ATTR void pressRButton()
{
  LEDColor = WHITE;
  Serial.println("\nWiFi Reset Button Pressed\n");
  wifiManager.resetSettings();
  ESP.restart();
}

//  if (now - lastMsg2 > 900000){
//     lastMsg2 = now;
//     NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
//     timeClient.update();
//     time_hour = timeClient.getHours();
//     if (time_hour >=0 || time_hour <=3){
//       time_minute = timeClient.getMinutes();
//       time_second = timeClient.getSeconds();
//       sleep_time = (3-time_hour)*60*60 + (59-time_minute)*60 + (59-time_second);
//       Serial.print ("\nEntering deep sleep mode for ");
//       Serial.print (sleep_time);
//       Serial.println (" seconds");
//       Serial.println ();
//       ESP.deepSleep(sleep_time * 1e6);
//     }
//   }
