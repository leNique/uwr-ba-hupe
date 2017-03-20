#include "LedControl.h" //  need the library
#include <SoftwareSerial.h>// import the serial library
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

byte Setup = 0; //Setup=0->Setup beginnt
//Setup=1->Spielzeit einstellen     A
//Setup=2->Strafzeit einstellen     B
//Setup=3->Strafwurfzeit einstellen C
//Setup=4->durchlaufen Zeit?        D
//Setup=5->Halbzeitpause            E
//Setup=6->Startbereit

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
        pinMode(5, OUTPUT);   // Hupe
        digitalWrite(5, HIGH);
        pinMode(14, INPUT_PULLUP); //Knopf1
        pinMode(15, INPUT_PULLUP); //Knopf2
        pinMode(16, INPUT_PULLUP); //Knopf3
        pinMode(17, INPUT_PULLUP); //Knopf4

}






void loop()
{
        // put your main code here, to run repeatedly:
        while (Setup < 6)                           //Setup - Startprogramm
        {
                SetupKnoepfe();
        }
        // Setup Abgeschlossen - Spiel kann beginnen


        Knoepfe();                            //Knöpfe an der Hupe werden abgefragt
        AutomatischHupen ();                  // falls automatisch gehupt werden muss wird das gemacht

        if (TimerSpielzeit <= 0)                         // Spiel zu ende - Abhupen, evtl. Halbzeit und reset
        {
                durchlaufendeZeitStop = 1; //Werte zurücksetzen
                TimerSpielzeit = Spieldauer;
                Stop = 1;
                nachSpielZeit = 0;
                 if (warHalbzeitPause==0)     // Strafzeiten nur löschen falls 2. Spielhälfte
                 {
                   for (int i=0; i<6; i++)
                   {Strafzeiten[i]=0;}
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
        if (digitalRead(2) == 0 && HupStatus[1] < 2 && HupStatus[2] < 2)
        {digitalWrite(5, LOW);
          lc.setChar(0, 2,'a', false);}
        else if ( digitalRead(3) == 0 && HupStatus[0] < 2 && HupStatus[2] < 2)
        {digitalWrite(5, LOW);
          lc.setChar(0, 2,'b', false);}
        else if ( digitalRead(4) == 0 && HupStatus[1] < 2 && HupStatus[0] < 2)
        {digitalWrite(5, LOW);
          lc.setChar(0, 2,'c', false);}
        else if (langesHupen==0 && kurzesHupen==0)
        {
                digitalWrite(5, HIGH);
        }                                                               // Hupe hupen lassen bei drücken eines Knopfes



        if (Stop == 0 && istHalbzeitPause==0)                      // Wenn Spiel läuft Abhupen suchen (zwei kurze Hupsignale)
        {
                ZweiSignale(0, digitalRead(2));
                ZweiSignale(1, digitalRead(3));
                ZweiSignale(2, digitalRead(4));
        }                                 // Wenn Spiel läuft Abhupen suchen (zwei kurze Hupsignale)

        if ((Stop != 0 || DurchlaufendeSpielzeit==1) && istHalbzeitPause==0)              // Wenn nicht Spiel läuft oder durchlaufende Spielzeit(Strafwurf beginnt) langes Hupen suchen
        {
                LangesSignal(0, digitalRead(2));
                LangesSignal(1, digitalRead(3));
                LangesSignal(2, digitalRead(4));
        }                                // Wenn nicht Spiel läuft langes Hupen suchen

}
