#ifndef config_h
#define config_h

// This is the actual config section.
// You can configure which outputs should be enabled.
#define OUTPUT_BLUETOOTH 1
#define OUTPUT_LCD 0
#define OUTPUT_LED 1
#define OUTPUT_SERIAL 0

// END OF CONFIG SECTION

// Check compiler flags to decide which board is used
#ifdef MEGA2560
#define BOARD_MEGA2560 1
#else
// Default board: Uno
#define BOARD_UNO 1
#endif

#include "constants.h"

#endif
