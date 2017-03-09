/*  Funktion: ZweiSignale
    Parameter:  i     - Typ: Integer
                        // [0,1,2]
                        // Indize des jeweiligen Hup-Drückers :-) todo
                val   - Typ: Boolean
                        // Rückgabewert von digitalRead([2,3,4])
                        // ?
*/

void ZweiSignale(int i, bool val)
{
        // kA
        if (val == 0)
        {
                if (TimerHupen[i] == 0 && HupStatus[i] == 0)
                {
                        TimerHupen[i] = millis();
                        HupStatus[i] = 1;
                        Fehler[i] = 0;
                }
        }

        // Keine 2 Hupsignale erkannt: Rücksetzen der Variablen
        if (TimerHupen[i] + 500 < millis())
        {
                TimerHupen[i] = 0;
                HupStatus[i] = 0;
                Fehler[i] = 0;
        }

        if ((HupStatus[i] == 1 || HupStatus[i] == 3) && val == 1) // Fehler erkannt
        {
                Fehler[i]++;
        }
        if (HupStatus[i] == 2 && val == 0)
        {
                Fehler[i]++;
        }


        if (val == 0 && HupStatus[i] == 1 && TimerHupen[i] < millis() - 40 && Fehler[i] < 20)
        {
                HupStatus[i] = 2;          // Erstes Hupsignal wurde bestätigt
                Fehler[i] = 0;
                TimerHupen[i] = millis();
        }
        if (val == 0 && HupStatus[i] == 2)
        {
                TimerHupen[i] = millis();
        }

        if (val == 1 && HupStatus[i] == 2 && TimerHupen[i] < millis() - 50 )
        {
                HupStatus[i] = 3;          // Pause erkannt
                Fehler[i] = 0;
                TimerHupen[i] = millis();
                TimerHupenPause[i] = millis();
        }
        if (val == 1 && HupStatus[i] == 3 && TimerHupenPause[i] > millis() - 200) // 2/10 Sekunde auf Pause fertig warten
        {
                TimerHupen[i] = millis(); //Pause bestätigt
                Fehler[i] = 0;
                HupStatus[i] = 4;
        }


        if (val == 0 && HupStatus[i] == 4 && TimerHupen[i] < millis() - 50 && Fehler[i] < 20)
        {
                Fehler[i] = 0;
                TimerHupen[i] = 0;
                HupStatus[i] = 0;
                if (DurchlaufendeSpielzeit == 0)
                {
                        Stop = millis(); //Zeit wird angehalten wenn keine durchlaufende Spielzeit
                }

                if (istStrafwurf == 1)
                {
                        istStrafwurf = 0;
                        StrafwurfTimer = 0;

                        lc.setChar(0, 1, ' ', false); //7. Led
                        lc.setChar(0, 0, ' ', false); //8. Led
                        // Anzeige von Strafwurf auf Strafzeiten umstellen
                        if (kleinsteStrafzeit <= 99 && AnzahlStrafzeiten != 0)
                        {
                                lc.setChar(0, 3, AnzahlStrafzeiten, false); //5. Led
                                lc.setChar(0, 1, kleinsteStrafzeit / 10, false); //7. Led
                                lc.setChar(0, 0, kleinsteStrafzeit % 10, false); //8. Led
                        }
                }

        }


}
