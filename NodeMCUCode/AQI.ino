// Update AQI from MQTT message
int updateAQI()
{
  AQI = mqttMsg.toInt();

  if (AQI > 0)
  {
    parseAQIJSON();
    changeAlertLevel();
  }
  else
  {
    removeAlertLevel();
  }
}

// Parse AQI as a JSON
void parseAQIJSON()
{
  jsonAQI["aqi"] = String(AQI);

  AQIMsg = "";
  serializeJson(jsonAQI, AQIMsg);
  printAQI();
}

// Print AQI to Serial monitor
void printAQI()
{
  Serial.print("Current AQI : ");
  Serial.println(AQIMsg);
}

// Change LED alert color
void changeAlertLevel()
{
  if (AQI <= 50)
  {
    LEDColor = GREEN;
  }
  else if (AQI <= 100)
  {
    LEDColor = ORANGE;
  }
  else
  {
    LEDColor = RED;
  }
}

// Remove LED alert color
void removeAlertLevel()
{
  LEDColor = WHITE;
}
