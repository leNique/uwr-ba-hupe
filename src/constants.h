// constants.h should not be included directly.
// Instead, include config.h

// TODO: for each board (uno and mega), find a pin layouts which accomodate everything:
//       3x referees
//       1x horn
//       4x UI buttons
//       2x Bluetooth
//       3x LED
//       - or -
//       6x LCD

#ifndef config_h
#include "Arduino.h" // provides A0
#include "config.h"
#endif

#ifndef constants_h
#define constants_h

// Pins for UI buttons
#if DIGITAL_BUTTONS
// UNO
const int PinButtonReset = 14;
const int PinButtonSetup = 15;
const int PinButtonPlus = 16;
const int PinButtonMinus = 17;
#endif

#if ANALOG_BUTTONS
// MEGA2560
const int PinAnalogButtons = A0;
#endif

// Pins for buttons and horn
#if BOARD_UNO
const int PinDrueckerSpielleiter = 2;
const int PinDrueckerUW1 = 3;
const int PinDrueckerUW2 = 4;
const int PinHorn = 5;
#endif

#if BOARD_MEGA2560
const int PinDrueckerSpielleiter = 22;
const int PinDrueckerUW1 = 23;
const int PinDrueckerUW2 = 24;
const int PinHorn = 25;
#endif

// Pins for LED display (LedControl)
#if OUTPUT_LED
// UNO
const int PinLedDout = 12;
const int PinLedClk = 11;
const int PinLedCs = 10;
const int LedNumDevices = 1;
#endif

// Pins for LCD display (LiquidCrystal)
#if OUTPUT_LCD
// MEGA2560
// RW is tied to GND
// data pins 0-3 are not used
const int PinLcdRs = 8;
const int PinLcdEnable = 9;
const int PinLcdD4 = 4;
const int PinLcdD5 = 5;
const int PinLcdD6 = 6;
const int PinLcdD7 = 7;
#endif

// Pins for Bluetooth module
#if OUTPUT_BLUETOOTH
// UNO
const int PinBluetoothRx = 9;
const int PinBluetoothTx = 8;
#endif

// Pins for Logging
#if LOGGING
#define SD_CARD_CS_PIN 6
#endif


// States of the Setup
enum SetupStates
{
  SetupStateHome = 0,
  SetupStateSpieldauer,
  SetupStateStrafzeit,
  SetupStateStrafwurf,
  SetupStateDurchlaufendeSpielzeit,
  SetupStateHalbzeitPause,
  SetupStateMax,
};

#endif
