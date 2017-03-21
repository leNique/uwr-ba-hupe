#include "config.h"

void SetupKnoepfe()
{
        if (digitalRead(PinButtonReset) == 0 && Knopf1Timer < millis() - 500) // Reset initalisieren
        {
                Knopf1Timer = millis();
                Setup = SetupStateHome;
        }


        if (digitalRead(PinButtonSetup) == 0 && Knopf2Timer < millis() - 500)
        {
                Knopf2Timer = millis();

                if (Setup < SetupStateMax)                 //Setup fortführen
                {
                        Setup++;
                        Knopf3beschleuniger = 0;
                        Knopf4beschleuniger = 0;
                }

                if (Setup == SetupStateMax)              //Setup fertig - Spiel bereit - Uhr angehalten
                {
                        Start = millis();
                        TimerSpielzeit = Spieldauer;
                        TimerHalbzeitPause = HalbzeitPause;
                        Start = Start + TimerSpielzeit * 1000;
                        Stop = millis();

                        for (int i=0; i<6; i++)
                        {Strafzeiten[i]=0;}
                        warHalbzeitPause=0;
                        istHalbzeitPause=0;
                        istStrafwurf=0;
                        StrafwurfStop=0;

                        zeigSpielzeit(TimerSpielzeit);
                        clearDigit5();
                }


        }

        if (digitalRead(PinButtonPlus) == 0 && Knopf3Timer < millis() - 500)
        {
                Knopf3Timer = millis();
                if (Knopf3beschleuniger < 6)
                {
                        Knopf3beschleuniger++;
                }

                if (Setup == SetupStateSpieldauer)
                {
                        Spieldauer = Spieldauer + beschleunigerSchrittweite[Knopf3beschleuniger];
                }
                if (Setup == SetupStateStrafzeit)
                {
                        Strafzeit = Strafzeit + beschleunigerSchrittweite[Knopf3beschleuniger];
                }
                if (Setup == SetupStateStrafwurf)
                {
                        Strafwurf = Strafwurf + beschleunigerSchrittweite[Knopf3beschleuniger];
                }
                if (Setup == SetupStateDurchlaufendeSpielzeit)
                {
                        DurchlaufendeSpielzeit = 1;
                        durchlaufendeZeitStop = 1;
                }
                if (Setup == SetupStateHalbzeitPause)
                {
                        HalbzeitPause = HalbzeitPause + beschleunigerSchrittweite[Knopf3beschleuniger];
                }

        }
        if (Knopf3Timer < millis() - 510)
        {
                Knopf3beschleuniger = 0;
        }

        if (digitalRead(PinButtonMinus) == 0 && Knopf4Timer < millis() - 500)
        {
                Knopf4Timer = millis();
                if (Knopf4beschleuniger < 6)
                {
                        Knopf4beschleuniger++;
                }

                if (Setup == SetupStateSpieldauer && Spieldauer - beschleunigerSchrittweite[Knopf4beschleuniger] > 0)
                {
                        Spieldauer = Spieldauer - beschleunigerSchrittweite[Knopf4beschleuniger];
                }
                if (Setup == SetupStateStrafzeit && Strafzeit - beschleunigerSchrittweite[Knopf4beschleuniger] > 0)
                {
                        Strafzeit = Strafzeit - beschleunigerSchrittweite[Knopf4beschleuniger];
                }
                if (Setup == SetupStateStrafwurf && Strafwurf - beschleunigerSchrittweite[Knopf4beschleuniger] > 0)
                {
                        Strafwurf = Strafwurf - beschleunigerSchrittweite[Knopf4beschleuniger];
                }
                if (Setup == SetupStateDurchlaufendeSpielzeit)
                {
                        DurchlaufendeSpielzeit = 0;
                        durchlaufendeZeitStop = 0;
                }
                if (Setup == SetupStateHalbzeitPause && HalbzeitPause - beschleunigerSchrittweite[Knopf4beschleuniger] > 0)
                {
                        HalbzeitPause = HalbzeitPause - beschleunigerSchrittweite[Knopf4beschleuniger];
                }

        }
        if (Knopf4Timer < millis() - 510)
        {
                Knopf4beschleuniger = 0;
        }





        //Anzeige Setup
        if (Setup == SetupStateHome)
        {
                zeigSetup();

                for (int i = 0; i < 6; i++) // Strafzeiten löschen falls vorhanden
                {
                  Strafzeiten[i] = 0;
                }
                StrafwurfTimer = 0; // Strafwurf löschen falls vorhanden
                istStrafwurf = 0;
                durchlaufendeZeitStop = 1; // Spiel mit durchlaufender Zeit anhalten
        }

        if (Setup == SetupStateSpieldauer)
        {
                zeigSpielzeit(Spieldauer);
                zeigSetupIndikator('A');
        }

        if (Setup == SetupStateStrafzeit)
        {
                zeigSpielzeit(Strafzeit);
                zeigSetupIndikator('B');
        }

        if (Setup == SetupStateStrafwurf)
        {
                zeigSpielzeit(Strafwurf);
                zeigSetupIndikator('C');
        }

        if (Setup == SetupStateDurchlaufendeSpielzeit)
        {
                zeigSetupDurchlaufendeSpielzeit(DurchlaufendeSpielzeit);
                clearDigits234();
                zeigSetupIndikator('D');
        }

        if (Setup == SetupStateHalbzeitPause)
        {
                zeigSpielzeit(HalbzeitPause);
                zeigSetupIndikator('E');
        }
}
