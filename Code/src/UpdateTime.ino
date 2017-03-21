#include "bluetooth.h"

void UpdateTime()
{
        //TimerSpielzeit +1 ???
        if ((Start - (TimerSpielzeit) * 1000) < millis() - nachSpielZeit && (Stop == 0 || (DurchlaufendeSpielzeit == 1 && durchlaufendeZeitStop == 0)))
        {
                if (istStrafwurf == 1 && TimerSpielzeit == 1)
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

                if (istStrafwurf == 0)
                {
                        if (kleinsteStrafzeit <= 99 && AnzahlStrafzeiten != 0)
                        {
                                zeigStrafzeiten(AnzahlStrafzeiten, kleinsteStrafzeit);
                        }
                        if (AnzahlStrafzeiten == 0 )
                        {
                                clearDigits578();
                        }
                }
                else                   // Strafwurf MODUS wird gerade ausgeführt
                {
                        if (DurchlaufendeSpielzeit == 1 && StrafwurfStop == 1) //bei durchlaufender  Spielzeit wird Strafwurf ewig verlängert
                        {
                                StrafwurfTimer = Strafwurf+1;
                        }

                        if (StrafwurfTimer > 0)
                        {
                                StrafwurfTimer--;
                                zeigSekundenAn78(StrafwurfTimer);
                        }
                        else
                        {
                                if (nachSpielZeit==0)
                                { Stop = millis(); }                  // Strafwurf zuende - Zeit wird angehalten falls noch keine Nachspielzeit erreicht ist
                                istStrafwurf=0;
                                kurzesHupen=1;                    //kurzesHupen wird ausgeführt

                                // Anzeige von Strafwurf auf Strafzeiten umstellen
                                if (kleinsteStrafzeit <= 99 && AnzahlStrafzeiten != 0)
                                {
                                        zeigStrafzeiten(AnzahlStrafzeiten, kleinsteStrafzeit);
                                }
                        }


                }

                #if OUTPUT_BLUETOOTH
                itoa (TimerSpielzeit,BluetoothBuffer,10);
                strcpy(BluetoothString,BluetoothBuffer);
                strcat(BluetoothString,BluetoothTrennzeichen);

                itoa (Strafzeiten[0],BluetoothBuffer,10);
                strcat(BluetoothString,BluetoothBuffer);
                strcat(BluetoothString,BluetoothTrennzeichen);
                itoa (Strafzeiten[1],BluetoothBuffer,10);
                strcat(BluetoothString,BluetoothBuffer);
                strcat(BluetoothString,BluetoothTrennzeichen);
                itoa (Strafzeiten[2],BluetoothBuffer,10);
                strcat(BluetoothString,BluetoothBuffer);
                strcat(BluetoothString,BluetoothTrennzeichen);
                itoa (Strafzeiten[3],BluetoothBuffer,10);
                strcat(BluetoothString,BluetoothBuffer);
                strcat(BluetoothString,BluetoothTrennzeichen);
                itoa (Strafzeiten[4],BluetoothBuffer,10);
                strcat(BluetoothString,BluetoothBuffer);
                strcat(BluetoothString,BluetoothTrennzeichen);
                itoa (Strafzeiten[5],BluetoothBuffer,10);
                strcat(BluetoothString,BluetoothBuffer);
                strcat(BluetoothString,BluetoothTrennzeichen);

                itoa (StrafwurfTimer,BluetoothBuffer,10);
                strcat(BluetoothString,BluetoothBuffer);

                strcat(BluetoothString,";0");

                Bluetooth.println(BluetoothString);
                #endif
        }

        ////// HALPZEITPAUSE

        //TimerHalbzeitPause +1 ?????
        if (istHalbzeitPause==1 && (StartTimerHalbzeitPause - (TimerHalbzeitPause) * 1000 < millis()))
        {
                TimerHalbzeitPause--;

                zeigSpielzeit(TimerHalbzeitPause);

                if (TimerHalbzeitPause==0)                                             // Die Halbzeit ist zu ende - Fertig machen für Spielbeginn
                {
                        StartTimerHalbzeitPause=0;
                        TimerHalbzeitPause=HalbzeitPause;
                        istHalbzeitPause=0;
                        Start = millis();
                        TimerSpielzeit = Spieldauer;
                        Start = Start + TimerSpielzeit * 1000;
                        Stop = millis();
                        zeigSpielzeit(TimerSpielzeit);
                        clearDigits5678();

                        #if OUTPUT_BLUETOOTH
                        itoa (TimerSpielzeit,BluetoothBuffer,10);
                        strcpy(BluetoothString,BluetoothBuffer);
                        strcat(BluetoothString,";0;0;0;0;0;0;0;0");

                        Bluetooth.println(BluetoothString);
                        #endif
                }
                else
                {
                        #if OUTPUT_BLUETOOTH
                        itoa (TimerHalbzeitPause,BluetoothBuffer,10);
                        strcpy(BluetoothString,"0;0;0;0;0;0;0;0;");
                        strcat(BluetoothString,BluetoothBuffer);

                        Bluetooth.println(BluetoothString);
                        #endif
                }
        }
}
