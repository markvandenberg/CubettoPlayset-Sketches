#define PRIMO_BUZZER_PIN 13

////////////////////////////////////////////////////////////////////////////////

// Notes
#define PRIMO_NOTE_B0  31
#define PRIMO_NOTE_C1  33
#define PRIMO_NOTE_CS1 35
#define PRIMO_NOTE_D1  37
#define PRIMO_NOTE_DS1 39
#define PRIMO_NOTE_E1  41
#define PRIMO_NOTE_F1  44
#define PRIMO_NOTE_FS1 46
#define PRIMO_NOTE_G1  49
#define PRIMO_NOTE_GS1 52
#define PRIMO_NOTE_A1  55
#define PRIMO_NOTE_AS1 58
#define PRIMO_NOTE_B1  62
#define PRIMO_NOTE_C2  65
#define PRIMO_NOTE_CS2 69
#define PRIMO_NOTE_D2  73
#define PRIMO_NOTE_DS2 78
#define PRIMO_NOTE_E2  82
#define PRIMO_NOTE_F2  87
#define PRIMO_NOTE_FS2 93
#define PRIMO_NOTE_G2  98
#define PRIMO_NOTE_GS2 104
#define PRIMO_NOTE_A2  110
#define PRIMO_NOTE_AS2 117
#define PRIMO_NOTE_B2  123
#define PRIMO_NOTE_C3  131
#define PRIMO_NOTE_CS3 139
#define PRIMO_NOTE_D3  147
#define PRIMO_NOTE_DS3 156
#define PRIMO_NOTE_E3  165
#define PRIMO_NOTE_F3  175
#define PRIMO_NOTE_FS3 185
#define PRIMO_NOTE_G3  196
#define PRIMO_NOTE_GS3 208
#define PRIMO_NOTE_A3  220
#define PRIMO_NOTE_AS3 233
#define PRIMO_NOTE_B3  247
#define PRIMO_NOTE_C4  262
#define PRIMO_NOTE_CS4 277
#define PRIMO_NOTE_D4  294
#define PRIMO_NOTE_DS4 311
#define PRIMO_NOTE_E4  330
#define PRIMO_NOTE_F4  349
#define PRIMO_NOTE_FS4 370
#define PRIMO_NOTE_G4  392
#define PRIMO_NOTE_GS4 415
#define PRIMO_NOTE_A4  440
#define PRIMO_NOTE_AS4 466
#define PRIMO_NOTE_B4  494
#define PRIMO_NOTE_C5  523
#define PRIMO_NOTE_CS5 554
#define PRIMO_NOTE_D5  587
#define PRIMO_NOTE_DS5 622
#define PRIMO_NOTE_E5  659
#define PRIMO_NOTE_F5  698
#define PRIMO_NOTE_FS5 740
#define PRIMO_NOTE_G5  784
#define PRIMO_NOTE_GS5 831
#define PRIMO_NOTE_A5  880
#define PRIMO_NOTE_AS5 932
#define PRIMO_NOTE_B5  988
#define PRIMO_NOTE_C6  1047
#define PRIMO_NOTE_CS6 1109
#define PRIMO_NOTE_D6  1175
#define PRIMO_NOTE_DS6 1245
#define PRIMO_NOTE_E6  1319
#define PRIMO_NOTE_F6  1397
#define PRIMO_NOTE_FS6 1480
#define PRIMO_NOTE_G6  1568
#define PRIMO_NOTE_GS6 1661
#define PRIMO_NOTE_A6  1760
#define PRIMO_NOTE_AS6 1865
#define PRIMO_NOTE_B6  1976
#define PRIMO_NOTE_C7  2093
#define PRIMO_NOTE_CS7 2217
#define PRIMO_NOTE_D7  2349
#define PRIMO_NOTE_DS7 2489
#define PRIMO_NOTE_E7  2637
#define PRIMO_NOTE_F7  2794
#define PRIMO_NOTE_FS7 2960
#define PRIMO_NOTE_G7  3136
#define PRIMO_NOTE_GS7 3322
#define PRIMO_NOTE_A7  3520
#define PRIMO_NOTE_AS7 3729
#define PRIMO_NOTE_B7  3951
#define PRIMO_NOTE_C8  4186
#define PRIMO_NOTE_CS8 4435
#define PRIMO_NOTE_D8  4699
#define PRIMO_NOTE_DS8 4978

////////////////////////////////////////////////////////////////////////////////

void playPowerOnTune()
{
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_C6);
  delay(375);
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_E6);
  delay(125);
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_G6);
  delay(250);
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_E6);
  delay(125);
  noTone(PRIMO_BUZZER_PIN);
}


////////////////////////////////////////////////////////////////////////////////

void playHappyTune()
{
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_C6);
  delay(150);
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_E6);
  delay(150);
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_G6);
  delay(100);
  noTone(PRIMO_BUZZER_PIN);
}

void playSadTune()
{
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_G5);
  delay(150);
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_DS5);
  delay(150);
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_C5);
  delay(300);
  noTone(PRIMO_BUZZER_PIN);
}

void playPairedTune()
{
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_D6);
  delay(150);
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_F6);
  delay(150);
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_DS5);
  delay(100);
  noTone(PRIMO_BUZZER_PIN);
}

void playUnpairedTune()
{
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_G3);
  delay(250);
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_F3);
  delay(250);
  tone(PRIMO_BUZZER_PIN, PRIMO_NOTE_B2);
  delay(300);
  noTone(PRIMO_BUZZER_PIN);
}

void playForwardTune() {
  tone(PRIMO_BUZZER_PIN, 3000);
  delay(50);
  noTone(PRIMO_BUZZER_PIN);
}

void playLeftTune() {
  tone(PRIMO_BUZZER_PIN, 5000);
  delay(50);
  noTone(PRIMO_BUZZER_PIN);
}

void playRightTune() {
  tone(PRIMO_BUZZER_PIN, 4000);
  delay(50);
  noTone(PRIMO_BUZZER_PIN);
}
