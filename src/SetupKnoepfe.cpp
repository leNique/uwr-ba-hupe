#include "config.h"


#ifndef SetupKnoepfe_H
#define SetupKnoepfe_H
#include "SetupKnoepfe.h"
#endif 
#ifndef SendBluetooth_H
#define SendBluetooth_H
#include "SendBluetooth.h"
#endif 


void SetupKnoepfe(bool isButtonResetPressed, bool isButtonSetupPressed, bool isButtonPlusPressed, bool isButtonMinusPressed)
{
    if (isButtonResetPressed && Knopf1Timer < millis() - 500) // Reset initalisieren
    {
        Knopf1Timer = millis();
        Setup = SetupStateHome;
    }

    if (isButtonSetupPressed && Knopf2Timer < millis() - 500)
    {
        Knopf2Timer = millis();

        // New setup state, or setup finished
        // -> clear display before writing new text
        clearDisplay();

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
            StartTimerHalbzeitPause = 0;
            Start = Start + TimerSpielzeit * 1000;
            Stop = millis();

            for (int i = 0; i < 6; i++)
            {
                Strafzeiten[i] = 0;
            }
            warHalbzeitPause = false;
            istHalbzeitPause = false;
            istStrafwurf = false;
            StrafwurfStop = false;

            zeigSpielzeit(TimerSpielzeit);
            clearDigit5();
            SendBluetooth();
        }
    }

    if (isButtonPlusPressed && Knopf3Timer < millis() - 500)
    {
        Knopf3Timer = millis();
        if (Knopf3beschleuniger < 6)
        {
            Knopf3beschleuniger++;
        }

        switch (Setup)
        {
            case SetupStateSpieldauer:
                Spieldauer += beschleunigerSchrittweite[Knopf3beschleuniger];
                if (Knopf3beschleuniger==6 && Spieldauer%60!=0)
                 {
                   Spieldauer=Spieldauer-(Spieldauer%60);
                 }
                break;
            case SetupStateStrafzeit:
                Strafzeit += beschleunigerSchrittweite[Knopf3beschleuniger];
                if (Knopf3beschleuniger==6 && Strafzeit%60!=0)
                 {
                   Strafzeit=Strafzeit-(Strafzeit%60);
                 }
                break;
            case SetupStateStrafwurf:
                Strafwurf += beschleunigerSchrittweite[Knopf3beschleuniger];
                break;
            case SetupStateDurchlaufendeSpielzeit:
                DurchlaufendeSpielzeit = !DurchlaufendeSpielzeit;
                durchlaufendeZeitStop = DurchlaufendeSpielzeit;
                break;
            case SetupStateHalbzeitPause:
                HalbzeitPause += beschleunigerSchrittweite[Knopf3beschleuniger];
                if (Knopf3beschleuniger==6 && HalbzeitPause%60!=0)
                 {
                   HalbzeitPause=HalbzeitPause-(HalbzeitPause%60);
                 }
                break;
        }
    }
    //if (Knopf3Timer < millis() - 510)
    if (!isButtonPlusPressed)
    {
        Knopf3beschleuniger = 0;
    }

    if (isButtonMinusPressed && Knopf4Timer < millis() - 500)
    {
        Knopf4Timer = millis();
        if (Knopf4beschleuniger < 6)
        {
            Knopf4beschleuniger++;
        }

        switch (Setup)
        {
            case SetupStateSpieldauer:
                Spieldauer -= beschleunigerSchrittweite[Knopf4beschleuniger];
                if (Knopf4beschleuniger==6 && Spieldauer%60!=0)
                 {
                   Spieldauer=Spieldauer-(Spieldauer%60);
                 }
                if (Spieldauer < 1) Spieldauer = 1;
                break;
            case SetupStateStrafzeit:
                Strafzeit -= beschleunigerSchrittweite[Knopf4beschleuniger];
                if (Knopf4beschleuniger==6 && Strafzeit%60!=0)
                 {
                   Strafzeit=Strafzeit-(Strafzeit%60);
                 }
                if (Strafzeit < 1) Strafzeit = 1;
                break;
            case SetupStateStrafwurf:
                Strafwurf -= beschleunigerSchrittweite[Knopf4beschleuniger];
                if (Strafwurf < 1) Strafwurf = 1;
                break;
            case SetupStateDurchlaufendeSpielzeit:
                DurchlaufendeSpielzeit = !DurchlaufendeSpielzeit;
                durchlaufendeZeitStop = DurchlaufendeSpielzeit;
                break;
            case SetupStateHalbzeitPause:
                HalbzeitPause -= beschleunigerSchrittweite[Knopf4beschleuniger];
                if (Knopf4beschleuniger==6 && HalbzeitPause%60!=0)
                 {
                   HalbzeitPause=HalbzeitPause-(HalbzeitPause%60);
                 }
                if (HalbzeitPause < 1) HalbzeitPause = 1;
                break;
        }
    }
    //if (Knopf4Timer < millis() - 510)
    if (!isButtonMinusPressed)
    {
        Knopf4beschleuniger = 0;
    }


    // Anzeige Setup
    switch (Setup)
    {
        case SetupStateHome:
            zeigSetup();

            for (int i = 0; i < 6; i++) // Strafzeiten löschen falls vorhanden
            {
                Strafzeiten[i] = 0;
            }
            StrafwurfTimer = 0; // Strafwurf löschen falls vorhanden
            istStrafwurf = false;
            durchlaufendeZeitStop = true; // Spiel mit durchlaufender Zeit anhalten
            break;

        case SetupStateSpieldauer:
            zeigSpielzeit(Spieldauer);
            zeigSetupIndikator('A');
            break;

        case SetupStateStrafzeit:
            zeigSpielzeit(Strafzeit);
            zeigSetupIndikator('B');
            break;

        case SetupStateStrafwurf:
            zeigSpielzeit(Strafwurf);
            zeigSetupIndikator('C');
            break;

        case SetupStateDurchlaufendeSpielzeit:
            zeigSetupDurchlaufendeSpielzeit(DurchlaufendeSpielzeit);
            zeigSetupIndikator('D');
            break;

        case SetupStateHalbzeitPause:
            zeigSpielzeit(HalbzeitPause);
            zeigSetupIndikator('E');
            break;
    }
}
