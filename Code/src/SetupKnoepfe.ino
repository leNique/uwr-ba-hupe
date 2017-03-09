void SetupKnoepfe()
{

        if (digitalRead(14) == 0 && Knopf1Timer < millis() - 500) // Reset initalisieren
        {
                Knopf1Timer = millis();
                Setup = 0;
        }


        if (digitalRead(15) == 0 && Knopf2Timer < millis() - 500)
        {
                Knopf2Timer = millis();

                if (Setup < 6)                 //Setup fortführen
                {
                        Setup++;
                        Knopf3beschleuniger = 0;
                        Knopf4beschleuniger = 0;
                }

                if (Setup == 6)              //Setup fertig - Spiel bereit - Uhr angehalten
                {
                        Start = millis();
                        TimerSpielzeit = Spieldauer;
                        TimerHalbzeitPause = HalbzeitPause;
                        Start = Start + TimerSpielzeit * 1000;
                        Stop = millis();
                        lc.setChar(0, 7, (TimerSpielzeit / 60) / 10, false); //1. Led
                        lc.setChar(0, 6, (TimerSpielzeit / 60) % 10, false); //2. Led
                        lc.setChar(0, 5, (TimerSpielzeit % 60) / 10, false); //3. Led
                        lc.setChar(0, 4, (TimerSpielzeit % 60) % 10, false); //4. Led
                        lc.setChar(0, 3, ' ', false); //5. Led
                }


        }

        if (digitalRead(16) == 0 && Knopf3Timer < millis() - 500)
        {
                Knopf3Timer = millis();
                if (Knopf3beschleuniger < 6)
                {
                        Knopf3beschleuniger++;
                }

                if (Setup == 1)
                {
                        Spieldauer = Spieldauer + beschleunigerSchrittweite[Knopf3beschleuniger];
                }
                if (Setup == 2)
                {
                        Strafzeit = Strafzeit + beschleunigerSchrittweite[Knopf3beschleuniger];
                }
                if (Setup == 3)
                {
                        Strafwurf = Strafwurf + beschleunigerSchrittweite[Knopf3beschleuniger];
                }
                if (Setup == 4)
                {
                        DurchlaufendeSpielzeit = 1;
                        durchlaufendeZeitStop = 1;
                }
                if (Setup == 5)
                {
                        HalbzeitPause = HalbzeitPause + beschleunigerSchrittweite[Knopf3beschleuniger];
                }

        }
        if (Knopf3Timer < millis() - 510)
        {
                Knopf3beschleuniger = 0;
        }

        if (digitalRead(17) == 0 && Knopf4Timer < millis() - 500)
        {
                Knopf4Timer = millis();
                if (Knopf4beschleuniger < 6)
                {
                        Knopf4beschleuniger++;
                }

                if (Setup == 1 && Spieldauer - beschleunigerSchrittweite[Knopf4beschleuniger] > 0)
                {
                        Spieldauer = Spieldauer - beschleunigerSchrittweite[Knopf4beschleuniger];
                }
                if (Setup == 2 && Strafzeit - beschleunigerSchrittweite[Knopf4beschleuniger] > 0)
                {
                        Strafzeit = Strafzeit - beschleunigerSchrittweite[Knopf4beschleuniger];
                }
                if (Setup == 3 && Strafwurf - beschleunigerSchrittweite[Knopf4beschleuniger] > 0)
                {
                        Strafwurf = Strafwurf - beschleunigerSchrittweite[Knopf4beschleuniger];
                }
                if (Setup == 4)
                {
                        DurchlaufendeSpielzeit = 0;
                        durchlaufendeZeitStop = 0;
                }
                if (Setup == 5 && HalbzeitPause - beschleunigerSchrittweite[Knopf4beschleuniger] > 0)
                {
                        HalbzeitPause = HalbzeitPause - beschleunigerSchrittweite[Knopf4beschleuniger];
                }

        }
        if (Knopf4Timer < millis() - 510)
        {
                Knopf4beschleuniger = 0;
        }





        //Anzeige Setup
        if (Setup == 0)
        {
                lc.setRow(0, 7, B01011011); //  Punkt dann beginntend oben im Uhrzeigersinn
                //lc.setChar(0, 6, 'e', false); //2. Led
                lc.setChar(0, 6, 'e', false); //2. Led
                lc.setRow(0, 5, B00001111); //3. Led
                lc.setRow(0, 4, B00111110); //4. Led
                lc.setChar(0, 3, 'p', false); //5. Led
                lc.setChar(0, 2, ' ', false); //6. Led
                lc.setChar(0, 1, ' ', false); //7. Led
                lc.setChar(0, 0, ' ', false); //8. Led

                for (int i = 0; i < 6; i++) // Strafzeiten löschen falls vorhanden
                {Strafzeiten[i] = 0;}
                StrafwurfTimer = 0; // Strafwurf löschen falls vorhanden
                istStrafwurf = 0;
        }

        if (Setup == 1)
        {
                lc.setChar(0, 7, (Spieldauer / 60) / 10, false); //1. Led
                lc.setChar(0, 6, (Spieldauer / 60) % 10, false); //2. Led
                lc.setChar(0, 5, (Spieldauer % 60) / 10, false); //3. Led
                lc.setChar(0, 4, (Spieldauer % 60) % 10, false); //4. Led
                lc.setChar(0, 3, 'A', false); //5. Led
        }

        if (Setup == 2)
        {
                lc.setChar(0, 7, (Strafzeit / 60) / 10, false); //1. Led
                lc.setChar(0, 6, (Strafzeit / 60) % 10, false); //2. Led
                lc.setChar(0, 5, (Strafzeit % 60) / 10, false); //3. Led
                lc.setChar(0, 4, (Strafzeit % 60) % 10, false); //4. Led
                lc.setChar(0, 3, 'B', false); //5. Led
        }

        if (Setup == 3)
        {
                lc.setChar(0, 7, (Strafwurf / 60) / 10, false); //1. Led
                lc.setChar(0, 6, (Strafwurf / 60) % 10, false); //2. Led
                lc.setChar(0, 5, (Strafwurf % 60) / 10, false); //3. Led
                lc.setChar(0, 4, (Strafwurf % 60) % 10, false); //4. Led
                lc.setChar(0, 3, 'C', false); //5. Led
        }

        if (Setup == 4)
        {
                lc.setChar(0, 7, DurchlaufendeSpielzeit, false); //1. Led
                lc.setChar(0, 6, ' ', false); //2. Led
                lc.setChar(0, 5, ' ', false); //3. Led
                lc.setChar(0, 4, ' ', false); //4. Led
                lc.setChar(0, 3, 'D', false); //5. Led
        }

        if (Setup == 5)
        {
                lc.setChar(0, 7, (HalbzeitPause / 60) / 10, false); //1. Led
                lc.setChar(0, 6, (HalbzeitPause / 60) % 10, false); //2. Led
                lc.setChar(0, 5, (HalbzeitPause % 60) / 10, false); //3. Led
                lc.setChar(0, 4, (HalbzeitPause % 60) % 10, false); //4. Led
                lc.setChar(0, 3, 'E', false); //5. Led
        }
}
