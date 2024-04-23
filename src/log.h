#ifndef gloabals_H
#define gloabals_H
#include "globals.h"
#endif 

// Zum Logen wird dieses Modul verwendet - Wemos D1 Data Logger Mini Shield+RTC DS1307 Clock For -

// change this to match your SD shield or module;
// WeMos Micro SD Shield V1.0.0: D8
// LOLIN Micro SD Shield V1.2.0: D4 (Default)
const int chipSelect = D4;


void SD_Setup();
void SD_WRITE_LOG();
void readDS1307time(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year);
byte bcdToDec(byte val);
