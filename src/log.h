#ifndef gloabals_H
#define gloabals_H
#include "globals.h"
#endif 


void SD_WRITE_LOG();
void readDS1307time(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year);
byte bcdToDec(byte val);
