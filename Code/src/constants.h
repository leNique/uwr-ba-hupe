#ifndef constants_h
#define constants_h

// Pins for UI buttons
const int PinButtonReset = 14;
const int PinButtonSetup = 15;
const int PinButtonPlus = 16;
const int PinButtonMinus = 17;

// Pins for other stuff
const int PinDrueckerSpielleiter = 2;
const int PinDrueckerUW1 = 3;
const int PinDrueckerUW2 = 4;
const int PinHorn = 5;

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
//test
