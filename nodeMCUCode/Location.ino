
// Initialize location
void initLocation()
{
  // Set defaults
  latVal = DEF_LAT;
  longVal = DEF_LONG;

  parseLocationJSON();
}

// Get location Serial inputs
void getLocation()
{
  while (Serial.available())
  {
    // Get the new byte
    char inChar = (char)Serial.read();

    // Add it to the serialInput
    if (inChar == ',')
    {
      assignCoordinate(LAT);
      serialInput = "";
    }
    else if (inChar == '\n')
    {
      assignCoordinate(LONG);
      serialInput = "";
      parseLocationJSON();
    }
    else
    {
      serialInput += inChar;
    }
  }
}

// Assign coodinate values
void assignCoordinate(int type)
{
  float serialVal = serialInput.toFloat();
  if (serialVal != 0)
  {
    switch (type)
    {
    case LAT:
      latVal = serialVal;
      break;
    case LONG:
      longVal = serialVal;
      break;
    }
  }
}

// Parse location as a JSON
void parseLocationJSON()
{
  jsonLocation["latitude"] = String(latVal, LOC_PREC);
  jsonLocation["longitude"] = String(longVal, LOC_PREC);

  locationMsg = "";
  serializeJson(jsonLocation, locationMsg);
  printLocation();
}

// Print location to Serial monitor
void printLocation()
{
  Serial.print("Current Location : ");
  Serial.println(locationMsg);
}

// Publish location to MQTT
void publishLocation()
{
  if (millis() - preLocMillis > LOC_DELAY)
  {
    preLocMillis = millis();
    publishMQTT(location_topic);
    printLocation();
  }
}

// Reset location to default
void resetLocation()
{
  initLocation();
}
