// DateTimeDcf.cpp qrt@qland.de 190326
//
// V1.4 added weekday string, bug fix weekday

#include "DateTimeDcf.h"

static const uint8_t daysInMonth[] PROGMEM = {
	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static const char weekDayStr[][3] = {
	"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su" 
};

uint8_t conv2d(const char* p) 
{
    uint8_t v = 0;

    if('0'<=*p && *p<='9')
        v = *p - '0';

	return 10 * v + *++p - '0';
}

DateTimeDcf::DateTimeDcf(uint32_t t) 
{
    ss = t % 60;
    t /= 60;
    mm = t % 60;
    t /= 60;
    hh = t % 24;
    uint16_t days = t / 24;
    uint8_t leap;

	for(yOff=0;; ++yOff){
        leap = yOff % 4 == 0;
        
		if(days < 365 + leap)
            break;
        
		days -= 365 + leap;
    }

    for(m=1;; ++m){
        uint8_t daysPerMonth = pgm_read_byte(daysInMonth + m - 1);
        
		if(leap && m == 2)
            ++daysPerMonth;
        
		if(days < daysPerMonth)
            break;
        
		days -= daysPerMonth;
    }

    d = days + 1;
}

DateTimeDcf::DateTimeDcf(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec) 
{
    if (year >= 2000)
        year -= 2000;
    
	yOff = year;
    m = month;
    d = day;
    hh = hour;
    mm = min;
    ss = sec;
}

DateTimeDcf::DateTimeDcf(const char* date, const char* time) 
{
    yOff = conv2d(date + 9);

	switch(date[0]){
        case 'J': m = date[1] == 'a' ? 1 : (date[2] == 'n' ? 6 : 7); break;
        case 'F': m = 2; break;
        case 'A': m = date[2] == 'r' ? 4 : 8; break;
        case 'M': m = date[2] == 'r' ? 3 : 5; break;
        case 'S': m = 9; break;
        case 'O': m = 10; break;
        case 'N': m = 11; break;
        case 'D': m = 12; break;
    }

    d = conv2d(date + 4);
    hh = conv2d(time);
    mm = conv2d(time + 3);
    ss = conv2d(time + 6);
}

uint8_t DateTimeDcf::dayOfWeek() const 
{
	return (getDays() + 5) % 7;						// +5 for 01.01.2000 is Sa
}

const char* DateTimeDcf::dayOfWeekStr() const
{
	return weekDayStr[dayOfWeek()];
}

uint8_t DateTimeDcf::weekOfYear() const
{
	uint8_t fwd = (date2days(yOff, 1, 1) + 5) % 7;	// first weekday of year, +5 for 01.01.2000 is Sa
	uint16_t yd = dayOfYear() - 1;					// day of year starting with 0
	return (yd + fwd) / 7 + (fwd>3 ? 0 : 1);		// ISO yearweek, 0 = last week of previous year
}

uint16_t DateTimeDcf::dayOfYear() const
{
	return getDays() - date2days(yOff, 1, 1) + 1;
}

uint32_t DateTimeDcf::getSecs() const 
{
	return time2secs(getDays(), hh, mm, ss);
}

uint16_t DateTimeDcf::getDays() const 
{
	return date2days(yOff, m, d);
}

uint16_t DateTimeDcf::date2days(uint16_t y, uint8_t m, uint8_t d) const
{
    if(y >= 2000)
        y -= 2000;

	uint16_t days = d;
    
	for(uint8_t i=1; i<m; ++i)
        days += pgm_read_byte(daysInMonth + i - 1);
    
	if(m>2 && y%4==0)
        ++days;
    
	return days + 365 * y + (y + 3) / 4 - 1;
}

uint32_t DateTimeDcf::time2secs(uint16_t days, uint8_t h, uint8_t m, uint8_t s) const
{
    return ((days * 24L + h) * 60 + m) * 60 + s;
}
