// Initialize LED
void initLED()
{
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
  LEDColor = WHITE;
}

// Change LED color
void colorRGBLED(unsigned long RGB)
{
  // Convert HEX value to RGB
  int R = RGB >> 16;
  int G = (RGB & 0x00ff00) >> 8;
  int B = (RGB & 0x0000ff);

  analogWrite(LED_R_PIN, 1023 - R * 4);
  analogWrite(LED_G_PIN, 1023 - G * 4);
  analogWrite(LED_B_PIN, 1023 - B * 4);
}

// Adjust LED to global color
void adjustLED()
{
  colorRGBLED(LEDColor);
}

// Test LED
void testLED()
{
  colorRGBLED(RED);
  delay(1000);

  colorRGBLED(YELLOW);
  delay(1000);

  colorRGBLED(GREEN);
  delay(1000);
}
