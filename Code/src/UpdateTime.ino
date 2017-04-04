#include "bluetooth.h"

void UpdateTime()
{
        //TimerSpielzeit +1 ???
        if ((Start - (TimerSpielzeit) * 1000) < millis() - nachSpielZeit && (Stop == 0 || (DurchlaufendeSpielzeit && !durchlaufendeZeitStop)))
        {
                if (istStrafwurf && TimerSpielzeit == 1)
                {
                        nachSpielZeit = nachSpielZeit + 1000;
                }
                else
                {
                        TimerSpielzeit--;
                }

                zeigSpielzeit(TimerSpielzeit);

                kleinsteStrafzeit = Strafzeit; //kleinsteStrafzeit auf max setzen
                AnzahlStrafzeiten = 0;
                for (int i = 0; i < 6; i++)
                {
                        if (Strafzeiten[i] != 0)
                        {
                                AnzahlStrafzeiten++;
                                Strafzeiten[i]--;
                                if (Strafzeiten[i] < kleinsteStrafzeit)
                                {
                                        kleinsteStrafzeit = Strafzeiten[i];
                                }
                        }
                }

                if (!istStrafwurf)
                {
                        zeigStrafzeiten(AnzahlStrafzeiten, kleinsteStrafzeit);
                }
                else                   // Strafwurf MODUS wird gerade ausgeführt
                {
                        if (DurchlaufendeSpielzeit && StrafwurfStop) //bei durchlaufender  Spielzeit wird Strafwurf ewig verlängert
                        {
                                StrafwurfTimer = Strafwurf + 1;
                        }

                        if (StrafwurfTimer > 0)
                        {
                                StrafwurfTimer--;
                                zeigSekundenAn78(StrafwurfTimer);
                        }
                        else
                        {
                                if (nachSpielZeit == 0)
                                { Stop = millis(); }                  // Strafwurf zuende - Zeit wird angehalten falls noch keine Nachspielzeit erreicht ist
                                istStrafwurf = false;
                                kurzesHupen = 1;                    //kurzesHupen wird ausgeführt

                                // Anzeige von Strafwurf auf Strafzeiten umstellen
                                zeigStrafzeiten(AnzahlStrafzeiten, kleinsteStrafzeit);
                        }
                }

                #if OUTPUT_BLUETOOTH
                SendBluetooth();
                #endif
        }

        ////// HALPZEITPAUSE

        //TimerHalbzeitPause +1 ?????
        if (istHalbzeitPause && (StartTimerHalbzeitPause - (TimerHalbzeitPause) * 1000 < millis()))
        {
                TimerHalbzeitPause--;

                zeigSpielzeit(TimerHalbzeitPause);

                if (TimerHalbzeitPause==0)                                             // Die Halbzeit ist zu ende - Fertig machen für Spielbeginn
                {
                        StartTimerHalbzeitPause=0;
                        TimerHalbzeitPause=HalbzeitPause;
                        istHalbzeitPause=false;
                        Start = millis();
                        TimerSpielzeit = Spieldauer;
                        Start = Start + TimerSpielzeit * 1000;
                        Stop = millis();
                        zeigSpielzeit(TimerSpielzeit);

                }
                #if OUTPUT_BLUETOOTH
                SendBluetooth();
                #endif
        }
}
