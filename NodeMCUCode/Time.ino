// Initialize time zone
void initTimeZone()
{
  // Set defaults
  tzSign = DEF_TZ_S;
  tzHours = DEF_TZ_H;
  tzMinutes = DEF_TZ_M;

  setUTCOffSet();
}

// Update time zone from MQTT message
int updateTimeZone()
{
  timeZone = mqttMsg;

  String sign = timeZone.substring(0, 1);
  tzHours = timeZone.substring(1, 3).toInt();
  tzMinutes = timeZone.substring(4, 6).toInt();

  if (sign.equals("-"))
  {
    tzSign = NEGATIVE;
  }
  else
  {
    tzSign = POSITIVE;
  }

  setUTCOffSet();
}

// Set UTC offset in seconds
void setUTCOffSet()
{
  switch (tzSign)
  {
  case POSITIVE:
    UTCOffset = tzHours * 3600 + tzMinutes * 60;
    break;
  case NEGATIVE:
    UTCOffset = -(tzHours * 3600 + tzMinutes * 60);
    break;
  }
  printTimeZone();
}

// Print time zone to Serial monitor
void printTimeZone()
{
  Serial.print("Current Time Zone : ");
  Serial.print(timeZone);
  Serial.print(" ");
  Serial.println(UTCOffset);
}
