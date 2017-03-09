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

                lc.setChar(0, 7, (TimerSpielzeit / 60) / 10, false); //1. Led
                lc.setChar(0, 6, (TimerSpielzeit / 60) % 10, false); //2. Led
                lc.setChar(0, 5, (TimerSpielzeit % 60) / 10, false); //3. Led
                lc.setChar(0, 4, (TimerSpielzeit % 60) % 10, false); //4. Led

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
                                lc.setChar(0, 3, AnzahlStrafzeiten, false); //5. Led
                                lc.setChar(0, 1, kleinsteStrafzeit / 10, false); //7. Led
                                lc.setChar(0, 0, kleinsteStrafzeit % 10, false); //8. Led
                        }
                        if (AnzahlStrafzeiten == 0 )
                        {
                                lc.setChar(0, 3, ' ', false); //5. Led
                                lc.setChar(0, 1, ' ', false); //7. Led
                                lc.setChar(0, 0, ' ', false); //8. Led
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
                                lc.setChar(0, 1, StrafwurfTimer / 10, false); //7. Led
                                lc.setChar(0, 0, StrafwurfTimer % 10, false); //8. Led
                        }
                        else
                        {
                                if (nachSpielZeit==0)
                                {Stop = millis();}                  // Strafwurf zuende - Zeit wird angehalten falls noch keine Nachspielzeit erreicht ist
                                istStrafwurf=0;
                                kurzesHupen=1;                    //kurzesHupen wird ausgeführt

                                // Anzeige von Strafwurf auf Strafzeiten umstellen
                                if (kleinsteStrafzeit <= 99 && AnzahlStrafzeiten != 0)
                                {
                                        lc.setChar(0, 3, AnzahlStrafzeiten, false); //5. Led
                                        lc.setChar(0, 1, kleinsteStrafzeit / 10, false); //7. Led
                                        lc.setChar(0, 0, kleinsteStrafzeit % 10, false); //8. Led
                                }
                        }


                }

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
        }

        ////// HALPZEITPAUSE

        //TimerHalbzeitPause +1 ?????
        if (istHalbzeitPause==1 && (StartTimerHalbzeitPause - (TimerHalbzeitPause) * 1000 < millis()))
        {
                TimerHalbzeitPause--;

                lc.setChar(0, 7, (TimerHalbzeitPause / 60) / 10, false); //1. Led
                lc.setChar(0, 6, (TimerHalbzeitPause / 60) % 10, false); //2. Led
                lc.setChar(0, 5, (TimerHalbzeitPause % 60) / 10, false); //3. Led
                lc.setChar(0, 4, (TimerHalbzeitPause % 60) % 10, false); //4. Led

                if (TimerHalbzeitPause==0)
                {
                        StartTimerHalbzeitPause=0;
                        TimerHalbzeitPause=HalbzeitPause;
                        istHalbzeitPause=0;
                        Start = millis();
                        TimerSpielzeit = Spieldauer;
                        Start = Start + TimerSpielzeit * 1000;
                        Stop = millis();
                        lc.setChar(0, 7, (TimerSpielzeit / 60) / 10, false); //1. Led
                        lc.setChar(0, 6, (TimerSpielzeit / 60) % 10, false); //2. Led
                        lc.setChar(0, 5, (TimerSpielzeit % 60) / 10, false); //3. Led
                        lc.setChar(0, 4, (TimerSpielzeit % 60) % 10, false); //4. Led
                        lc.setChar(0, 3, ' ', false); //5. Led
                        lc.setChar(0, 2, ' ', false); //6. Led
                        lc.setChar(0, 1, ' ', false); //7. Led
                        lc.setChar(0, 0, ' ', false); //9. Led

                        itoa (TimerSpielzeit,BluetoothBuffer,10);
                        strcpy(BluetoothString,BluetoothBuffer);
                        strcat(BluetoothString,";0;0;0;0;0;0;0;0");

                        Bluetooth.println(BluetoothString);
                }
                else
                {
                        itoa (TimerHalbzeitPause,BluetoothBuffer,10);
                        strcpy(BluetoothString,"0;0;0;0;0;0;0;0;");
                        strcat(BluetoothString,BluetoothBuffer);

                        Bluetooth.println(BluetoothString);
                }
        }





}
