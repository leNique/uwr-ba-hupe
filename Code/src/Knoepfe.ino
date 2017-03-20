void Knoepfe ()
{
        if (digitalRead(14) == 0 && Knopf1Timer < millis() - 1000) // Reset initalisieren
        {
                Knopf1Timer = millis();
                Reset = 1;
        }
        if (Knopf1Timer + 2000 < millis())    // nach 2 Sekunden ResetModus beenden
        {
                if (Reset==1)
                {
                        lc.setChar(0, 7, (TimerSpielzeit / 60) / 10, false); //1. Led
                        lc.setChar(0, 6, (TimerSpielzeit / 60) % 10, false); //2. Led
                        lc.setChar(0, 5, (TimerSpielzeit % 60) / 10, false); //3. Led
                        lc.setChar(0, 4, (TimerSpielzeit % 60) % 10, false); //4. Led
                        lc.setChar(0, 3, ' ', false); //5. Led
                }
                Reset = 0;
        }

        if (Reset == 1)
        {
                lc.setRow(0, 7, B00000101); //  Punkt dann beginntend oben im Uhrzeigersinn
                lc.setChar(0, 6, 'e', false); //2. Led
                lc.setRow(0, 5, B01011011); //3. Led
                lc.setChar(0, 4, 'e', false); //4. Led
                lc.setRow(0, 3, B00001111); //5. Led
        }



        if (digitalRead(15) == 0 && Knopf2Timer < millis() - 1000) // Reset / Strafwurf
        {
                Knopf2Timer = millis();

                if (Reset == 1)                             // Reset tatsächlich auslösen
                {
                        Setup = 0;

                }

                if (Stop != 0 || DurchlaufendeSpielzeit == 1)                           //Strafwurf
                {

                        if (istStrafwurf == 1)
                        {
                                StrafwurfTimer = 0;
                                istStrafwurf = 0;
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
                        else
                        {
                                if (DurchlaufendeSpielzeit == 1)
                                {
                                        StrafwurfStop = 1;
                                }
                                istStrafwurf = 1;
                                StrafwurfTimer = Strafwurf;
                                lc.setChar(0, 1, StrafwurfTimer / 10, false); //7. Led
                                lc.setChar(0, 0, StrafwurfTimer % 10, false); //8. Led
                        }

                }

        }

        if (digitalRead(16) == 0 && Knopf3Timer < millis() - 1000) //Strafzeit
        {
                Knopf3Timer = millis();
                for (int i = 0; i < 6; i++)
                {
                        if (Strafzeiten[i] == 0)
                        {
                                Strafzeiten[i] = Strafzeit;
                                i = 6;
                        }
                }

                AnzahlStrafzeiten = 0;
                for (int i = 0; i < 6; i++)
                {
                        if (Strafzeiten[i] != 0)
                        {
                                AnzahlStrafzeiten++;
                        }
                        lc.setChar(0, 3, AnzahlStrafzeiten, false); //5. Led
                }
        }

        if (digitalRead(17) == 0 && Knopf4Timer < millis() - 800)
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

                        if (StrafwurfStop == 1 && istStrafwurf == 1) //durchlaufende Zeit - Strafwurf ausführen
                        {
                                StrafwurfStop = 0;
                        }

                }

        } //Ende Knopf4


}
