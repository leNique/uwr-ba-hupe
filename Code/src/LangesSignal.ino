void LangesSignal (int i, bool val)
{
        if (Stop != 0 || DurchlaufendeSpielzeit == 1)
        {
                if (val == 0 && LangesHupenStatus[i] == 0)
                {
                        TimerLangesHupen[i] = millis();
                        LangesHupenStatus[i] = 1;
                        LangesHupenFehler[i] = 0;
                }

                if (val == 1 && LangesHupenStatus[i] == 1)
                {
                        LangesHupenFehler[i]++;
                }

                if (LangesHupenStatus[i] == 1 && TimerLangesHupen[i] + 700 < millis())
                {
                        TimerLangesHupen[i] = 0;
                        LangesHupenStatus[i] = 0;
                }

                if (val == 0 && LangesHupenStatus[i] == 1 && LangesHupenFehler[i] < 250 && TimerLangesHupen[i] + 450 < millis()) // 450 Millisekunden muss für langes Hupen mindestens gehupt werden
                {
                        TimerLangesHupen[i] = 0;     //LangesHupenerkannt    Uhr läuft weiter
                        LangesHupenStatus[i] = 0;
                        if (DurchlaufendeSpielzeit == 0)
                        {
                                Start = Start + millis() - Stop;
                                Stop = 0;
                        }

                        if (DurchlaufendeSpielzeit == 1 && durchlaufendeZeitStop == 1) //durchlaufende Zeit - Spiel starten
                        {
                                durchlaufendeZeitStop = 0;
                                Start = Start + millis() - Stop;
                                Stop = 0;
                        }

                        if (StrafwurfStop == 1 && istStrafwurf == 1) //durchlaufende Zeit - Strafwurf ausführen
                        {
                                StrafwurfStop = 0;
                        }
                }
        }
}
