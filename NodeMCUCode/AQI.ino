// Update AQI from MQTT message
int updateAQI()
{
  AQI = mqttMsg.toInt();

  if (AQI > 0)
  {
    parseAQIJSON();
    printAQI();
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
}

// Print AQI to Serial monitor
void printAQI()
{
  Serial.print("Current AQI : ");
  Serial.println(AQI);
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
  adjustLED();
}

// Remove LED alert color
void removeAlertLevel()
{
  LEDColor = WHITE;
  adjustLED();
}
