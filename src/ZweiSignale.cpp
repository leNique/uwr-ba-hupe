#include "config.h"

#ifndef ZweiSignale_H
#define ZweiSignale_H
#include "ZweiSignale.h"
#endif 
#ifndef SendBluetooth_H
#define SendBluetooth_H
#include "SendBluetooth.h"
#endif 

void ZweiSignale(int i, bool val)
{
        if (val == 1)
        {
                if (TimerHupen[i] == 0 && HupStatus[i] == 0)
                {
                        TimerHupen[i] = millis();
                        HupStatus[i] = 1;
                        Fehler[i] = 0;
                }
        }

        if (TimerHupen[i] + 1200 < millis())    //Rücksetzung keine 2 Hupsignale erkannt
        {
                TimerHupen[i] = 0;
                HupStatus[i] = 0;
                Fehler[i] = 0;
                StopMerker[i] = 0; // StopMerker zurücksetzen (automatisches Hupen ist wieder freigegeben)
                AbhupenVerboten[i] = 0;
        }

        if ((HupStatus[i] == 1 || HupStatus[i] == 4) && val == 0) // Fehler erkannt
        {
                Fehler[i]++;
        }




        if (val == 1 && HupStatus[i] == 1 && TimerHupen[i] < millis() - 40 && Fehler[i] < 20)
        {
                HupStatus[i] = 2;          // Erstes Hupsignal wurde bestätigt
                StopMerker[i] = millis();    //StopMerker setzen falls 2. Signal erkannt wird und kein Druchlaufen Spielzeit...
                AbhupenVerboten[i] = 1;
                Fehler[i] = 0;
                TimerHupen[i] = millis();
        }
        if (val == 1 && HupStatus[i] == 2)         //Erstes Signal bestätigt - darf aber unendlich lange sein
        {
                TimerHupen[i] = millis();
        }

        if (val == 0 && HupStatus[i] == 2 && TimerHupen[i] < millis() - 50 )
        {
                HupStatus[i] = 3;          // Pause erkannt  - Pause muss mindestens 50 mSec lang sein
                TimerHupen[i] = millis();
                TimerHupenPause[i] = millis();
        }
        if (val == 0 && HupStatus[i] == 3 && TimerHupenPause[i] > millis() - 1500) // max. 1,5 Sekunden auf Pause fertig warten
        {
                TimerHupen[i] = millis(); //Pause bestätigt
        }

        if (val == 1 && HupStatus[i] == 3)           // 2. Signal erkannt - Pause beendet
        {
          TimerHupen[i] = millis();
          HupStatus[i] = 4;
          Fehler[i] = 0;
        }


        if (val == 1 && HupStatus[i] == 4 && TimerHupen[i] < millis() - 50 && Fehler[i] < 20)     // 2. Signal bestätigt
        {
                Fehler[i] = 0;
                TimerHupen[i] = 0;
                HupStatus[i] = 0;
                if (!DurchlaufendeSpielzeit)
                {
                        //Stop = millis(); //Zeit wird angehalten wenn keine durchlaufende Spielzeit
                        Stop = StopMerker[i]; //Zeit wird angehalten aber zur am 1. Hupen erkannten Spielzeit
                        StopMerker[i]=0; // StopMerker zurücksetzen (automatisches Hupen ist wieder freigegeben)
                }

                if (istStrafwurf)
                {
                        istStrafwurf = false;
                        
                        // Anzeige von Strafwurf auf Strafzeiten umstellen
                        //zeigStrafzeiten(AnzahlStrafzeiten, kleinsteStrafzeit);
                        zeigStrafwurfZeitSek = Strafwurf-StrafwurfTimer;
                        StrafwurfTimer = 0;
                        zeigStrafwurfZeitTimer = millis();
                        SendBluetooth();
                }
        }
}
