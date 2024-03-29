#ifndef DrueckerAbfragen_H
#define DrueckerAbfragen_H
#include "DrueckerAbfragen.h"
#endif 


#define MinimaleHupZeit    100
#define HupeSperrZeit     2000

void DrueckerAbfragen()
{

  BounceDrueckerSpielleiter.update();
  BounceDrueckerUW1.update();
  BounceDrueckerUW2.update();

     // Drücker Spielleiter

  if (BounceDrueckerSpielleiter.read()==0 && TimerDrueckerSpielleiter==0 && BlockTimerDrueckerUW1 + HupeSperrZeit < millis() && BlockTimerDrueckerUW2 + HupeSperrZeit < millis())
  {
    TimerDrueckerSpielleiter=millis();
    BlockTimerDrueckerSpielleiter=millis();
    MinimalTimerDruecker=millis();
  }

  if (BounceDrueckerSpielleiter.read()==1 && MinimalTimerDruecker + MinimaleHupZeit < millis())
  {
    TimerDrueckerSpielleiter=0;
    DrueckerSpielleiter=false;
  }

  if (TimerDrueckerSpielleiter!=0 && TimerDrueckerSpielleiter+20 < millis())
  {
    DrueckerSpielleiter=true;       //Drücker wurde 20 ms gedrückt - bestätigt
    BlockTimerDrueckerSpielleiter=millis();
  }

     // Drücker UW 1

  if (BounceDrueckerUW1.read()==0 && TimerDrueckerUW1==0 && BlockTimerDrueckerSpielleiter + HupeSperrZeit < millis() && BlockTimerDrueckerUW2 + HupeSperrZeit < millis())
  {
    TimerDrueckerUW1=millis();
    BlockTimerDrueckerUW1=millis();
    MinimalTimerDruecker=millis();
  }

  if (BounceDrueckerUW1.read()==1 && MinimalTimerDruecker + MinimaleHupZeit < millis())
  {
    TimerDrueckerUW1=0;
    DrueckerUW1=false;
  }

  if (TimerDrueckerUW1!=0 && TimerDrueckerUW1+20 < millis())
  {
    DrueckerUW1=true;       //Drücker wurde 20 ms gedrückt - bestätigt
    BlockTimerDrueckerUW1=millis();
  }

     // Drücker UW 2

  if (BounceDrueckerUW2.read()==0 && TimerDrueckerUW2==0 && BlockTimerDrueckerUW1 + HupeSperrZeit < millis() && BlockTimerDrueckerSpielleiter + HupeSperrZeit < millis())
  {
    TimerDrueckerUW2=millis();
    BlockTimerDrueckerUW2=millis();
    MinimalTimerDruecker=millis();
  }

  if (BounceDrueckerUW2.read()==1 && MinimalTimerDruecker + MinimaleHupZeit < millis())
  {
    TimerDrueckerUW2=0;
    DrueckerUW2=false;
  }

  if (TimerDrueckerUW2!=0 && TimerDrueckerUW2+20 < millis())
  {
    DrueckerUW2=true;       //Drücker wurde 20 ms gedrückt - bestätigt
    BlockTimerDrueckerUW2=millis();
  }


}
