#ifndef gloabals_H
#define gloabals_H
#include "globals.h"
#endif 

// Zum Logen wird dieses Modul verwendet - Wemos D1 Data Logger Mini Shield+RTC DS1307 Clock For -


void SD_WRITE_LOG();
void readDS1307time(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year);
byte bcdToDec(byte val);
