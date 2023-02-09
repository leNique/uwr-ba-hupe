#include "constants.h"

#ifndef AutomatischHupen_H
#define AutomatischHupen_H
#include "AutomatischHupen.h"
#endif 


void AutomatischHupen ()
{
        if (langesHupen>0)      //langes Abhupen (Spielende)
        {
                // 1. Hupen
                if (langesHupen==1)
                {Abhupen=millis(); langesHupen++; digitalWrite(PinHorn, LOW);}
                if (langesHupen==2)
                {
                        if (Abhupen<millis()-1500)
                        {langesHupen++;}
                }
                if (langesHupen==3)
                {Abhupen=millis(); langesHupen++; digitalWrite(PinHorn, HIGH);}
                if (langesHupen==4)
                {
                        if (Abhupen<millis()-500)
                        {langesHupen++;}
                }

                // 2. Hupen

                if (langesHupen==5)
                {Abhupen=millis(); langesHupen++; digitalWrite(PinHorn, LOW);}
                if (langesHupen==6)
                {
                        if (Abhupen<millis()-1500)
                        {langesHupen++;}
                }
                if (langesHupen==7)
                {Abhupen=millis(); langesHupen++; digitalWrite(PinHorn, HIGH);}
                if (langesHupen==8)
                {
                        if (Abhupen<millis()-500)
                        {langesHupen++;}
                }

                // 3. Hupen

                if (langesHupen==9)
                {Abhupen=millis(); langesHupen++; digitalWrite(PinHorn, LOW);}
                if (langesHupen==10)
                {
                        if (Abhupen<millis()-1500)
                        {langesHupen++;}
                }
                if (langesHupen==11)
                {Abhupen=millis(); langesHupen++; digitalWrite(PinHorn, HIGH);}
                if (langesHupen==12)
                {
                        if (Abhupen<millis()-500)
                        {langesHupen++;}
                }

                // 4. Hupen

                if (langesHupen==13)
                {Abhupen=millis(); langesHupen++; digitalWrite(PinHorn, LOW);}
                if (langesHupen==14)
                {
                        if (Abhupen<millis()-1500)
                        {langesHupen++;}
                }
                if (langesHupen==15)
                {Abhupen=millis(); langesHupen++; digitalWrite(PinHorn, HIGH); langesHupen=0;}

        }





        if (kurzesHupen>0)    // kurzes Abhupen (Strafwurf)
        {
                if (kurzesHupen==1)
                {Abhupen=millis(); kurzesHupen++; digitalWrite(PinHorn, LOW);}
                if (kurzesHupen==2)
                {
                        if (Abhupen<millis()-250)
                        {kurzesHupen++;}
                }
                if (kurzesHupen==3)
                {Abhupen=millis(); kurzesHupen++; digitalWrite(PinHorn, HIGH);}
                if (kurzesHupen==4)
                {
                        if (Abhupen<millis()-200)
                        {kurzesHupen++;}
                }

                if (kurzesHupen==5)
                {Abhupen=millis(); kurzesHupen++; digitalWrite(PinHorn, LOW);}
                if (kurzesHupen==6)
                {
                        if (Abhupen<millis()-250)
                        {kurzesHupen++;}
                }
                if (kurzesHupen==7)
                {Abhupen=millis(); kurzesHupen++; digitalWrite(PinHorn, HIGH);}
                if (kurzesHupen==8)
                {
                        if (Abhupen<millis()-200)
                        {kurzesHupen++;}
                }

                if (kurzesHupen==9)
                {Abhupen=millis(); kurzesHupen++; digitalWrite(PinHorn, LOW);}
                if (kurzesHupen==10)
                {
                        if (Abhupen<millis()-250)
                        {kurzesHupen++;}
                }
                if (kurzesHupen==11)
                {Abhupen=millis(); kurzesHupen++; digitalWrite(PinHorn, HIGH);}
                if (kurzesHupen==12)
                {
                        if (Abhupen<millis()-200)
                        {kurzesHupen++;}
                }

                if (kurzesHupen==13)
                {Abhupen=millis(); kurzesHupen++; digitalWrite(PinHorn, LOW);}
                if (kurzesHupen==14)
                {
                        if (Abhupen<millis()-250)
                        {kurzesHupen++;}
                }
                if (kurzesHupen==15)
                {Abhupen=millis(); kurzesHupen++; digitalWrite(PinHorn, HIGH);}
                if (kurzesHupen==16)
                {
                        if (Abhupen<millis()-200)
                        {kurzesHupen++;}
                }

                if (kurzesHupen==17)
                {Abhupen=millis(); kurzesHupen++; digitalWrite(PinHorn, LOW);}
                if (kurzesHupen==18)
                {
                        if (Abhupen<millis()-250)
                        {kurzesHupen++;}
                }
                if (kurzesHupen==19)
                {Abhupen=millis(); kurzesHupen++; digitalWrite(PinHorn, HIGH); kurzesHupen=0;}
        }

}
