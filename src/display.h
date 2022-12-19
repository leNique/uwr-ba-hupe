#ifndef gloabals_H
#define gloabals_H
#include "globals.h"
#endif 

void clearDigits234();
void clearDigit5();
void clearDigits5678();
void clearDigits578();
void clearDigits78();
void clearDisplay();
void zeigReset();
void zeigSetup();
void zeigSetupIndikator(char c);
void zeigSetupDurchlaufendeSpielzeit(bool isDurchlaufend);
void zeigSekundenAn78(int sekunden);
void zeigAnzahlStrafzeiten(int anzahl);
void zeigStrafzeiten(int anzahl, int kuerzesteStrafzeit);
void zeigStrafwurfZeit(int StrafwurfZeitSek);
void zeigSpielzeit(int spielzeit);
void zeigWerGehuptHat(char c);
void zeigHalbzeit();
