#ifndef log_H
#define log_H
#include "log.h"
#endif 



void SD_WRITE_LOG()
{
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  readDS1307time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  String filename = "";
  filename += String(year, DEC);
  filename += ".";
  filename += String(month, DEC);
  filename += ".";
  filename += String(dayOfMonth, DEC);
  filename += ".txt";
  
  String timestamp = "";
  timestamp += (hour<10?"0":"");
  timestamp += String(hour, DEC);
  timestamp += ":";
  timestamp += (minute<10?"0":"");
  timestamp += String(minute, DEC);
  timestamp += ":";
  timestamp += (second<10?"0":"");
  timestamp += String(second, DEC);
  timestamp += " - ";
  
  File target = SD.open(filename, FILE_WRITE);
  
  if (target) {

        target.println(timestamp+"Test, Test. 1, 2, 3.");

        target.close();
    }
    else {
        //Wenn die Datei nicht geöffnet werden kann, dann soll eine Fehlermeldung
        //ausgegeben werden.
        //Ein möglicher Fehler kann sein dass, die Datei bereits durch einen anderen 
        //Service geöffnet wurde.
        //Serial.println("Fehler beim Öffnen von text.txt.");
    }
  
  
}


void readDS1307time(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year){
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
  //Anfordern der ersten 7 Datenbyte  vom DS1307
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}

//Konvertiert Binärcodierte Dezimalzahl zu einer
//normalen Dezimalzahl.
byte bcdToDec(byte val){
  return( (val/16*10) + (val%16) );
}
