void DrueckerAbfragen()
{

  if (digitalRead(PinDrueckerSpielleiter)==0 && TimerDrueckerSpielleiter==0)
  {
    TimerDrueckerSpielleiter=millis();
  }
  else
  {
    TimerDrueckerSpielleiter=0;
    DrueckerSpielleiter=0;
  }

  if (TimerDrueckerSpielleiter!=0 && TimerDrueckerSpielleiter+10 < millis())
  {
  }


  if (digitalRead(PinDrueckerUW1)==0 && TimerDrueckerUW1==0)
  {
    TimerDrueckerUW1=millis();
  }
  else
  {
    TimerDrueckerUW1=0;
    DrueckerUW1=0;
  }

  if (TimerDrueckerUW1!=0 && TimerDrueckerUW1+10 < millis())
  {
  }


  if (digitalRead(PinDrueckerUW2)==0 && TimerDrueckerUW2==0)
  {
    TimerDrueckerUW2=millis();
  }
  else
  {
    TimerDrueckerUW2=0;
    DrueckerUW2=0;
  }

  if (TimerDrueckerUW2!=0 && TimerDrueckerUW2+10 < millis())
  {
  }


}
