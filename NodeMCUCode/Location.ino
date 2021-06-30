// Initialize location
void initLocation()
{
  // Set defaults
  latVal = DEF_LAT;
  longVal = DEF_LONG;
  loc_mode = NORMAL_MODE;

  parseLocationJSON();
}

// Get location Serial inputs
void getSerialLocation()
{
  // Input pattern: latitude, longitude
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

      // Handle invalid inputs
      if (latVal == 0 || longVal == 0)
      {
        Serial.println("Serial Error. Reset!");
        resetLocation();
      }
      else if (latVal > 90 || latVal < -90 || longVal > 180 || longVal < -180)
      {
        Serial.println("Invalid Location. Reset!");
        resetLocation();
      }
      else
      {
        Serial.print("Serial Message Received : ");
        parseLocationJSON();
        publishLocation();
      }
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

// Publish location to MQTT recurrently
void publishLocationRecur()
{
  if (!preLocMillis || (millis() - preLocMillis > LOC_DELAY))
  {
    publishLocation();
  }
}

// Publish location to MQTT
void publishLocation()
{
  preLocMillis = millis();
  publishMQTT(location_topic);
  printLocation();
}

// Reset location to default
void resetLocation()
{
  initLocation();
  publishLocation();
}

// Change Location for Demo
void demoLocationChange()
{
  if (!preLocMillis || (millis() - preLocMillis > DEMO_LOC_DELAY))
  {
    preLocMillis = millis();
    latVal = lat_array[loc_iter];
    longVal = long_array[loc_iter];

    if (loc_iter < (NUM_LOC - 1))
    {
      loc_iter++;
    }
    else
    {
      loc_iter = 0;
    }

    Serial.print("\nTravelled to : ");
    Serial.println(loc_array[loc_iter]);

    parseLocationJSON();
    publishLocation();
  }
}

// Process location data
void processLocation()
{
  switch (loc_mode)
  {
  case NORMAL_MODE:
    getSerialLocation();
    publishLocationRecur();
    break;

  case DEMO_MODE:
    demoLocationChange();
    break;
  }
}

// Switch location mode
void switchLocationMode()
{
  switch (loc_mode)
  {
  case NORMAL_MODE:
    removeAlertLevel();
    Serial.println("\nLocation Mode Switch Button Pressed\n");
    Serial.println("Starting Demo Journey...");
    playHP();

    loc_mode = DEMO_MODE;
    break;

  case DEMO_MODE:
    Serial.println("\nLocation Mode Switch Button Pressed\n");
    Serial.println("Resetting...");

    loc_mode = NORMAL_MODE;
    ESP.reset();
    break;
  }
}
