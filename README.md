<a name="oben"></a>

# Eieruhr

![Bild](/pic/eieruhr_f.png)

## Story

Mit diesem Projekt wird eine Eieruhr mit zwei 64LED-Matrix-Modulen realisiert. Schalter 1 ist der Einschalter und mit Schalter 2 kann zwischen 3 Zeiten gewählt werden, 5 Minuten, 5 Minuten 30 Sekunden und 6 Minuten. Beim Einschalten ertönen, je nach gewählter Zeit, unterschiedliche Signale. Zusätzlich wird bei gewählten 5,5 Minuten zusätzlich ein Signal bei abgelaufenen 5 Minuten, bei gewählten 6 Minuten ein Signal bei 5 und 5,5 Minuten ausgegeben. Diese Zeiten können softwareseitig in nachfolgender Zeile verändert werden:
int pause_5 = 136; int pause_5_5 = 149; int pause_6 = 162;
Die Zeiten für die Zwischensignale in der Zeile:
byte beep_1 = 50; byte beep_2 = 44; byte beep_3 = 50;
Beide Zeilen befinden sich im Deklarationsteil des Sketches.

![Eieruhr](/pic/eieruhr.png)

Eieruhr Anzeige mit einer 2 x 64 LED Matrix

---
## Hardware
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

Der Schaltplan

![Schaltplan](/pic/schaltplan_eieruhr.png)



Das NANO-Shield

![Shield](/pic/eieruhrshield.png)


64 LED Matrix Module

![Bild](/pic/eieruhr_max.jpg)

NANO

![Bild](/pic/eieruhr_nano.png)


Schalter

![Bild](/pic/eieruhr_schalter.png)









<div style="position:absolute; left:2cm; ">   
<ol class="breadcrumb" style="border-top: 2px solid black;border-bottom:2px solid black; height: 45px; width: 900px;"> <p align="center"><a href="#oben">nach oben</a></p></ol>
</div> 



