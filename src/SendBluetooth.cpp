#if OUTPUT_BLUETOOTH

void SendBluetooth ()
{
  itoa (TimerSpielzeit,BluetoothBuffer,10);
  strcpy(BluetoothString,BluetoothBuffer);
  strcat(BluetoothString,BluetoothTrennzeichen);

  itoa (Strafzeiten[0],BluetoothBuffer,10);
  strcat(BluetoothString,BluetoothBuffer);
  strcat(BluetoothString,BluetoothTrennzeichen);
  itoa (Strafzeiten[1],BluetoothBuffer,10);
  strcat(BluetoothString,BluetoothBuffer);
  strcat(BluetoothString,BluetoothTrennzeichen);
  itoa (Strafzeiten[2],BluetoothBuffer,10);
  strcat(BluetoothString,BluetoothBuffer);
  strcat(BluetoothString,BluetoothTrennzeichen);
  itoa (Strafzeiten[3],BluetoothBuffer,10);
  strcat(BluetoothString,BluetoothBuffer);
  strcat(BluetoothString,BluetoothTrennzeichen);
  itoa (Strafzeiten[4],BluetoothBuffer,10);
  strcat(BluetoothString,BluetoothBuffer);
  strcat(BluetoothString,BluetoothTrennzeichen);
  itoa (Strafzeiten[5],BluetoothBuffer,10);
  strcat(BluetoothString,BluetoothBuffer);
  strcat(BluetoothString,BluetoothTrennzeichen);

  itoa (StrafwurfTimer,BluetoothBuffer,10);
  strcat(BluetoothString,BluetoothBuffer);
  strcat(BluetoothString,BluetoothTrennzeichen);

    if (istHalbzeitPause)
    {
      itoa (TimerHalbzeitPause,BluetoothBuffer,10);
      strcat(BluetoothString,BluetoothBuffer);
      strcat(BluetoothString,"S");
    }
    else
    {
      strcat(BluetoothString,"0S");
    }

  Bluetooth.println(BluetoothString);

}
#endif
