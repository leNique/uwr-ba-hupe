#include <Bounce2.h>

#include "config.h"
#include "analog_buttons.h"
#include "bluetooth.h"
#include "display.h"

// ---- Variablen

extern unsigned long Start;
extern unsigned long Stop;
extern unsigned long StopMerker;  // Timer der die Zeit beim ersten Hupenfesthält und bei unterbrechung in Stop schreibt.
extern unsigned long TimerSpielzeit;
extern unsigned long nachSpielZeit;

extern unsigned long TimerHupen[3];       // Timer für die erkennung von 2 Signalen
extern unsigned long TimerHupenPause[3];  // Timer für die erkennung von 2 Signalen
extern unsigned long TimerLangesHupen[3]; // Timer für die erkennung von einem langem Signale
extern int LangesHupenStatus[3];
extern unsigned int LangesHupenFehler[3];
extern unsigned int Fehler[3];
extern int HupStatus[3];

extern unsigned long Abhupen;
extern byte langesHupen;
extern byte kurzesHupen;

extern unsigned long Knopf1Timer;        // Reset
extern unsigned long Knopf2Timer;        // Strafwurf / Enter
extern unsigned long Knopf3Timer;        // Strafzeit / +
extern unsigned long Knopf4Timer;        // Zeit / -
extern byte Knopf3beschleuniger;
extern byte Knopf4beschleuniger;
extern int beschleunigerSchrittweite[7];

extern  byte Setup; //Setup=SetupStateHome -> Setup beginnt
//Setup=SetupStateSpieldauer             -> Spielzeit einstellen     A
//Setup=SetupStateStrafzeit              -> Strafzeit einstellen     B
//Setup=SetupStateStrafwurf              -> Strafwurfzeit einstellen C
//Setup=SetupStateDurchlaufendeSpielzeit -> durchlaufen Zeit?        D
//Setup=SetupStateHalbzeitPause          -> Dauer der Halbzeitpause  E
//Setup=SetupStateMax                    -> Startbereit

extern byte Status;  // Akuteller Zustand des Spieles                       Status hat im Moment keine funktion - evtl. besser aber vieleicht auch nicht....
// Status=0  -> Spiel hat noch nicht begonnen
// Status=1  -> Spiel läuft normal
// Status=2  -> Spiel gestoppt
// Status=3  -> Halbzeitpause
// Status=20 -> Strafwurf ist gewählt - Uhr steht
// Status=21 -> Strafwurf ist gewählt - Uhr läuft
// Status=1 ->
// Status=1 ->
// Status=1 ->

extern bool Reset;
extern bool durchlaufendeZeitStop;
extern bool StrafwurfStop;

extern int Spieldauer; // 15min*60 = 900 - beim Setup belegen
extern int Strafzeit; // 2min*60 =120  - beim Setup belegen
extern int Strafwurf; // beim Setup belegen
extern bool DurchlaufendeSpielzeit; //true = durchlaufende Spielzeit- beim Setup belegen
extern int HalbzeitPause; // 5min Halbzeitpause

extern bool istStrafwurf;
extern unsigned long StrafwurfTimer;
extern int zeigStrafwurfZeitSek;
extern unsigned long zeigStrafwurfZeitTimer;

extern int Strafzeiten[6];
extern int kleinsteStrafzeit;
extern int AnzahlStrafzeiten;

extern bool warHalbzeitPause;   // Zähler ob Halbzeit schon war oder noch erste Spielhälfte läuft
extern bool istHalbzeitPause;
extern unsigned long TimerHalbzeitPause;
extern unsigned long StartTimerHalbzeitPause;

#if OUTPUT_BLUETOOTH
extern char BluetoothBuffer[4];
extern char BluetoothTrennzeichen[2];
extern char BluetoothString[33];
extern SoftwareSerial Bluetooth();
#endif


//Drücker abfragen
extern bool DrueckerSpielleiter;
extern bool DrueckerUW1;
extern bool DrueckerUW2;
extern unsigned long TimerDrueckerSpielleiter;
extern unsigned long TimerDrueckerUW1;
extern unsigned long TimerDrueckerUW2;
extern unsigned long BlockTimerDrueckerSpielleiter;
extern unsigned long BlockTimerDrueckerUW1;
extern unsigned long BlockTimerDrueckerUW2;
extern unsigned long MinimalTimerDruecker;
extern Bounce BounceDrueckerSpielleiter;
extern Bounce BounceDrueckerUW1;
extern Bounce BounceDrueckerUW2;
