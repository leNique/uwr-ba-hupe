#include "config.h"
#include "display.h"

void Knoepfe(bool isButtonResetPressed, bool isButtonSetupPressed, bool isButtonPlusPressed, bool isButtonMinusPressed)
{
    if (isButtonResetPressed && Knopf1Timer < millis() - 1000) // Reset initalisieren
    {
        Knopf1Timer = millis();
        Reset = true;
    }
    if (Knopf1Timer + 2000 < millis())    // nach 2 Sekunden ResetModus beenden
    {
        if (Reset)
        {
            zeigSpielzeit(TimerSpielzeit);
            clearDigit5();
        }
        Reset = false;
    }

    if (Reset)
    {
        zeigReset();
    }


    if (isButtonSetupPressed && Knopf2Timer < millis() - 1000) // Reset / Strafwurf
    {
        Knopf2Timer = millis();

        if (Reset)                             // Reset tatsächlich auslösen
        {
            Setup = SetupStateHome;
        }

        if (Stop != 0 || DurchlaufendeSpielzeit)                           //Strafwurf
        {
            if (istStrafwurf)
            {
                StrafwurfTimer = 0;
                istStrafwurf = false;

                // Anzeige von Strafwurf auf Strafzeiten umstellen
                zeigStrafzeiten(AnzahlStrafzeiten, kleinsteStrafzeit);
            }
            else
            {
                if (DurchlaufendeSpielzeit)
                {
                    StrafwurfStop = true;
                }
                istStrafwurf = true;
                StrafwurfTimer = Strafwurf;
                zeigSekundenAn78(StrafwurfTimer);
            }
        }
    }

    if (isButtonPlusPressed && Knopf3Timer < millis() - 1000) //Strafzeit
    {
        Knopf3Timer = millis();
        for (int i = 0; i < 6; i++)
        {
            if (Strafzeiten[i] == 0)
            {
                Strafzeiten[i] = Strafzeit;
                break;
            }
        }

        AnzahlStrafzeiten = 0;
        for (int i = 0; i < 6; i++)
        {
            if (Strafzeiten[i] != 0)
            {
                AnzahlStrafzeiten++;
            }
        }
        zeigAnzahlStrafzeiten(AnzahlStrafzeiten);
    }

    if (isButtonMinusPressed && Knopf4Timer < millis() - 800)
    {
        Knopf4Timer = millis();

        if (Stop != 0)               //Zeit umschalten läuft - LÄUFT NICHT
        {
            if (!DurchlaufendeSpielzeit)
            {
                Start = Start + millis() - Stop;
                Stop = 0;
            }
            else                 //durchlaufende Zeit
            {
                if (durchlaufendeZeitStop) // Spiel am Anfang Starten
                {
                    durchlaufendeZeitStop = false;
                    Start = Start + millis() - Stop;
                    Stop = 0;
                }
            }
        }
        else                       //Zeit umschalten LÄUFT - läuft nicht
        {
            if (!DurchlaufendeSpielzeit)
            {
                Stop = millis(); //Zeit wird angehalten wenn keine durchlaufende Spielzeit
            }

            if (istStrafwurf && !StrafwurfStop) //durchlaufende Zeit - Strafwurf beenden
            {
                istStrafwurf = false;
                StrafwurfTimer = 0;

                // Anzeige von Strafwurf auf Strafzeiten umstellen
                zeigStrafzeiten(AnzahlStrafzeiten, kleinsteStrafzeit);
            }

            if (StrafwurfStop && istStrafwurf) //durchlaufende Zeit - Strafwurf ausführen
            {
                StrafwurfStop = false;
            }
        }
    } //Ende ButtonMinus
}
