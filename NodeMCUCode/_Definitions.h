// Default location
#define DEF_LAT 6.9271
#define DEF_LONG 79.8612 // Colombo
#define LOC_PREC 4
#define LOC_DELAY 60000 // 1 min

// Default time zone
#define DEF_TZ_S 2 // Positive
#define DEF_TZ_H 5
#define DEF_TZ_M 30
#define DEF_TZ_DELAY 900000 // 15 mins

// Default sleep time
#define START_H 0 // Sleep at 00:00
#define WAKE_H 3
#define WAKE_M 59
#define WAKE_S 59 // Wake up at 03:59:59

// Baud rate
#define BAUD_RATE 115200

// DNS port
#define DNS_PORT 53

// JSON
#define capacity JSON_OBJECT_SIZE(2)

// Coordinates
#define LAT 0
#define LONG 1

// Signs
#define POSITIVE 2
#define NEGATIVE 3

// Device modes
#define NORMAL_MODE 4
#define DEMO_MODE 5

// Demo location change
#define NUM_LOC 6
#define DEMO_LOC_DELAY 10000 // 10 secs

// Colors
#define OFF 0x000000
#define WHITE 0xFFFFFF

#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF

#define CYAN 0x00FFFF
#define MAGENTA 0xFF00FF
#define YELLOW 0xFFFF00

#define ORANGE 0xFF8000

// Musical notes
#define NOTE_A1 550
#define NOTE_AS1 582
#define NOTE_B1 617
#define NOTE_C1 654
#define NOTE_CS1 693
#define NOTE_D1 734
#define NOTE_DS1 777
#define NOTE_E1 824
#define NOTE_F1 873
#define NOTE_FS1 925
#define NOTE_G1 980
#define NOTE_GS1 1003
#define NOTE_A2 1100
#define NOTE_AS2 1165
#define NOTE_B2 1234
#define NOTE_C2 1308
#define NOTE_CS2 1385
#define NOTE_D2 1555

// Tempo
#define TEMPO 40

// Tone length
#define L_HALF 5
#define L_ONE 10
#define L_ONE_HALF 15
#define L_TWO 20
#define L_TWO_HALF 25
