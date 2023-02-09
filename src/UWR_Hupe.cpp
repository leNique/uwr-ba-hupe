#ifndef globals_H
#define globals_H
#include "globals.h"
#endif 
#ifndef Knoepfe_H
#define Knoepfe_H
#include "Knoepfe.h"
#endif 
#ifndef AutomatischHupen_H
#define AutomatischHupen_H
#include "AutomatischHupen.h"
#endif 
#ifndef DrueckerAbfragen_H
#define DrueckerAbfragen_H
#include "DrueckerAbfragen.h"
#endif 
#ifndef LangesSignal_H
#define LangesSignal_H
#include "LangesSignal.h"
#endif 
#ifndef SendBluetooth_H
#define SendBluetooth_H
#include "SendBluetooth.h"
#endif 
#ifndef SetupKnoepfe_H
#define SetupKnoepfe_H
#include "SetupKnoepfe.h"
#endif 
#ifndef UpdateTime_H
#define UpdateTime_H
#include "UpdateTime.h"
#endif 
#ifndef ZweiSignale_H
#define ZweiSignale_H
#include "ZweiSignale.h"
#endif 
#ifndef display_H
#define display_H
#include "display.h"
#endif 


unsigned long Start = 0;
unsigned long Stop = 0;
unsigned long StopMerker[3] = {0};  // Timer der die Zeit beim ersten Hupenfesthält und bei unterbrechung in Stop schreibt.
bool AbhupenVerboten[3] = {0}; // StopMerker ist gesetzt das Spiel darf nicht automatisch abgehupt werden
unsigned long TimerSpielzeit = 0;
unsigned long nachSpielZeit = 0;

unsigned long TimerHupen[3] = {0};       // Timer für die erkennung von 2 Signalen
unsigned long TimerHupenPause[3] = {0};  // Timer für die erkennung von 2 Signalen
unsigned long TimerLangesHupen[3] = {0}; // Timer für die erkennung von einem langem Signale
int LangesHupenStatus[3] = {0};
unsigned int LangesHupenFehler[3] = {0};
unsigned int Fehler[3] = {0};
int HupStatus[3] = {0};

unsigned long Abhupen = 0;
byte langesHupen = 0;
byte kurzesHupen = 0;

unsigned long Knopf1Timer = 0;        // Reset
unsigned long Knopf2Timer = 0;        // Strafwurf / Enter
unsigned long Knopf3Timer = 0;        // Strafzeit / +
unsigned long Knopf4Timer = 0;        // Zeit / -
byte Knopf3beschleuniger = 0;
byte Knopf4beschleuniger = 0;
int beschleunigerSchrittweite[] = {0, 1, 2, 5, 10, 30, 60};

byte Setup = SetupStateHome; //Setup=SetupStateHome -> Setup beginnt
//Setup=SetupStateSpieldauer             -> Spielzeit einstellen     A
//Setup=SetupStateStrafzeit              -> Strafzeit einstellen     B
//Setup=SetupStateStrafwurf              -> Strafwurfzeit einstellen C
//Setup=SetupStateDurchlaufendeSpielzeit -> durchlaufen Zeit?        D
//Setup=SetupStateHalbzeitPause          -> Dauer der Halbzeitpause  E
//Setup=SetupStateMax                    -> Startbereit

byte Status = 0;  // Akuteller Zustand des Spieles                       Status hat im Moment keine funktion - evtl. besser aber vieleicht auch nicht....
// Status=0  -> Spiel hat noch nicht begonnen
// Status=1  -> Spiel läuft normal
// Status=2  -> Spiel gestoppt
// Status=3  -> Halbzeitpause
// Status=20 -> Strafwurf ist gewählt - Uhr steht
// Status=21 -> Strafwurf ist gewählt - Uhr läuft
// Status=1 ->
// Status=1 ->
// Status=1 ->

bool Reset = false;
bool durchlaufendeZeitStop = false;
bool StrafwurfStop = false;

int Spieldauer = 900; // 15min*60 = 900 - beim Setup belegen
int Strafzeit = 120; // 2min*60 =120  - beim Setup belegen
int Strafwurf = 45; // beim Setup belegen
bool DurchlaufendeSpielzeit = false; //true = durchlaufende Spielzeit- beim Setup belegen
int HalbzeitPause = 300; // 5min Halbzeitpause

bool istStrafwurf = false;
unsigned long StrafwurfTimer = 0;
int zeigStrafwurfZeitSek = 0;
unsigned long zeigStrafwurfZeitTimer = 0;

int Strafzeiten[] = {0, 0, 0, 0, 0, 0};
int kleinsteStrafzeit;
int AnzahlStrafzeiten = 0;

bool warHalbzeitPause = false;   // Zähler ob Halbzeit schon war oder noch erste Spielhälfte läuft
bool istHalbzeitPause = false;
unsigned long TimerHalbzeitPause = 0;
unsigned long StartTimerHalbzeitPause = 0;

#if OUTPUT_BLUETOOTH
char BluetoothBuffer[4];
char BluetoothTrennzeichen[] = ";";
char BluetoothString[33];
SoftwareSerial Bluetooth(PinBluetoothRx, PinBluetoothTx);
#endif

#if OUTPUT_LED
#include "LedControl.h"
LedControl lc = LedControl(PinLedDout, PinLedClk, PinLedCs, LedNumDevices);
#endif


//Drücker abfragen
bool DrueckerSpielleiter = true;
bool DrueckerUW1 = true;
bool DrueckerUW2 = true;
unsigned long TimerDrueckerSpielleiter = 0;
unsigned long TimerDrueckerUW1 = 0;
unsigned long TimerDrueckerUW2 = 0;
unsigned long BlockTimerDrueckerSpielleiter = 0;
unsigned long BlockTimerDrueckerUW1 = 0;
unsigned long BlockTimerDrueckerUW2 = 0;
unsigned long MinimalTimerDruecker = 0;
Bounce BounceDrueckerSpielleiter = Bounce();
Bounce BounceDrueckerUW1 = Bounce();
Bounce BounceDrueckerUW2 = Bounce();


void setup()
{
        #if OUTPUT_SERIAL
        Serial.begin(9600);
        while (!Serial) {
          ; // wait for serial port to connect. Needed for native USB port only
        }
        Serial.write("setup() starting\n");
        #endif

        #if OUTPUT_LED
        lc.shutdown(0, false); // turn off power saving, enables display
        lc.setIntensity(0, 8); // sets brightness (0~15 possible values)
        lc.clearDisplay(0);// clear screen
        delay(1005);
        #endif
        //  Start=millis();        //Beim Anhupen Ausführen
        //  TimerSpielzeit=Spieldauer;      //Beim Anhupen Ausführen
        //  Start=Start+TimerSpielzeit*1000;//Beim Anhupen Ausführen

        #if OUTPUT_LCD
        // set up the LCD's number of columns and rows:
        lcd.begin(16, 2);
        // Print a message to the LCD.
        lcd.print("uwr-ba-hupe     ");
        lcd.setCursor(0, 1);
        lcd.print("startet...");
        delay(500);
        #endif

        #if OUTPUT_BLUETOOTH
        Bluetooth.begin(9600);
        #endif

        pinMode(PinDrueckerSpielleiter, INPUT);
        pinMode(PinDrueckerUW1, INPUT);
        pinMode(PinDrueckerUW2, INPUT);

        BounceDrueckerSpielleiter.attach(PinDrueckerSpielleiter);
        BounceDrueckerSpielleiter.interval(20);
        BounceDrueckerUW1.attach(PinDrueckerUW1);
        BounceDrueckerUW1.interval(20);
        BounceDrueckerUW2.attach(PinDrueckerUW2);
        BounceDrueckerUW2.interval(20);

        pinMode(PinHorn, OUTPUT);   // Hupe
        digitalWrite(PinHorn, HIGH);

        #if DIGITAL_BUTTONS
        pinMode(PinButtonReset, INPUT_PULLUP); //Knopf1
        pinMode(PinButtonSetup, INPUT_PULLUP); //Knopf2
        pinMode(PinButtonPlus, INPUT_PULLUP); //Knopf3
        pinMode(PinButtonMinus, INPUT_PULLUP); //Knopf4
        #endif
        #if ANALOG_BUTTONS
        // Do not set pin mode.
        #endif

        #if OUTPUT_SERIAL
        Serial.write("setup() finished\n");
        #endif
}




void loop()
{
    #if ANALOG_BUTTONS
    int btn_id = readAnalogButton(PinAnalogButtons);
    bool isButtonResetPressed = (btnSELECT == btn_id);
    bool isButtonSetupPressed = (btnLEFT   == btn_id);
    bool isButtonPlusPressed  = (btnUP     == btn_id);
    bool isButtonMinusPressed = (btnDOWN   == btn_id);
    #endif

    #if DIGITAL_BUTTONS
    bool isButtonResetPressed = (digitalRead(PinButtonReset) == LOW);
    bool isButtonSetupPressed = (digitalRead(PinButtonSetup) == LOW);
    bool isButtonPlusPressed  = (digitalRead(PinButtonPlus)  == LOW);
    bool isButtonMinusPressed = (digitalRead(PinButtonMinus) == LOW);
    #endif

    // Setup - Startprogramm
    while (Setup < SetupStateMax)
    {
      #if DIGITAL_BUTTONS
      bool isButtonResetPressed = (digitalRead(PinButtonReset) == LOW);
      bool isButtonSetupPressed = (digitalRead(PinButtonSetup) == LOW);
      bool isButtonPlusPressed  = (digitalRead(PinButtonPlus)  == LOW);
      bool isButtonMinusPressed = (digitalRead(PinButtonMinus) == LOW);
      #endif
        SetupKnoepfe(isButtonResetPressed, isButtonSetupPressed, isButtonPlusPressed, isButtonMinusPressed);
    }
    // Setup Abgeschlossen - Spiel kann beginnen


    // Knöpfe an der Hupe behandeln
    Knoepfe(isButtonResetPressed, isButtonSetupPressed, isButtonPlusPressed, isButtonMinusPressed);

    // falls automatisch gehupt werden muss wird das gemacht
    AutomatischHupen();

    DrueckerAbfragen();

        if (TimerSpielzeit <= 0 && AbhupenVerboten[0] == 0 && AbhupenVerboten[1] == 0 && AbhupenVerboten[2] == 0)                         // Spiel zu ende - Abhupen, evtl. Halbzeit und reset
        {
                durchlaufendeZeitStop = true; //Werte zurücksetzen
                TimerSpielzeit = Spieldauer;
                Stop = 1;
                nachSpielZeit = 0;
                 if (warHalbzeitPause)     // Strafzeiten nur löschen falls 2. Spielhälfte
                 {
                   for (int i=0; i<6; i++)
                   {
                     Strafzeiten[i] = 0;
                   }
                   warHalbzeitPause = false;
                   TimerHalbzeitPause = 1; // Halbzeitpause auf 1 Sek stellen (Halbzeit war schon deshalb überspringen)
                   clearDigits5678();
                   #if OUTPUT_BLUETOOTH
                   SendBluetooth();               //Display auf Startzeit setzten
                   #endif
                 }
                 else
                 {
                   warHalbzeitPause = true;
                   zeigHalbzeit();
                 }      // 2. Spielhälfte - neues Spiel beginnt

                if (StartTimerHalbzeitPause == 0 && !istHalbzeitPause)
                {
                        StartTimerHalbzeitPause = millis() + TimerHalbzeitPause * 1000;
                        istHalbzeitPause = true;
                }

                langesHupen=1;       //Abhupen
        }                                            // Spiel zu ende - Abhupen und reset

        UpdateTime();                           // Anzeige akualisieren

        if (DrueckerSpielleiter)
        {
          digitalWrite(PinHorn, LOW);
          zeigWerGehuptHat('a');
        }
        else if (DrueckerUW1)
        {
          digitalWrite(PinHorn, LOW);
          zeigWerGehuptHat('b');
        }
        else if (DrueckerUW2)
        {
          digitalWrite(PinHorn, LOW);
          zeigWerGehuptHat('c');
        }
        else if (langesHupen==0 && kurzesHupen==0)
        {
                digitalWrite(PinHorn, HIGH);
        }                                                               // Hupe hupen lassen bei drücken eines Knopfes

        if (Stop == 0 && !istHalbzeitPause)                      // Wenn Spiel läuft Abhupen suchen (zwei kurze Hupsignale)
        {
                ZweiSignale(0, DrueckerSpielleiter);
                ZweiSignale(1, DrueckerUW1);
                ZweiSignale(2, DrueckerUW2);
        }
        // Wenn Spiel läuft, Abhupen suchen (zwei kurze Hupsignale)


        if ((Stop != 0 || DurchlaufendeSpielzeit) && !istHalbzeitPause)              // Wenn nicht Spiel läuft oder durchlaufende Spielzeit(Strafwurf beginnt) langes Hupen suchen
        {
                LangesSignal(0, DrueckerSpielleiter);
                LangesSignal(1, DrueckerUW1);
                LangesSignal(2, DrueckerUW2);
        }
        // Wenn nicht Spiel läuft langes Hupen suchen
}
