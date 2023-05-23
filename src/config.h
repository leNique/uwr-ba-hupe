#ifndef config_h
#define config_h

// Use compiler flags to decide which board is used
#ifdef MEGA2560

#define BOARD_MEGA2560 1

#define ANALOG_BUTTONS 1

#define OUTPUT_BLUETOOTH 0
#define OUTPUT_LCD 1
#define OUTPUT_LED 0
#define OUTPUT_SERIAL 1

#else
// Default board: Uno

#define BOARD_UNO 1

#define DIGITAL_BUTTONS 1

#define OUTPUT_BLUETOOTH 1
#define OUTPUT_LCD 0
#define OUTPUT_LED 1
#define OUTPUT_SERIAL 0

#define LOGGING 0

#endif

#include "constants.h"

#endif
