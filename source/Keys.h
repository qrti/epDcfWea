#pragma once

#include <arduino.h>

#define TKCYC			10					// key cycle time in ms
#define CSHORT		   (50 / TKCYC)			// short press cycles
#define CLONG		   (2000 / TKCYC)		// long press cycles

#define NUMKEYS			2	

#define KEY0_PIN		26					// PA2
#define KEY1_PIN		27					// PA3

class Keys
{
public:
	Keys();
	~Keys();

	static void init(uint8_t, void (*)(), void (*)());
	static void check();

private:
	static void shortPress(uint8_t);
	static void longPress(uint8_t);

	static void (*shortFunc[NUMKEYS])();
	static void (*longFunc[NUMKEYS])();
	static uint8_t pin[NUMKEYS];
	static uint8_t cnt[NUMKEYS];
	static uint8_t nuk;
};
