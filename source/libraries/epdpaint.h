/**
 *  @filename   :   epdpaint.h
 *  @brief      :   Header file for epdpaint.cpp
 *  @author     :   Yehui from Waveshare
 *  
 *  Copyright (C) Waveshare     July 28 2017
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

#ifndef EPDPAINT_H
#define EPDPAINT_H

// Display orientation
#define ROTATE_0            0
#define ROTATE_90           1
#define ROTATE_180          2
#define ROTATE_270          3

#define COLBLACK    0
#define COLWHITE	1
#define COLXY11		2
#define COL11		3
#define COL21		4

#include "fonts.h"

class Paint {
public:
    Paint(unsigned char* image, int width, int height);
    ~Paint();

    int  GetWidth(void);
    void SetWidth(int width);
    int  GetHeight(void);
    void SetHeight(int height);
    int  GetRotate(void);
    void SetRotate(int rotate);
    unsigned char* GetImage(void);

	void Clear(uint8_t col);
	void ClearWhite(uint16_t isize);
    void DrawAbsolutePixel(uint16_t x, uint16_t y, uint8_t col);
    void DrawAbsolutePixel(uint16_t x, uint16_t y);
    void DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t col);
    void DrawLineH(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t col);
    void DrawLineV(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t col);
	void resPac(void);
    void DrawCharAt(uint16_t x, uint16_t y, char ascii_char, sFONT* font, uint8_t col);
	void DrawStringAt(uint16_t x, uint16_t y, const char* text, sFONT* font, uint8_t col);

    void DrawPixel(int x, int y, int colored);
    void DrawCharAtO(int x, int y, char ascii_char, sFONT* font, int colored);
    void DrawStringAtO(int x, int y, const char* text, sFONT* font, int colored);

    void DrawHorizontalLine(int x, int y, int width, int colored);
    void DrawVerticalLine(int x, int y, int height, int colored);
    void DrawRectangle(int x0, int y0, int x1, int y1, int colored);
    void DrawFilledRectangle(int x0, int y0, int x1, int y1, int colored);
    void DrawCircle(int x, int y, int radius, int colored);
    void DrawFilledCircle(int x, int y, int radius, int colored);

private:
    unsigned char* image;
    int width;
    int height;
    int rotate;
	uint8_t pac;				// pattern counter
};

#endif

/* END OF FILE */

