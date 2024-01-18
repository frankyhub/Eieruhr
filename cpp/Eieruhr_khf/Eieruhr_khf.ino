/************************************************************************************************* 
                                      PROGRAMMINFO
************************************************************************************************** 
Funktion: Eieruhr
**************************************************************************************************
Version: 22.02.2022
**************************************************************************************************
Board: NANO V3
64 LED Matrix Display
**************************************************************************************************
C++ Arduino IDE V1.8.13
**************************************************************************************************
Einstellungen:
https://dl.espressif.com/dl/package_esp32_index.json
http://dan.drown.org/stm32duino/package_STM32duino_index.json
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json
**************************************************************************************************
 LIB https://github.com/MajicDesigns/MD_MAX72XX

https://www.makerguides.com/max7219-led-dot-matrix-display-arduino-tutorial/
**************************************************************************************************
Funktion:

Schalter 1 ist der Einschalter und mit Schalter 2 kann zwischen 3 Zeiten gewählt werden, 5 Minuten, 
5 Minuten 30 Sekunden und 6 Minuten. Beim Einschalten ertönen, je nach gewählter Zeit, unterschiedliche 
Signale. Zusätzlich wird bei gewählten 5,5 Minuten zusätzlich ein Signal bei abgelaufenen 5 Minuten, 
bei gewählten 6 Minuten ein Signal bei 5 und 5,5 Minuten ausgegeben. Diese Zeiten können softwareseitig 
in nachfolgender Zeile verändert werden:
int pause_5 = 136; int pause_5_5 = 149; int pause_6 = 162;
Die Zeiten für die Zwischensignale in der Zeile:
byte beep_1 = 50; byte beep_2 = 44; byte beep_3 = 50;
Beide Zeilen befinden sich im Deklarationsteil des Sketches.

Schalter 1 = 8
Schalter 2 = 7
Buzzer     = 9

SS = PIN 10   
MOSI = PIN 11 
SCK = PIN 13
**************************************************************************************************/

#include <MD_MAX72xx.h >

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 2 // Anzahl Segmente

#define CLK_PIN 13  // or SCK
#define DATA_PIN 11 // or MOSI
#define CS_PIN 10   // or SS

MD_MAX72XX su = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);


// Adressen für die Koerner
byte zeile1 = 0; byte reihe1 = 0;
byte zeile2 = 0; byte reihe2 = 0;

int pause_5 = 136; int pause_5_5 = 149; int pause_6 = 162; // Zeiten Ablauf
int pause_1 = pause_5_5;
byte beep_1 = 50; byte beep_2 = 44; byte beep_3 = 50; // Zwischenzeiten 5 bei 5:30, 5 bei 6, 5:30 bei 6

byte ton_ausgang = 9;
byte schalter1 = 8; byte schalter2 = 7; // Schalter fuer Zeiteinstellung

int zw_unten = 0;     // Zaelwert unten, Position unten
int zw_oben = 0;      // Zaelwert oben, Zaelwert Hauptschleife und Position oben
byte zw_laenge = 0;   // Waeglaenge des Korn
byte zw_anzahl = 0;   // Anzahl der Koerner
byte zw_laenge_1 = 0; // Weglaenge des Korn in der Schleife
byte zw_anzahl_1 = 0; // Anzahl der Koerner in der Schleife
byte zw_position = 7; // Position Korn

// Unterer Rhombus, 9 -> Stererelement, X -> Fallhöhe, Y -> Anzahl Wiederholungen, Z... -> Positionen
// X und Y gelten immer bis zum naechste Steuerelement.

byte unten [] = {9, 8, 01, 00,                                     //1   Zeile 01
                 9, 07, 02, 01, 10,                                //2   Zeile 02
                 9, 07, 01, 11, 9, 06, 02, 20, 02,                 //1+2 Zeile 03
                 9, 06, 04, 12, 21, 30, 03,                        //4   Zeile 04
                 9, 06, 01, 22, 9, 05, 04, 13, 31, 40, 04,         //1+4 Zeile 05
                 9, 05, 06, 23, 32, 14, 41, 05, 50,                //6   Zeile 06
                 9, 05, 01, 33, 9, 04, 06, 24, 42, 15, 51, 06, 60, //1+6 Zeile 07
                 9, 04, 06, 34, 43, 25, 52, 16, 61, 07, 70,        //6   Zeile 08
                 9, 04, 01, 44, 9, 03, 04, 35, 53, 26, 62, 17, 71, //1+4 Zeile 09
                 9, 03, 04, 45, 54, 36, 63, 27, 72,                //4   Zeile 10
                 9, 03, 01, 55, 9, 02, 03, 46, 64, 37, 73,         //1+3 Zeile 11
                 9, 02, 03, 56, 65, 74, 47,                        //3   Zeile 12
                 9, 02, 01, 66, 9, 01, 01, 75, 57,                 //1+1 Zeile 13
                 9, 01, 01, 67, 76,                                //1   Zeile 14
                 9, 0, 0, 77                                       //0   Zeile 14
                };

// Oberer Rhombus, Positionen

byte oben [] = {77,                              // Zeile 01
                67, 76,                          // Zeile 02
                66, 75, 57,                      // Zeile 03
                56, 65, 74, 47,                  // Zeile 04
                55, 46, 64, 37, 73,              // Zeile 05
                45, 54, 36, 63, 27, 72,          // Zeile 06
                44, 35, 53, 26, 62, 17, 71,      // Zeile 07
                34, 43, 25, 52, 16, 61, 07, 70,  // Zeile 08
                33, 24, 42, 15, 51, 06, 60,      // Zeile 09
                23, 32, 14, 41, 05, 50,          // Zeile 10
                22, 13, 31, 40, 04,              // Zeile 11
                12, 21, 30, 03,                  // Zeile 12
                11, 20, 02,                      // Zeile 13
                01, 10,                          // Zeile 14
                00                               // Zeile 15
               };

void setup() {
  su.begin(); su.control(MD_MAX72XX::INTENSITY, 0); // Start MD_MAX72xx.h; Helligkeit Minimum

  // Benoetigte Ports
  pinMode (ton_ausgang, OUTPUT);
  pinMode (schalter1, INPUT); digitalWrite (schalter1, HIGH);
  pinMode (schalter2, INPUT); digitalWrite (schalter2, HIGH);

}

void loop() {

  su.clear();  delay (100);  su.clear(); // Loeschen Anzeige

  // Zuordnung der Verzoegerungszeiten

  if (digitalRead (schalter1 ) == 0) {
    pause_1 = pause_5;
  };
  if (digitalRead (schalter2) == 0) {
    pause_1 = pause_6;
  }

  // Tonsignal / Lichtsignal für eingestellte Zeit

  if (pause_1 == pause_5 ) {
    su.setPoint (4, 12, 1); // Mitte
    tone(ton_ausgang, 500); delay (1000); noTone(ton_ausgang);
    delay (2000);
  };

  if (pause_1 == pause_5_5) {
    su.setPoint (6, 10, 1); // Links
    su.setPoint (2, 14, 1); // Rechts
    tone(ton_ausgang, 500); delay (1000); noTone(ton_ausgang); delay (1000);
    tone(ton_ausgang, 500); delay (1000); noTone(ton_ausgang);
    delay (1000);
  };

  if (pause_1 == pause_6) {
    su.setPoint (4, 12, 1); // Mitte
    su.setPoint (6, 10, 1); // Links
    su.setPoint (2, 14, 1); // Rechts
    tone(ton_ausgang, 500); delay (1000); noTone(ton_ausgang); delay (1000);
    tone(ton_ausgang, 500); delay (1000); noTone(ton_ausgang); delay (1000);
    tone(ton_ausgang, 500); delay (1000); noTone(ton_ausgang);
  };

  //Fuellen oberer Rhombus

  zw_oben = 0;

  do {
    zeile2 = oben [zw_oben] / 10; reihe2 = (oben [zw_oben] % 10) + 8;
    su.setPoint(zeile2, reihe2, 1);
    zw_oben++;
  }
  while (zw_oben != 64);

  // Lesen Steuerzeichen und Ausgabe der Koerner

  zw_unten = 0; zw_oben = 0;

  do {
    if (unten [zw_unten] == 9) {
      zw_unten++; zw_laenge = unten [zw_unten]; zw_unten++; zw_anzahl = unten [zw_unten]; zw_unten++;
    };

    zw_anzahl_1 = zw_anzahl;// Uebernahme der Daten fuer aeußeren Zyklus (Anzahl der Ketten)

    do {

      zw_laenge_1 = zw_laenge; zw_position = 7;  // Uebernahme der Daten fuer inneren Zyklus (Anzahl Koerner der Kette und Ausgabe)

      do {
        if (zw_laenge_1 != 0) {
          su.setPoint (zw_position, zw_position, 1); delay (pause_1);
          su.setPoint (zw_position, zw_position, 0); zw_position--;
          zw_laenge_1--;
        }
      }
      while (zw_laenge_1 != 0);

      if (zw_anzahl_1 != 0) {
        zw_anzahl_1--;
      };
      delay (pause_1 * 5);
    }
    while (zw_anzahl_1 != 0);

    // Ausgabe der gefallenen Koerner

    zeile1 = unten [zw_unten] / 10; reihe1 = unten [zw_unten] % 10;
    su.setPoint(zeile1, reihe1, 1);
    zw_unten++;
    zeile2 = oben [zw_oben] / 10; reihe2 = (oben [zw_oben] % 10) + 8;
    su.setPoint(zeile2, reihe2, 0);
    zw_oben++;

    // Ausgabe Signal Zwischenzeiten

    if (zw_oben == beep_1 && pause_1 == pause_5_5) {
      tone(ton_ausgang, 500);
      delay (1000);
      noTone(ton_ausgang);
    }

    if (zw_oben == beep_2 && pause_1 == pause_6) {
      tone(ton_ausgang, 500);
      delay (1000);
      noTone(ton_ausgang);
    }
    if (zw_oben == beep_3 && pause_1 == pause_6) {
      tone(ton_ausgang, 500);
      delay (1000);
      noTone(ton_ausgang);
    }
  }
  while (zw_oben != 64);

  // Ausgabe Endsignal

  tone(ton_ausgang, 500); delay (1000);
  noTone(ton_ausgang); delay (500);
  tone(ton_ausgang, 800); delay (1000);
  noTone(ton_ausgang); delay (500);
  tone(ton_ausgang, 500); delay (1000);
  noTone(ton_ausgang); delay (500);

  su.clear();

  // "Bildschirm und Batterieschoner" do while wird nicht verlassen.

  do {
    zeile1 = random(8); reihe1 = random (16);
    su.setPoint(zeile1, reihe1, 1); delay (100);
    su.setPoint(zeile1, reihe1, 0);
  }
  while (zw_oben != 0);
}
