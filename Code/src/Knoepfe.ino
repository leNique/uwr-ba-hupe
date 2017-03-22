#include "config.h"
#include "display.h"
#include "analog_buttons.h"

void Knoepfe()
{
    #if ANALOG_BUTTONS
    int btn_id = readAnalogButton(PinAnalogButtons);
    bool isButtonResetPressed = (btnSELECT == btn_id);
    bool isButtonSetupPressed = (btnLEFT   == btn_id);
    bool isButtonPlusPressed  = (btnUP     == btn_id);
    bool isButtonMinusPressed = (btnDOWN   == btn_id);
    #endif

    #if DIGITAL_BUTTONS
    bool isButtonResetPressed = (digitalRead(PinButtonReset) == 0);
    bool isButtonSetupPressed = (digitalRead(PinButtonSetup) == 0);
    bool isButtonPlusPressed  = (digitalRead(PinButtonPlus)  == 0);
    bool isButtonMinusPressed = (digitalRead(PinButtonMinus) == 0);
    #endif

    if (isButtonResetPressed && Knopf1Timer < millis() - 1000) // Reset initalisieren
    {
        Knopf1Timer = millis();
        Reset = 1;
    }
    if (Knopf1Timer + 2000 < millis())    // nach 2 Sekunden ResetModus beenden
    {
        if (Reset == 1)
        {
            zeigSpielzeit(TimerSpielzeit);
            clearDigit5();
        }
        Reset = 0;
    }

    if (Reset == 1)
    {
        zeigReset();
    }


    if (isButtonSetupPressed && Knopf2Timer < millis() - 1000) // Reset / Strafwurf
    {
        Knopf2Timer = millis();

        if (Reset == 1)                             // Reset tatsächlich auslösen
        {
            Setup = SetupStateHome;
        }

        if (Stop != 0 || DurchlaufendeSpielzeit == 1)                           //Strafwurf
        {
            if (istStrafwurf == 1)
            {
                StrafwurfTimer = 0;
                istStrafwurf = 0;

                // Anzeige von Strafwurf auf Strafzeiten umstellen
                zeigStrafzeiten(AnzahlStrafzeiten, kleinsteStrafzeit);
            }
            else
            {
                if (DurchlaufendeSpielzeit == 1)
                {
                    StrafwurfStop = 1;
                }
                istStrafwurf = 1;
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
            if (DurchlaufendeSpielzeit == 0)
            {
                Start = Start + millis() - Stop;
                Stop = 0;
            }
            else                 //durchlaufende Zeit
            {
                if (durchlaufendeZeitStop == 1) // Spiel am Anfang Starten
                {
                    durchlaufendeZeitStop = 0;
                    Start = Start + millis() - Stop;
                    Stop = 0;
                }
            }
        }
        else                       //Zeit umschalten LÄUFT - läuft nicht
        {
            if (DurchlaufendeSpielzeit == 0)
            {
                Stop = millis(); //Zeit wird angehalten wenn keine durchlaufende Spielzeit
            }

            if (istStrafwurf == 1 && StrafwurfStop == 0) //durchlaufende Zeit - Strafwurf beenden
            {
                istStrafwurf = 0;
                StrafwurfTimer = 0;

                // Anzeige von Strafwurf auf Strafzeiten umstellen
                zeigStrafzeiten(AnzahlStrafzeiten, kleinsteStrafzeit);
            }

            if (StrafwurfStop == 1 && istStrafwurf == 1) //durchlaufende Zeit - Strafwurf ausführen
            {
                StrafwurfStop = 0;
            }
        }
    } //Ende ButtonMinus
}
