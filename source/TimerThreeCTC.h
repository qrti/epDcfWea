#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Arduino.h"

#define RESOLUTION 65536

class TimerThreeCTC
{
public:  
    unsigned char clockSelectBits;

    void start();
    void stop();
    void restart();
    void attachInterrupt(void (*isr)(), long microseconds);
    void detachInterrupt();
    void setPeriod(long microseconds);
    void (*isrCallback)();
};

extern TimerThreeCTC Timer3;
