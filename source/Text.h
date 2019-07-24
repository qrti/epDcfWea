#pragma once

#include <Arduino.h>
#include "libraries/epdpaint.h"
#include "epDcfWea.h"

class Text
{
public:
	Text();
	~Text();

    void setFont(const uint8_t*);
	void locate(int16_t x, int16_t y);
	void writeText(char* text);
	void writeChar(uint8_t c);
    void drawChar(const uint8_t*, int16_t, int16_t, uint8_t, uint8_t, uint8_t);    

private:
    const uint8_t* font;

	uint8_t fWidth;					// font max width
    uint8_t fHeight;				// font height
	uint8_t spacing;				// font spacing
	uint8_t numChar;				// font number of chars

    int16_t char_x;					// char position x
    int16_t char_y;					// char position y
};
