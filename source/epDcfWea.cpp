// epDcfWea.ino - V1.1 qrt@qland.de 201002
//
// ePaper drivers from https://github.com/waveshare/e-Paper
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

#include "libraries/fonts.h"

#define DEGREE		"\xc2""\xb0"					    // for arduino serial

void transfer(void);										
void key0_short(void);
void key0_long(void);
void key1_short(void);
void key1_long(void);

void display(void);
void getTime(DateTimeDcf);
void getChannel(uint8_t);
void getDate(DateTimeDcf);
void getSet(void);
void checkBasSet(void);

Epd epd;
Dcf dcf;
Wea wea;
Text text;

unsigned char image[ISIZE];
Paint paint(image, DSIZEX, DSIZEY);

setStruct set[] = {
    { 2, 0 },               // date format      dmy/ymd
    { 2, 0 },               // dcf logic        neg/pos
    { 3, 0 },               // font             0/1/2
    { 3, 0 },               // headline         wea/date/info
    { 3, 0 }                // wea channel      0/1/2
};

char buf[32];			

uint8_t seti = SET_FONT;    // set index for start
uint8_t sadeCnt;            // save delay counter

void setup()
{
	//Serial.begin(57600);

	epd.Init(lut_full_update);							// init full update

	epd.ClearFrameMemory(0xff);							// 0 = black, 1 = white
	epd.DisplayFrame(POSTWAIT);

	epd.ClearFrameMemory(0xff);							// both buffers
	epd.DisplayFrame(POSTWAIT);
	
	paint.ClearWhite(ISIZE);

    for(uint8_t i=0; i<NUMSETS; i++){                   // read settings from EEPROM
        set[i].sel = EEPROM.read(i);

        if(set[i].sel >= set[i].numItems)               // check range
            set[i].sel = 0;                             // default 0
    }

    checkBasSet();                                      // check if to enter basic settings 

	dcf.keys.init(KEY0_PIN, &key0_short, &key0_long);	// key 0, left 
	dcf.keys.init(KEY1_PIN, &key1_short, &key1_long);	// key 1, right               

	dcf.receive(set[SET_DCFLOG].sel, false);
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

void display(void)
{
	if(sadeCnt == 255){		                    // immediate save
        for(uint8_t i=0; i<SET_NORMAL; i++)
            EEPROM.write(i,set[i].sel);

		sadeCnt = 0;                            // save done
	}
	else if(sadeCnt > SAVE_DELAY+1){            // delayed save
        for(uint8_t i=SET_NORMAL; i<NUMSETS; i++)
            EEPROM.write(i,set[i].sel);

		sadeCnt = 0;                            // save done
	}

	if(sadeCnt && sadeCnt!=255)                 // if save delay active
		sadeCnt++;                              // count up save delay counter

	DateTimeDcf now = dcf.now();

	text.locate(0, 0);
	text.setFont(fonts[(set[SET_FONT].sel<<1) + 1]);
	getTime(now);

	text.locate(0, 93);
	text.setFont(fonts[set[SET_FONT].sel<<1]);

	wea.advanceRecTime();

    if(seti < SET_NORMAL)
        getSet();
    else if(set[SET_HEADLINE].sel == HEAD_WEA)
		getChannel(set[SET_WEACHA].sel);
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
	if(set[SET_HEADLINE].sel == HEAD_DATE)
		sprintf(buf, "%s %02d.%02d.%02d", now.dayOfWeekStr(), now.day(), now.month(), now.year()-2000);
	else if(set[SET_HEADLINE].sel == HEAD_INFO)
		sprintf(buf, "W%02d D%03d", now.weekOfYear(), now.dayOfYear());

	text.writeText(buf);
}

void getSet(void)
{
    if(seti == SET_DATEFORM)
	    sprintf(buf, "Date Form: %s", set[SET_DATEFORM].sel ? "ymd" : "dmy");
    else if(seti == SET_DCFLOG)
	    sprintf(buf, "DCF Logic: %s", set[SET_DCFLOG].sel ? "pos" : "neg");

    paint.DrawStringAt(DSIZEX-12, 0, buf, &Font24, 0x00);
}

void transfer(void)										// transfer image to e-paper module
{
	static uint8_t fup;									// full update counter

	if(++fup)											// count inits
		epd.Init(lut_partial_update);					// init partial update
	else
		epd.Init(lut_full_update);						// init full update every 256 times

	epd.SetFrameMemory(paint.GetImage(), 0, 0, paint.GetWidth(), paint.GetHeight());	// transfer image
	epd.DisplayFrame(POSTWAIT);     				    // display 
	epd.Sleep();										// sleep

	paint.ClearWhite(ISIZE);
}

void checkBasSet(void)
{
    pinMode(PIN_LED, OUTPUT);                             

    pinMode(KEY1_PIN, INPUT_PULLUP);
    delay(50);

    if(digitalRead(KEY1_PIN) == 0){                         // if key 1 pressed, execute basic settings
        seti = SET_DATEFORM;                                // dateform setting   
    
        while(digitalRead(KEY1_PIN) == 0){                  // wait until key 1 is released
            digitalWrite(PIN_LED, !digitalRead(PIN_LED));   // toggle LED
            delay(50);
        }

        digitalWrite(PIN_LED, LED_OFF);                     // LED off
    }

    delay(50);                                              // debounce
}

// basic settings
// while power on hold key1 until LED flashes
// key0 short switches settings
// key1 short switches selection
// key0 long  unused in basic settings
// key1 long  saves and exits basic settings
//
// normal settings (saved about SAVE_DELAY seconds after change)
// key0 short switches headline weather/date/info
// key1 short switches weather channel
// key0 long  switch font
// key1 long  resets current weather channel

void key0_short(void)
{
    if(seti < SET_NORMAL){                                  // switch basic settings
        if(++seti >= SET_NORMAL)                             
            seti = 0;
    }                       
    else{                                                   // normal setting, switch headline
        if(++set[SET_HEADLINE].sel >= set[SET_HEADLINE].numItems)
            set[SET_HEADLINE].sel = 0;

	    togChan = false;                                    // block channel toggle
	    sadeCnt = 1;                                        // delayed save
    }
}

void key0_long()                                            
{
    if(++set[SET_FONT].sel >= set[SET_FONT].numItems)       // normal setting, switch font
        set[SET_FONT].sel = 0;
}

void key1_short()
{
    if(seti < SET_NORMAL){                                  // switch basic selection
        if(++set[seti].sel >= set[seti].numItems)             
            set[seti].sel = 0;
    }
    else{                                                   // normal setting, switch channel
        if(set[SET_HEADLINE].sel == HEAD_WEA)
            if(++set[SET_WEACHA].sel >= set[SET_WEACHA].numItems)
                set[SET_WEACHA].sel = 0;

	    togChan = false;                                    // block channel toggle
	    sadeCnt = 1;                                        // delayed save
    }
}

void key1_long()			
{
    if(seti < SET_NORMAL){                                  // switch to normal settings
        seti = SET_NORMAL;                                  
	    togChan = false;                                    // block channel toggle
	    sadeCnt = 255;                                      // immediate save
    }                       
    else if(set[SET_HEADLINE].sel == HEAD_WEA){             // normal settings
	    wea.resetChan(set[SET_WEACHA].sel);				    // reset selected channel
    }
}
