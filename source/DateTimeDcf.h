#pragma once

#define SECONDS_PER_DAY         86400L

#include "Arduino.h"

class DateTimeDcf
{
public:
    DateTimeDcf(uint32_t t=0);
    DateTimeDcf(uint16_t year, uint8_t month, uint8_t day, uint8_t hour=0, uint8_t min=0, uint8_t sec=0);
    DateTimeDcf(const char* date, const char* time);

    uint16_t year() const       { return 2000 + yOff; }
    uint8_t month() const       { return m; }
    uint8_t day() const         { return d; }
    uint8_t hour() const        { return hh; }
    uint8_t minute() const      { return mm; }
    uint8_t second() const      { return ss; }
    uint8_t dayOfWeek() const;
	const char* dayOfWeekStr() const;
	uint8_t weekOfYear() const;
	uint16_t dayOfYear() const;

    uint32_t getSecs() const;			// 32-bit time as seconds since 01.01.2000
	uint16_t getDays() const;			// days since 01.01.2000

private:
	uint16_t date2days(uint16_t, uint8_t, uint8_t) const;
	uint32_t time2secs(uint16_t, uint8_t, uint8_t, uint8_t) const; 

protected:
    uint8_t yOff, m, d, hh, mm, ss;
};
