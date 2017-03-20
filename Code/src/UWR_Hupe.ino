/*
Herz der UWR-BA Hupe
beinhaltet setup()- und loop()-Funktion
*/


#include "LedControl.h" //  need the library
#include <SoftwareSerial.h>// import the serial library
#include "constants.h"

SoftwareSerial Bluetooth(9, 8); // RX, TX
LedControl lc = LedControl(12, 11, 10, 1); //
// pin 12 is connected to DOUT
// pin 11 is connected to the CLK
// pin 10 is connected to LOAD

unsigned long Start = 0;
unsigned long Stop = 0;
unsigned long TimerSpielzeit = 0;
unsigned long nachSpielZeit = 0;

unsigned long TimerHupen[3] = {0};       // Timer für die erkennung von 2 Signalen
unsigned long TimerHupenPause[3] = {0};  // Timer für die erkennung von 2 Signalen
unsigned long TimerLangesHupen[3] = {0}; // Timer für die erkennung von einem langem Signale
int LangesHupenStatus[3] = {0};
unsigned int LangesHupenFehler[3] = {0};
unsigned int Fehler[3] = {0};
int HupStatus[3] = {0};

unsigned long Abhupen=0;
byte langesHupen=0;
byte kurzesHupen=0;

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

bool Reset = 0;
bool durchlaufendeZeitStop = 0;
bool StrafwurfStop = 0;

int Spieldauer = 900; // 15min*60 = 900 - beim Setup belegen
int Strafzeit = 120; // 2min*60 =120  - beim Setup belegen
int Strafwurf = 45; // beim Setup belegen
bool DurchlaufendeSpielzeit = 0; //1 = durchlaufende Spielzeit- beim Setup belegen
int HalbzeitPause = 300; // 5min Halbzeitpause

bool istStrafwurf = 0;
unsigned long StrafwurfTimer = 0;


int Strafzeiten[] = {0, 0, 0, 0, 0, 0};
int kleinsteStrafzeit;
int AnzahlStrafzeiten = 0;

bool istHalbzeitPause=0;
unsigned long TimerHalbzeitPause=0;
unsigned long StartTimerHalbzeitPause=0;

// Bluethooth Variablen
char BluetoothBuffer[4];
char BluetoothTrennzeichen[]=";";
char BluetoothString[33];

void setup()
{
        // put your setup code here, to run once:
        lc.shutdown(0, false); // turn off power saving, enables display
        lc.setIntensity(0, 8); // sets brightness (0~15 possible values)
        lc.clearDisplay(0);// clear screen
        delay(1005);
        //  Start=millis();        //Beim Anhupen Ausführen
        //  TimerSpielzeit=Spieldauer;      //Beim Anhupen Ausführen
        //  Start=Start+TimerSpielzeit*1000;//Beim Anhupen Ausführen


        Bluetooth.begin(9600);
        //Serial.begin(9600);
        pinMode(2, INPUT);     // set pin to input
        pinMode(3, INPUT);     // set pin to input
        pinMode(4, INPUT);     // set pin to input
        pinMode(PinHorn, OUTPUT);   // Hupe
        digitalWrite(PinHorn, HIGH);
        pinMode(PinButtonReset, INPUT_PULLUP); //Knopf1
        pinMode(PinButtonSetup, INPUT_PULLUP); //Knopf2
        pinMode(PinButtonPlus, INPUT_PULLUP); //Knopf3
        pinMode(PinButtonMinus, INPUT_PULLUP); //Knopf4

}

/* loop(): Hauptcode steht in dieser Funktion - wird immer wieder ausgeführt */
void loop()
{
        // Setup - Startprogramm
        while (Setup < SetupStateMax)
        {
                SetupKnoepfe();
        }
        // Setup Abgeschlossen - Spiel kann beginnen

        // Abfrage der Knöpfe an der Hupe
        Knoepfe();

        // Checke, ob automatische abgehupt werden muss
        AutomatischHupen ();

        // Checke, ob Spiel zu Ende ist --> Abhupen, evtl. Halbzeit und reset
        if (TimerSpielzeit <= 0)
        {
                durchlaufendeZeitStop = 1; //Werte zurücksetzen
                TimerSpielzeit = Spieldauer;
                Stop = 1;
                nachSpielZeit = 0;
                for (int i=0; i<6; i++)
                {Strafzeiten[i]=0;}

                if (StartTimerHalbzeitPause==0 && istHalbzeitPause==0)
                {
                        StartTimerHalbzeitPause = millis() + TimerHalbzeitPause * 1000;
                        istHalbzeitPause=1;
                }


                langesHupen=1;       //Abhupen

        }
        // Spiel zu ende - Abhupen und reset

        // Aktualisieren der Zeitanzeige
        UpdateTime();

        // Bei gedrücktem Knopf: lasse Hupe hupen
        if ((digitalRead(PinDrueckerSpielleiter) == 0 || digitalRead(PinDrueckerUW1) == 0 || digitalRead(PinDrueckerUW2) == 0))
        {
                digitalWrite(PinHorn, LOW);
        }
        else if (langesHupen==0 && kurzesHupen==0)
        {
                digitalWrite(PinHorn, HIGH);
        }
        // Hupe hupen lassen bei Drücken eines Knopfes

        // Während Spiel: Suche nach Abhup-Signal (zwei kurze Hupsignale)
        if (Stop == 0 && istHalbzeitPause==0)
        {
                ZweiSignale(0, digitalRead(PinDrueckerSpielleiter));
                ZweiSignale(1, digitalRead(PinDrueckerUW1));
                ZweiSignale(2, digitalRead(PinDrueckerUW2));
        }
        // Wenn Spiel läuft, Abhupen suchen (zwei kurze Hupsignale)

        // Gestopptes/noch nicht begonnenes Spiel/bei durchlaufender Zeit (Strafwurf beginnt): Suche langes Hupen
        if ((Stop != 0 || DurchlaufendeSpielzeit==1) && istHalbzeitPause==0)
        {
                LangesSignal(0, digitalRead(PinDrueckerSpielleiter));
                LangesSignal(1, digitalRead(PinDrueckerUW1));
                LangesSignal(2, digitalRead(PinDrueckerUW2));
        }
        // Wenn nicht Spiel läuft langes Hupen suchen

}
