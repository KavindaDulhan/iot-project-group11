// Initialize buzzer
void initBuzzer()
{
  pinMode(BUZZER_PIN, OUTPUT);
  buzzer(2);
}

// Beep buzzer
void buzzer(int count)
{
  if (count > 0)
  {
    for (int i = 0; i < count; i++)
    {
      tone(BUZZER_PIN, NOTE_C2);
      delay(100);
      noTone(BUZZER_PIN);
      delay(100);
    }
  }
}

// Set buzzer tone
void setTone(int note, int length)
{
  tone(BUZZER_PIN, note, TEMPO * length);
  delay(TEMPO * length);
  noTone(BUZZER_PIN);
}

// Play Harry Potter theme
void playHP()
{
  setTone(NOTE_B1, L_ONE);
  setTone(NOTE_E1, L_ONE_HALF);
  setTone(NOTE_G1, L_HALF);
  setTone(NOTE_F1, L_ONE);
  setTone(NOTE_E1, L_TWO);
  setTone(NOTE_B2, L_ONE);
  setTone(NOTE_A2, L_TWO_HALF);
  setTone(NOTE_FS1, L_TWO_HALF);
  setTone(NOTE_E1, L_ONE_HALF);
  setTone(NOTE_G1, L_HALF);
  setTone(NOTE_F1, L_ONE);
  setTone(NOTE_DS1, L_TWO);
  setTone(NOTE_F1, L_ONE);
  setTone(NOTE_B1, L_TWO_HALF);
  delay(2000);
}
