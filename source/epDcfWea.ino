// epDcfWea.ino - V0.9 qrt@qland.de 190704
//
// todo
// - left button long press -> settings
// - settings, font, date format, dcf polarity
// - temperature/humidity graph

#include <Arduino.h>
#include <SPI.h>
#include <EEPROM.h>

#include "libraries/epd2in9.h"
#include "libraries/epdpaint.h"

#include "epDcfWea.h"
#include "Dcf.h"
#include "Wea.h"
#include "Text.h"

#include "font/consolas_4070.h"
#include "font/consolas_2234.h"
#include "font/courier_b_4070.h"
#include "font/courier_b_2234.h"
#include "font/sevenseg_2234.h"
#include "font/sevenseg_3870.h"

#define DEGREE		"\xc2""\xb0"						// for arduino serial

void transfer(void);										
void key0_short(void);
void key0_long(void);
void key1_short(void);
void key1_long(void);

Epd epd;
Dcf dcf;
Wea wea;
Text text;

unsigned char image[ISIZE];
Paint paint(image, DSIZEX, DSIZEY);

char buf[32];			

uint8_t setting = 0;
uint8_t font = 0;
uint8_t dafo = 0;
uint8_t sigl = 0;
uint8_t pumo = 0;

uint8_t chan = 0;
uint8_t weda = 0;

uint8_t eeSave;

void setup()
{
	//Serial.begin(57600);

	epd.Init(lut_full_update);							// init full update

	epd.ClearFrameMemory(0xff);							// 0 = black, 1 = white
	epd.DisplayFrame(POSTWAIT);

	epd.ClearFrameMemory(0xff);							// both buffers
	epd.DisplayFrame(POSTWAIT);
	
	paint.ClearWhite(ISIZE);

	font = EEPROM.read(EEFONT);
	if(font > NUMFONTS) font = 0;

	dafo = EEPROM.read(EEDAFO);			// dd.mm.yy, yy.mm.dd
	if(dafo > NUMDAFO) dafo = 0;

	sigl = EEPROM.read(EESILO);			// negative, positive
	if(sigl > NUMSILOS) sigl = 0;		

	pumo = EEPROM.read(EEPUMO);			// no pullup, pullup
	if(pumo > NUMPUMOS) pumo = 0;		

	chan = EEPROM.read(EECHAN);			// 0, 1, 2
	if(chan > NUMCHANS) chan = 0;

	weda = EEPROM.read(EEWEDA);			// wea, date, week/day
	if(weda > NUMWEDA) weda = 0;

	dcf.keys.init(KEY0_PIN, &key0_short, &key0_long);	// wea/date, settings			left 
	dcf.keys.init(KEY1_PIN, &key1_short, &key1_long);	// channel++, channel reset		right

	dcf.receive(sigl, pumo, false);
	wea.init();
}

void loop()
{
	static uint32_t lsecs;
	
	display();

	while(dcf.secs == lsecs)
		;

	lsecs = dcf.secs;
}

uint8_t const *fonts[] = { consolas_2234, consolas_4070, 
						   courier_b_2234, courier_b_4070,
						   sevenseg_2234, sevenseg_3870 };

void display()
{
	if(eeSave == 255){
		dcf.setLogPul(sigl, pumo);

		EEPROM.write(EEFONT, font);
		EEPROM.write(EEDAFO, dafo);
		EEPROM.write(EESILO, sigl);
		EEPROM.write(EEPUMO, pumo);
		eeSave = 0;
	}
	else if(eeSave > 15){
		EEPROM.write(EECHAN, chan);
		EEPROM.write(EEWEDA, weda);
		eeSave = 0;
	}

	if(eeSave && eeSave!=255)
		eeSave++;

	DateTimeDcf now = dcf.now();

	text.locate(0, 0);
	text.setFont(fonts[(font<<1) + 1]);
	getTime(now);

	text.locate(0, 93);
	text.setFont(fonts[font<<1]);

	wea.advanceRecTime();

	if(weda == 0)
		getChannel(chan);
	else
		getDate(now);

	wea.startRecTime();

	transfer();
}

void getTime(DateTimeDcf now)
{
	sprintf(buf, "%02u:%02u:%02u", now.hour(), now.minute(), now.second());
	text.writeText(buf);
}

#define FILL	0x04

bool togChan = true;

void getChannel(uint8_t ch)
{
	uint8_t status = wea.getStatus(ch);

	if(status == RECNO){
		sprintf(buf, "  -.-C  -%% %c%c", FILL, '1'+ch);
	}
	else{
		uint8_t c = '1' + ch;

		if(togChan){
			if(status==RECTO && dcf.secs&1)
				c = ' ';
			else if(status == RECCU)
				c = '*';
		}
		
		togChan = true;

		uint16_t t = wea.getTemp(ch);						// get temperature
		uint8_t tl = t >> 8;								// left decimal point
		uint8_t sg = t & 0x80 ? '-' : (t ? '+' : ' ');		// sign

		uint8_t h = wea.getHumi(ch);						// get humidity

		char tt = ' ';										// assume trend show pause
		char th = ' ';

		if(!(dcf.secs & 0x03)){								// show trend every 4 s for 1 s
			uint16_t trend = wea.getTrend(ch);				// get trend
			tt = 0x85 + (int8_t)(trend & 0xff);				// trend t, 0x85 = neutral trend char
			th = 0x85 + (int8_t)(trend >> 8);				//       h
		}

		if(tl < 10)
			sprintf(buf, " %c%d.%dC%c%2d%%%c%c%c", sg, tl, t&0x0f, tt, h, th, FILL, c);
		else
			sprintf(buf, "%c%d.%dC%c%2d%%%c%c%c", sg, tl, t&0x0f, tt, h, th, FILL, c);
	}

	text.writeText(buf);
}

void getDate(DateTimeDcf now)
{
	if(weda == 1)
		sprintf(buf, "%s %02d.%02d.%02d", now.dayOfWeekStr(), now.day(), now.month(), now.year()-2000);
	else if(weda == 2)
		sprintf(buf, "W%02d D%03d", now.weekOfYear(), now.dayOfYear());

	text.writeText(buf);
}

void transfer(void)										// transfer image to e-paper module
{
	static uint8_t fup;									// full update counter

	if(++fup)											// count inits
		epd.Init(lut_partial_update);					// init partial update
	else
		epd.Init(lut_full_update);						// init full update every 256 times

	epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());	// transfer image
	epd.DisplayFrame(POSTWAIT);							// display 
	epd.Sleep();										// sleep

	paint.ClearWhite(ISIZE);							// pre clear
}

void key0_short()
{
	if(setting){
		if(++setting >= NUMSETTINGS+1)					// switch settings
			setting = 1;
	}
	else{
		if(++weda >= NUMWEDA)							// switch wea/date/week-day
			weda = 0;

		togChan = false;
		eeSave = 1;
	}
}

void key0_long()
{
	if(setting){										// normal/settings
		setting = 1;									// first setting
	}
	else{
		setting = 0;									// settings off
		eeSave = 255;									// save settings
		togChan = false;
	}
}

void key1_short()
{
	if(setting){										// setting	
		if(setting == EEFONT){							
			if(++font >= NUMFONTS)						// font
				font = 0;
		}
		else if(setting == EEDAFO){
			if(++dafo >= NUMDAFO)						// date format
				dafo = 0;
		}
		else if(setting == EESILO){
			if(++sigl >= NUMSILOS)						// signal logic
				sigl = 0;
		}
		else if(setting == EEPUMO){
			if(++pumo >= NUMPUMOS)						// pullup mode
				pumo = 0;
		}

	}
	else{
		if(++chan >= NUMCHANS)							// channel
			chan = 0;

		togChan = false;
		eeSave = 1;
	}
}

void key1_long()			
{
	if(setting){
	}
	else{
		wea.resetChan(chan);							// reset channel
	}
}
