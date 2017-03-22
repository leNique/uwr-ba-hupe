#ifndef analog_buttons_h
#define analog_buttons_h

#if ANALOG_BUTTONS
#include "Arduino.h" // provides analogRead

const int btnRIGHT  = 0; // analog value: 0
const int btnUP     = 1; //  143
const int btnDOWN   = 2; //  327
const int btnLEFT   = 3; //  502
const int btnSELECT = 4; //  740
const int btnNONE   = 5; // 1023

int readAnalogButton(int pin)
{
    int adc_key_in = analogRead(pin);       // read the value from the sensor

    // A reading of 1023 is very likely, so we add this branch as a way of early termination.
    if (adc_key_in > 950) return btnNONE;

    if (adc_key_in <  71)  return btnRIGHT;
    if (adc_key_in < 235)  return btnUP;
    if (adc_key_in < 415)  return btnDOWN;
    if (adc_key_in < 620)  return btnLEFT;
    if (adc_key_in < 881)  return btnSELECT;

    return btnNONE;
}

#endif // ANALOG_BUTTONS

#endif
