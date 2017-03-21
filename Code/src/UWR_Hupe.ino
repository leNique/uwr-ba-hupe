#include "config.h"
#include "bluetooth.h"
#include "display.h"

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

bool warHalbzeitPause=0;   // Zähler ob Halbzeit schon war oder noch erste Spielhälfte läuft
bool istHalbzeitPause=0;
unsigned long TimerHalbzeitPause=0;
unsigned long StartTimerHalbzeitPause=0;

#if OUTPUT_BLUETOOTH
char BluetoothBuffer[4];
char BluetoothTrennzeichen[]=";";
char BluetoothString[33];
#endif




void setup()
{
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
        lcd.print("star tet.");
        #endif

        #if OUTPUT_BLUETOOTH
        Bluetooth.begin(9600);
        #endif
        #if OUTPUT_SERIAL
        Serial.begin(9600);
        while (!Serial) {
          ; // wait for serial port to connect. Needed for native USB port only
        }
        #endif

        pinMode(PinDrueckerSpielleiter, INPUT);
        pinMode(PinDrueckerUW1, INPUT);
        pinMode(PinDrueckerUW2, INPUT);
        pinMode(PinHorn, OUTPUT);
        digitalWrite(PinHorn, HIGH);
        pinMode(PinButtonReset, INPUT_PULLUP); //Knopf1
        pinMode(PinButtonSetup, INPUT_PULLUP); //Knopf2
        pinMode(PinButtonPlus, INPUT_PULLUP); //Knopf3
        pinMode(PinButtonMinus, INPUT_PULLUP); //Knopf4
}




void loop()
{
        // Setup - Startprogramm
        while (Setup < SetupStateMax)
        {
                SetupKnoepfe();
        }
        // Setup Abgeschlossen - Spiel kann beginnen


        Knoepfe();          // Knöpfe an der Hupe werden abgefragt
        AutomatischHupen(); // falls automatisch gehupt werden muss wird das gemacht

        if (TimerSpielzeit <= 0)                         // Spiel zu ende - Abhupen, evtl. Halbzeit und reset
        {
                durchlaufendeZeitStop = 1; //Werte zurücksetzen
                TimerSpielzeit = Spieldauer;
                Stop = 1;
                nachSpielZeit = 0;
                 if (warHalbzeitPause==0)     // Strafzeiten nur löschen falls 2. Spielhälfte
                 {
                   for (int i=0; i<6; i++)
                   {
                     Strafzeiten[i]=0;
                   }
                   warHalbzeitPause=1;
                 }
                 else
                 {
                   warHalbzeitPause=0;
                 }      // 2. Spielhälfte - neues Spiel beginnt

                if (StartTimerHalbzeitPause==0 && istHalbzeitPause==0)
                {
                        StartTimerHalbzeitPause = millis() + TimerHalbzeitPause * 1000;
                        istHalbzeitPause=1;
                }


                langesHupen=1;       //Abhupen
        }                                            // Spiel zu ende - Abhupen und reset

        UpdateTime();                           // Anzeige akualisieren

        //if ((digitalRead(2) == 0 && LangesHupenStatus[1]==0 && LangesHupenStatus[2]==0 && HupStatus[1]==0 && HupStatus[2]==0)||( digitalRead(3) == 0 && LangesHupenStatus[0]==0 && LangesHupenStatus[2]==0 && HupStatus[0]==0 && HupStatus[2]==0) || ( digitalRead(4) == 0 && LangesHupenStatus[1]==0 && LangesHupenStatus[0]==0 && HupStatus[1]==0 && HupStatus[0]==0)) // Hupe hupen lassen bei drücken eines Knopfes
        //if ((digitalRead(2) == 0 )||( digitalRead(3) == 0 ) || ( digitalRead(4) == 0 )) // Hupe hupen lassen bei drücken eines Knopfes
        if (digitalRead(PinDrueckerSpielleiter) == 0 && HupStatus[1] < 2 && HupStatus[2] < 2)
        {
          digitalWrite(PinHorn, LOW);
          zeigWerGehuptHat('a');
        }
        else if ( digitalRead(PinDrueckerUW1) == 0 && HupStatus[0] < 2 && HupStatus[2] < 2)
        {
          digitalWrite(PinHorn, LOW);
          zeigWerGehuptHat('b');
        }
        else if ( digitalRead(PinDrueckerUW2) == 0 && HupStatus[1] < 2 && HupStatus[0] < 2)
        {
          digitalWrite(PinHorn, LOW);
          zeigWerGehuptHat('c');
        }
        else if (langesHupen==0 && kurzesHupen==0)
        {
                digitalWrite(PinHorn, HIGH);
        }                                                               // Hupe hupen lassen bei drücken eines Knopfes

        if (Stop == 0 && istHalbzeitPause==0)                      // Wenn Spiel läuft Abhupen suchen (zwei kurze Hupsignale)
        {
                ZweiSignale(0, digitalRead(PinDrueckerSpielleiter));
                ZweiSignale(1, digitalRead(PinDrueckerUW1));
                ZweiSignale(2, digitalRead(PinDrueckerUW2));
        }
        // Wenn Spiel läuft, Abhupen suchen (zwei kurze Hupsignale)


        if ((Stop != 0 || DurchlaufendeSpielzeit==1) && istHalbzeitPause==0)              // Wenn nicht Spiel läuft oder durchlaufende Spielzeit(Strafwurf beginnt) langes Hupen suchen
        {
                LangesSignal(0, digitalRead(PinDrueckerSpielleiter));
                LangesSignal(1, digitalRead(PinDrueckerUW1));
                LangesSignal(2, digitalRead(PinDrueckerUW2));
        }
        // Wenn nicht Spiel läuft langes Hupen suchen
}
