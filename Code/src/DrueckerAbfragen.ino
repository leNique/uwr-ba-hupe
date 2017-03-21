void DrueckerAbfragen()
{

  BounceDrueckerSpielleiter.update();
  BounceDrueckerUW1.update();
  BounceDrueckerUW2.update();


  if (BounceDrueckerSpielleiter.read()==0 && TimerDrueckerSpielleiter==0)
  {
    TimerDrueckerSpielleiter=millis();
  }

  if (BounceDrueckerSpielleiter.read()==1)
  {
    TimerDrueckerSpielleiter=0;
    DrueckerSpielleiter=0;
  }

  if (TimerDrueckerSpielleiter!=0 && TimerDrueckerSpielleiter+20 < millis())
  {
    DrueckerSpielleiter=1;       //Drücker wurde 20 ms gedrückt - bestätigt
  }


  if (BounceDrueckerUW1.read()==0 && TimerDrueckerUW1==0)
  {
    TimerDrueckerUW1=millis();
  }

  if (BounceDrueckerUW1.read()==1)
  {
    TimerDrueckerUW1=0;
    DrueckerUW1=0;
  }

  if (TimerDrueckerUW1!=0 && TimerDrueckerUW1+20 < millis())
  {
    DrueckerUW1=1;       //Drücker wurde 20 ms gedrückt - bestätigt
  }


  if (BounceDrueckerUW2.read()==0 && TimerDrueckerUW2==0)
  {
    TimerDrueckerUW2=millis();
  }

  if (BounceDrueckerUW2.read()==1)
  {
    TimerDrueckerUW2=0;
    DrueckerUW2=0;
  }

  if (TimerDrueckerUW2!=0 && TimerDrueckerUW2+20 < millis())
  {
    DrueckerUW2=1;       //Drücker wurde 20 ms gedrückt - bestätigt
  }


}
