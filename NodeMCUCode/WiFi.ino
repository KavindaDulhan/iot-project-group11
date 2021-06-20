// Initialize WiFi
void initWiFi()
{
  saveOldSSID();

  // WiFi manager
  initWiFiManager();
  delay(5000);

  // Soft AP
  saveNewSSID();
  initSoftAP();

  // TODO: Refactor this
  if (strcmp(old_ssid, new_ssid))
  {
    ESP.restart();
  }
}

// Save old SSID #TODO
void saveOldSSID()
{
  wifi_station_get_config(&conf);
  memcpy(old_ssid, conf.ssid, sizeof(conf.ssid));
  old_ssid[32] = 0; // Nullterm in case of 32 char SSID
}

// Save new SSID #TODO
void saveNewSSID()
{
  wifi_station_get_config(&conf);
  memcpy(new_ssid, conf.ssid, sizeof(conf.ssid));
  new_ssid[32] = 0; // Nullterm in case of 32 char SSID
}

// Initialize WiFi manager
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
  removeAlertLevel();
  Serial.println("\nWiFi Reset Button Pressed\n");
  wifiManager.resetSettings();
  ESP.restart();
}

// Deep sleep at predefined hours #TEST
void enterDeepSleep()
{
  if (millis() - preSleepMillis > DEF_TZ_DELAY)
  {
    preSleepMillis = millis();

    NTPClient timeClient(ntpUDP, "pool.ntp.org", UTCOffset);

    timeClient.update();
    int tHour = timeClient.getHours();

    if (tHour >= START_H || tHour <= WAKE_H)
    {
      int tMinute = timeClient.getMinutes();
      int tSecond = timeClient.getSeconds();

      long sleepTime = (WAKE_H - tHour) * 3600 + (WAKE_H - tMinute) * 60 + (WAKE_S - tSecond);

      Serial.print("\nEntering Deep Sleep Mode for : ");
      Serial.print(sleepTime);
      Serial.println(" seconds");

      ESP.deepSleep(sleepTime * 1e6);
    }
  }
}
