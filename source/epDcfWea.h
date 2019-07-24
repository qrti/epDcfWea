#pragma once

#include "libraries/epdpaint.h"

#define DSIZEX	128L							// display size x		display is natively portrait
#define DSIZEY	296L							// display size y		for rotation 90 degree x and y are swapped
#define ISIZE	DSIZEX * DSIZEY / 8				// image size in bytes

//#define LED_PIN		24						// PA0			minimal ATMEGA board default
//#define LED_OFF		1						// LED off		negative logic, anode is Vcc
//#define LED_ON		0						// LED on		

#define NUMCHANS	3							// number of channels
#define NUMWEDA		3							// wea/date/week-days

#define NUMFONTS	3							// number of fonts
#define NUMDAFO		2							//		     date formats
#define NUMSILOS	2							//			 signal logic
#define NUMPUMOS	2							//			 pullup mode
#define	NUMSETTINGS	4							//			 settings

#define EEFONT		1							// font
#define EEDAFO		2							// date format
#define EESILO		3							// signal logic
#define EEPUMO		4							// pullup mode

#define EECHAN		10							// wea channel				EEPROM addresses	
#define EEWEDA		11							// wea or date						

extern Paint paint;
