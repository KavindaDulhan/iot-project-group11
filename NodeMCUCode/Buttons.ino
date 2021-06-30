// Attach interrupts to buttons
void initButtons()
{
  attachInterrupt(digitalPinToInterrupt(WIFI_R_PIN), pressedWiFiR, FALLING);
  attachInterrupt(digitalPinToInterrupt(LOC_MS_PIN), pressedLocMS, FALLING);
}

// Actions for reset button press
ICACHE_RAM_ATTR void pressedWiFiR()
{
  wifiReset();
}

// Attach for location mode switch button
ICACHE_RAM_ATTR void pressedLocMS()
{
  switchLocationMode();
}
