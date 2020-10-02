#pragma once

#include "libraries/epdpaint.h"

#define DSIZEX	128L							// display size x		display is natively portrait
#define DSIZEY	296L							// display size y		for rotation 90 degree x and y are swapped
#define ISIZE	DSIZEX * DSIZEY / 8				// image size in bytes

#define PIN_LED		        24					// PA0			minimal ATMEGA board default
#define LED_OFF		        HIGH				// LED off		negative logic, anode is Vcc
#define LED_ON		        LOW					// LED on		

#define SAVE_DELAY          10                  // seconds delay after normal settings change
#define NUMSETS             5                   // number of settings  

#define SET_DATEFORM        0                   // basic settings
#define SET_DCFLOG          1
#define SET_FONT            2                   // normal settings
#define SET_HEADLINE        3
#define SET_WEACHA          4

#define SET_NORMAL          SET_FONT            // first normal setting

#define HEAD_WEA            0                   // head lines
#define HEAD_DATE           1
#define HEAD_INFO           2

extern Paint paint;

typedef struct setStruct
{
    uint8_t numItems;       // number of selections
    uint8_t sel;            // selected item
}setStruct;
