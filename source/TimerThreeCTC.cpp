// timer 3 CTC mode routines qrt@qland.de 190321

#include "TimerThreeCTC.h"

TimerThreeCTC Timer3;										// preinstatiate

ISR(TIMER3_COMPA_vect)										// IR service routine that wraps a user defined function supplied by attachInterrupt
{
    Timer3.isrCallback();
}

void TimerThreeCTC::setPeriod(long microseconds)
{
    TCCR3A = 0;                                             // clear control register A 
    TCCR3B = _BV(WGM32);                                    // CTC mode

    long cycles = (F_CPU * microseconds) / 1000000L;                               

    if(cycles < RESOLUTION)              clockSelectBits = _BV(CS30);               // no prescale, full xtal
    else if((cycles >>= 3) < RESOLUTION) clockSelectBits = _BV(CS31);               // prescale by /8
    else if((cycles >>= 3) < RESOLUTION) clockSelectBits = _BV(CS31) | _BV(CS30);   // prescale by /64
    else if((cycles >>= 2) < RESOLUTION) clockSelectBits = _BV(CS32);               // prescale by /256
    else if((cycles >>= 2) < RESOLUTION) clockSelectBits = _BV(CS32) | _BV(CS30);   // prescale by /1024
    else cycles = RESOLUTION,            clockSelectBits = _BV(CS32) | _BV(CS30);   // request was out of bounds, set as maximum

    OCR3A = cycles - 1;                                                             // top
}

void TimerThreeCTC::attachInterrupt(void (*isr)(), long microseconds)
{
    setPeriod(microseconds);
    
    isrCallback = isr;                                          // register user's callback with the real ISR
    TIMSK3 = _BV(OCIE3A);										// enables CMP A IR
    
    sei();                                                      // ensures that IRs are globally enabled
    start();                                                    // start timer
}

void TimerThreeCTC::detachInterrupt()
{
    TIMSK3 &= ~_BV(OCIE3A);                                     // clears CMP A IR
}

void TimerThreeCTC::start()
{
    TCCR3B |= clockSelectBits;
}

void TimerThreeCTC::stop()
{
    TCCR3B &= ~(_BV(CS30) | _BV(CS31) | _BV(CS32));             // clears all clock selects bits
}

void TimerThreeCTC::restart()
{  
    stop();                                                     // stop   
    TCNT3 = 0;                                                  // reset timer
    TIFR3 = _BV(OCF3A);                                         // delete pending OCRA IR
    start();                                                    // start
}
