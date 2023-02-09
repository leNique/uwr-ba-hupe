#ifndef display_H
#define display_H
#include "display.h"
#endif 
#ifndef UpdateTime_H
#define UpdateTime_H
#include "UpdateTime.h"
#endif 
#ifndef SendBluetooth_H
#define SendBluetooth_H
#include "SendBluetooth.h"
#endif 

void UpdateTime()
{
        //TimerSpielzeit +1 ???
        if ((Start - (TimerSpielzeit) * 1000) < millis() - nachSpielZeit && (Stop == 0 || (DurchlaufendeSpielzeit && !durchlaufendeZeitStop)))
        {
//Serial.print("langesh: ");
//Serial.print(LangesHupenFehler[2]);
                if (istStrafwurf && TimerSpielzeit == 1)
                {
                        nachSpielZeit = nachSpielZeit + 1000;
                }
                else
                {
                        if (TimerSpielzeit > 0)
                        {TimerSpielzeit--;}

                        if (StopMerker[0]==0 && StopMerker[1]==0 && StopMerker[2]==0)
                        {
                         AbhupenVerboten[0] = 0;
                         AbhupenVerboten[1] = 0;
                         AbhupenVerboten[2] = 0;
                        }
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
                        if (StrafwurfTimer <= 0)                      // Die 0. Sekunde soll nicht mitgezählt werden
                        {
                                if (nachSpielZeit == 0)
                                { Stop = millis(); }                  // Strafwurf zuende - Zeit wird angehalten falls noch keine Nachspielzeit erreicht ist
                                istStrafwurf = false;
                                kurzesHupen = 1;                    //kurzesHupen wird ausgeführt

                                // Anzeige von Strafwurf auf Strafzeiten umstellen
                                //zeigStrafzeiten(AnzahlStrafzeiten, kleinsteStrafzeit);
                                zeigStrafwurfZeitSek = Strafwurf-StrafwurfTimer;
                                zeigStrafwurfZeitTimer = millis();
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

        
        
        if (zeigStrafwurfZeitSek != 0)                              // Nach dem Strafwurf wird (blinkend 7sec) die für den Strafwurf benötigte Zeit angezeigt
        {
                if (zeigStrafwurfZeitTimer+1000>millis())
                {
                        zeigStrafwurfZeit(zeigStrafwurfZeitSek);
                }
                else if (zeigStrafwurfZeitTimer+1500>millis())
                {
                        zeigStrafwurfZeit(0);
                }
                else if (zeigStrafwurfZeitTimer+2500>millis())
                {
                        zeigStrafwurfZeit(zeigStrafwurfZeitSek);
                }
                else if (zeigStrafwurfZeitTimer+3000>millis())
                {
                        zeigStrafwurfZeit(0);
                }
                else if (zeigStrafwurfZeitTimer+4000>millis())
                {
                        zeigStrafwurfZeit(zeigStrafwurfZeitSek);
                }
                else if (zeigStrafwurfZeitTimer+4500>millis())
                {
                        zeigStrafwurfZeit(0);
                }
                else if (zeigStrafwurfZeitTimer+5500>millis())
                {
                        zeigStrafwurfZeit(zeigStrafwurfZeitSek);
                }
                else if (zeigStrafwurfZeitTimer+6000>millis())
                {
                        zeigStrafwurfZeit(0);
                }
                else if (zeigStrafwurfZeitTimer+7000>millis())
                {
                        zeigStrafwurfZeit(zeigStrafwurfZeitSek);
                }
                else 
                {
                 zeigStrafwurfZeitSek=0;
                 zeigStrafwurfZeitTimer=0;
                 zeigStrafzeiten(AnzahlStrafzeiten, kleinsteStrafzeit);
                }
        }

}
