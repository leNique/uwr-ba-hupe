void LangesSignal (int i, bool val)
{
        if ((Stop != 0 && Stop + 8000 < millis()) || DurchlaufendeSpielzeit)    //nur ausführen wenn Zeit schon 8 Sec steht oder durchlaufende Zeit
        {
                if (val == 1 && LangesHupenStatus[i] == 0)    // Es wird gehupt und die Zeitmessung startet für langeshupen
                {
                        TimerLangesHupen[i] = millis();
                        LangesHupenStatus[i] = 1;
                        LangesHupenFehler[i] = 0;
                }

                if (val == 0 && LangesHupenStatus[i] == 1)   // Der Taster ist nicht gedrückt während Hupen (Fehler)
                {
                        LangesHupenFehler[i]++;
                }

                if (LangesHupenStatus[i] == 1 && TimerLangesHupen[i] + 700 < millis())    // es wurde kein langes Hupsignal erkannt - die Messung wird verworfen
                {
                        TimerLangesHupen[i] = 0;
                        LangesHupenStatus[i] = 0;
                }

                if (val == 1 && LangesHupenStatus[i] == 1 && LangesHupenFehler[i] < 250 && TimerLangesHupen[i] + 380 < millis()) // 380 Millisekunden muss für langes Hupen mindestens gehupt werden
                {
                        TimerLangesHupen[i] = 0;     //LangesHupenerkannt    Uhr läuft weiter
                        LangesHupenStatus[i] = 0;
                        if (!DurchlaufendeSpielzeit)
                        {
                                Start = Start + millis() - Stop;
                                Stop = 0;
                        }

                        if (DurchlaufendeSpielzeit && durchlaufendeZeitStop) //durchlaufende Zeit - Spiel starten
                        {
                                durchlaufendeZeitStop = false;
                                Start = Start + millis() - Stop;
                                Stop = 0;
                        }

                        if (StrafwurfStop && istStrafwurf) //durchlaufende Zeit - Strafwurf ausführen
                        {
                                StrafwurfStop = false;
                        }
                }
        }
}
