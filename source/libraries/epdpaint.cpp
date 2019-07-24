/**
 *  @filename   :   epdpaint.cpp
 *  @brief      :   Paint tools
 *  @author     :   Yehui from Waveshare
 *  
 *  Copyright (C) Waveshare     September 9 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <avr/pgmspace.h>
#include "epdpaint.h"
#include <arduino.h>

Paint::Paint(unsigned char* image, int width, int height) {
    this->rotate = ROTATE_0;
    this->image = image;
    /* 1 byte = 8 pixels, so the width should be the multiple of 8 */
    this->width = width % 8 ? width + 8 - (width % 8) : width;
    this->height = height;
}

Paint::~Paint() {
}

/**
 *  @brief: Getters and Setters
 */
unsigned char* Paint::GetImage(void) {
    return this->image;
}

int Paint::GetWidth(void) {
    return this->width;
}

void Paint::SetWidth(int width) {
    this->width = width % 8 ? width + 8 - (width % 8) : width;
}

int Paint::GetHeight(void) {
    return this->height;
}

void Paint::SetHeight(int height) {
    this->height = height;
}

int Paint::GetRotate(void) {
    return this->rotate;
}

void Paint::SetRotate(int rotate){
    this->rotate = rotate;
}

void Paint::Clear(uint8_t col) 
{
    for(uint16_t x=0; x<this->width; x++)
        for(uint16_t y=0; y<this->height; y++)
            DrawAbsolutePixel(x, y, col);
}

void Paint::ClearWhite(uint16_t isize) 
{
	for(uint16_t i=0; i<isize; i++)
		image[i] = 0xff;
}

void Paint::DrawAbsolutePixel(uint16_t x, uint16_t y, uint8_t col) 
{
	static uint8_t pcol;

	if(pcol != col){
		pac = 0;
		pcol = col;
	}

    if(x>=this->width || y>=this->height)
        return;

	if(col == COLXY11)
		col = (x ^ y) & 1 ? 0 : 1;
	else if(col == COL11)
		col = pac++ & 1 ? 1 : 0;
	else if(col == COL21)
		col = pac++ & 3 ? 1 : 0;

    if(col == COLBLACK)
        image[(x>>3) + (y<<4)] &= ~(0x80 >> (x & 7));
    else
        image[(x>>3) + (y<<4)] |= 0x80 >> (x & 7);
}

void Paint::DrawAbsolutePixel(uint16_t x, uint16_t y) 
{
    if(x>=this->width || y>=this->height)
        return;

	image[(x>>3) + (y<<4)] &= ~(0x80 >> (x & 7));
}

void Paint::resPac(void)
{
	pac = 0;
}

void Paint::DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t col)
{
    int8_t ax = 1, ay = 1;
    int16_t dx = x1 - x0;
    int16_t dy = y1 - y0;

    if(dx < 0){
        dx = -dx;
        ax = -ax;
    }

    if(dy < 0){
        dy = -dy;
        ay = -ay;
    }

    if((dx!=0 && dy!=0) || (dx==0 && dy==0)){
        if(dx >= dy){
            uint16_t r = dx / 2;

            for(uint16_t x=0; x<=dx; x++){
                r += dy;

                if(r >= dx){
                    r -= dx;
                    DrawAbsolutePixel(x0, y0, col);
                    x0 += ax;
                    y0 += ay;
                }
                else{
                    DrawAbsolutePixel(x0, y0, col);
                    x0 += ax;
                }
            }
        }
        else{
            uint16_t r = dy / 2;

            for(uint16_t y=0; y<=dy; y++){
                r += dx;

                if(r >= dy){
                    r -= dy;
                    DrawAbsolutePixel(x0, y0, col);
                    x0 += ax;
                    y0 += ay;
                }
                else{
                    DrawAbsolutePixel(x0, y0, col);
                    y0 += ay;
                }
            }
        }
    }
    else if(dx!=0 && dy==0){
        for(uint16_t x=0; x<=dx; x++){
            DrawAbsolutePixel(x0, y0, col);
            x0 += ax;
        }
    }
    else if(dx==0 && dy!=0){
        for(uint16_t y=0; y<=dy; y++){
            DrawAbsolutePixel(x0, y0, col);
            y0 += ay;
        }
    }
}

void Paint::DrawLineH(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t col)
{
	if(x0 > x1)
		while(x0 >= x1)
			DrawAbsolutePixel(x0--, y0, col);
	else
		while(x0 <= x1)
			DrawAbsolutePixel(x0++, y0, col);	
}

void Paint::DrawLineV(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t col)
{
	if(y0 > y1)
		while(y0 >= y1)
			DrawAbsolutePixel(x0, y0--, col);
	else
		while(y0 <= y1)
			DrawAbsolutePixel(x0, y0++, col);	
}

void Paint::DrawCharAt(uint16_t x, uint16_t y, char ascii_char, sFONT* font, uint8_t col) 
{
    uint16_t char_offset = (ascii_char - ' ') * font->Height * (font->Width / 8 + (font->Width % 8 ? 1 : 0));
    const uint8_t* ptr = &font->table[char_offset];

    for(uint16_t h=0; h<font->Height; h++){
        for(uint16_t w=0; w<font->Width; w++){
            if(pgm_read_byte(ptr) & (0x80 >> (w % 8)))
                DrawAbsolutePixel(x - h, y + w, col);

            if(w % 8 == 7) 
                ptr++;
        }

        if (font->Width % 8 != 0)
            ptr++;
    }
}
	
void Paint::DrawStringAt(uint16_t x, uint16_t y, const char* text, sFONT* font, uint8_t col) 
{
    const char* p_text = text;
    
    while(*p_text != 0){
        DrawCharAt(x, y, *p_text, font, col);
        y += font->Width;
        p_text++;
    }
}

/**
 *  @brief: this draws a pixel by the coordinates
 */
void Paint::DrawPixel(int x, int y, int colored) {
    int point_temp;
    if (this->rotate == ROTATE_0) {
        if(x < 0 || x >= this->width || y < 0 || y >= this->height) {
            return;
        }
        DrawAbsolutePixel(x, y, colored);
    } else if (this->rotate == ROTATE_90) {
        if(x < 0 || x >= this->height || y < 0 || y >= this->width) {
          return;
        }
        point_temp = x;
        x = this->width - y;
        y = point_temp;
        DrawAbsolutePixel(x, y, colored);
    } else if (this->rotate == ROTATE_180) {
        if(x < 0 || x >= this->width || y < 0 || y >= this->height) {
          return;
        }
        x = this->width - x;
        y = this->height - y;
        DrawAbsolutePixel(x, y, colored);
    } else if (this->rotate == ROTATE_270) {
        if(x < 0 || x >= this->height || y < 0 || y >= this->width) {
          return;
        }
        point_temp = x;
        x = y;
        y = this->height - point_temp;
        DrawAbsolutePixel(x, y, colored);
    }
}

/**
 *  @brief: this draws a charactor on the frame buffer but not refresh
 */
void Paint::DrawCharAtO(int x, int y, char ascii_char, sFONT* font, int colored) {
    int i, j;
    unsigned int char_offset = (ascii_char - ' ') * font->Height * (font->Width / 8 + (font->Width % 8 ? 1 : 0));
    const unsigned char* ptr = &font->table[char_offset];

    for (j = 0; j < font->Height; j++) {
        for (i = 0; i < font->Width; i++) {
            if (pgm_read_byte(ptr) & (0x80 >> (i % 8))) {
                DrawPixel(x + i, y + j, colored);
            }
            if (i % 8 == 7) {
                ptr++;
            }
        }
        if (font->Width % 8 != 0) {
            ptr++;
        }
    }
}

/**
*  @brief: this displays a string on the frame buffer but not refresh
*/
void Paint::DrawStringAtO(int x, int y, const char* text, sFONT* font, int colored) {
    const char* p_text = text;
    unsigned int counter = 0;
    int refcolumn = x;
    
    /* Send the string character by character on EPD */
    while (*p_text != 0) {
        /* Display one character on EPD */
        DrawCharAtO(refcolumn, y, *p_text, font, colored);
        /* Decrement the column position by 16 */
        refcolumn += font->Width;
        /* Point on the next character */
        p_text++;
        counter++;
    }
}

/**
*  @brief: this draws a horizontal line on the frame buffer
*/
void Paint::DrawHorizontalLine(int x, int y, int line_width, int colored) {
    int i;
    for (i = x; i < x + line_width; i++) {
        DrawPixel(i, y, colored);
    }
}

/**
*  @brief: this draws a vertical line on the frame buffer
*/
void Paint::DrawVerticalLine(int x, int y, int line_height, int colored) {
    int i;
    for (i = y; i < y + line_height; i++) {
        DrawPixel(x, i, colored);
    }
}

/**
*  @brief: this draws a rectangle
*/
void Paint::DrawRectangle(int x0, int y0, int x1, int y1, int colored) {
    int min_x, min_y, max_x, max_y;
    min_x = x1 > x0 ? x0 : x1;
    max_x = x1 > x0 ? x1 : x0;
    min_y = y1 > y0 ? y0 : y1;
    max_y = y1 > y0 ? y1 : y0;
    
    DrawHorizontalLine(min_x, min_y, max_x - min_x + 1, colored);
    DrawHorizontalLine(min_x, max_y, max_x - min_x + 1, colored);
    DrawVerticalLine(min_x, min_y, max_y - min_y + 1, colored);
    DrawVerticalLine(max_x, min_y, max_y - min_y + 1, colored);
}

/**
*  @brief: this draws a filled rectangle
*/
void Paint::DrawFilledRectangle(int x0, int y0, int x1, int y1, int colored) {
    int min_x, min_y, max_x, max_y;
    int i;
    min_x = x1 > x0 ? x0 : x1;
    max_x = x1 > x0 ? x1 : x0;
    min_y = y1 > y0 ? y0 : y1;
    max_y = y1 > y0 ? y1 : y0;
    
    for (i = min_x; i <= max_x; i++) {
      DrawVerticalLine(i, min_y, max_y - min_y + 1, colored);
    }
}

/**
*  @brief: this draws a circle
*/
void Paint::DrawCircle(int x, int y, int radius, int colored) {
    /* Bresenham algorithm */
    int x_pos = -radius;
    int y_pos = 0;
    int err = 2 - 2 * radius;
    int e2;

    do {
        DrawPixel(x - x_pos, y + y_pos, colored);
        DrawPixel(x + x_pos, y + y_pos, colored);
        DrawPixel(x + x_pos, y - y_pos, colored);
        DrawPixel(x - x_pos, y - y_pos, colored);
        e2 = err;
        if (e2 <= y_pos) {
            err += ++y_pos * 2 + 1;
            if(-x_pos == y_pos && e2 <= x_pos) {
              e2 = 0;
            }
        }
        if (e2 > x_pos) {
            err += ++x_pos * 2 + 1;
        }
    } while (x_pos <= 0);
}

/**
*  @brief: this draws a filled circle
*/
void Paint::DrawFilledCircle(int x, int y, int radius, int colored) {
    /* Bresenham algorithm */
    int x_pos = -radius;
    int y_pos = 0;
    int err = 2 - 2 * radius;
    int e2;

    do {
        DrawPixel(x - x_pos, y + y_pos, colored);
        DrawPixel(x + x_pos, y + y_pos, colored);
        DrawPixel(x + x_pos, y - y_pos, colored);
        DrawPixel(x - x_pos, y - y_pos, colored);
        DrawHorizontalLine(x + x_pos, y + y_pos, 2 * (-x_pos) + 1, colored);
        DrawHorizontalLine(x + x_pos, y - y_pos, 2 * (-x_pos) + 1, colored);
        e2 = err;
        if (e2 <= y_pos) {
            err += ++y_pos * 2 + 1;
            if(-x_pos == y_pos && e2 <= x_pos) {
                e2 = 0;
            }
        }
        if(e2 > x_pos) {
            err += ++x_pos * 2 + 1;
        }
    } while(x_pos <= 0);
}

/* END OF FILE */























