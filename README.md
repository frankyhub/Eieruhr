## Eieruhr
Eieruhr mit zwei 64LED-Matrix-Modulen

Mit diesem Projekt wird eine Eieruhr mit zwei 64LED-Matrix-Modulen realisiert. Schalter 1 ist der Einschalter und mit Schalter 2 kann zwischen 3 Zeiten gewählt werden, 5 Minuten, 5 Minuten 30 Sekunden und 6 Minuten. Beim Einschalten ertönen, je nach gewählter Zeit, unterschiedliche Signale. Zusätzlich wird bei gewählten 5,5 Minuten zusätzlich ein Signal bei abgelaufenen 5 Minuten, bei gewählten 6 Minuten ein Signal bei 5 und 5,5 Minuten ausgegeben. Diese Zeiten können softwareseitig in nachfolgender Zeile verändert werden:
int pause_5 = 136; int pause_5_5 = 149; int pause_6 = 162;
Die Zeiten für die Zwischensignale in der Zeile:
byte beep_1 = 50; byte beep_2 = 44; byte beep_3 = 50;
Beide Zeilen befinden sich im Deklarationsteil des Sketches.

![Eieruhr](https://github.com/frankyhub/Eieruhr/blob/main/pic/eieruhr.png)

Eieruhr Anzeige mit einer 2 x 64 LED Matrix

---
# Hardware
Die Hardware für die Eieruhr

+ 1 x NANO V31
+ 1 x LM2536
+ 2 x 64 LED Matrix Module
+ 1 x Buzzer
+ 1 x Wechselschalter
+ 1 x Schalter 1pol.
+ 1 x 9V Batterieclip
+ 1 x 9V Batterie
+ 1 x Gehäuse
+ Kabel

---

## Verdrahtung

![Schaltplan](https://github.com/frankyhub/Eieruhr/blob/main/pic/schaltplan_eieruhr.png)

Der Schaltplan


![Shield](https://github.com/frankyhub/Eieruhr/blob/main/pic/eieruhrshield.png)

Das NANO-Shield

---



