#ifndef bluetooth_h
#define bluetooth_h

#include "config.h"

#if OUTPUT_BLUETOOTH
#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(PinBluetoothRx, PinBluetoothTx);

#endif

#endif
