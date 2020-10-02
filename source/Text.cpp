#include "Text.h"

Text::Text()
{
}

Text::~Text()
{
}

void Text::setFont(const uint8_t* const font)
{
    this->font = font;

	fWidth = pgm_read_byte(&font[0]);							// font max width
    fHeight = pgm_read_byte(&font[1]);							//      height
	spacing = pgm_read_byte(&font[2]);							//      spacing
    numChar = pgm_read_byte(&font[3]);							//      number of chars
}

void Text::locate(int16_t x, int16_t y)
{
    char_x = x;
    char_y = y;
}

void Text::writeText(char* text)
{
	uint8_t i = 0;

	while(text[i])
		writeChar(text[i++]);
}

void Text::writeChar(uint8_t c)
{   
	if(c < ' '){
		char_x += c;
		return;
	}

    uint16_t i = 0;

    while(i<numChar && pgm_read_byte(&font[4+i*4])!=c)				// lookup char
        i++;

    if(i >= numChar)												// char present?
        return;

    i = 4 + i * 4;													// metrics table offset

    uint8_t cWidth = pgm_read_byte(&font[i+1]);						// char width    
    uint16_t offset = pgm_read_byte(&font[i+2])<<8 | pgm_read_byte(&font[i+3]);		// font table offset

    uint8_t sl, sr;													// left, right space

    if(c==':' || c=='.'){											// reduced space for :.
        sl = 0;
        sr = spacing;
    }
    else{															// normal space
        sl = (fWidth - cWidth) / 2;									// left  
        sr = fWidth - cWidth - sl + spacing;						// right 
    }

    drawChar(&font[offset], char_x, char_y, cWidth, sl, sr);		// draw char
    char_x += cWidth + sl + sr;										// next position
}

#define COMBITS     2												// compress bits	
#define COMBYTES    ((1 << COMBITS) - 1)							// compress bytes

void Text::drawChar(const uint8_t* p, int16_t x0, int16_t y0, uint8_t cWidth, uint8_t spcLeft, uint8_t spcRight)
{    
    const uint8_t* ctp = p + COMBYTES;								// compress table pointer
    uint8_t cts = 0;												//                shift counter

    uint16_t ucl = cWidth * ((fHeight+7) >> 3);						// uncomp data length
    const uint8_t* utp = ctp + ((ucl+COMBYTES) >> COMBITS);			//        table pointer

    for(uint8_t y=0; y<fHeight; y+=8){								// char height in byte pieces
        for(uint8_t x=0; x<cWidth; x++){							// char width
            uint8_t i = (pgm_read_byte(ctp) >> cts) & COMBYTES;		// compress table index
			uint8_t byte = i==COMBYTES ? pgm_read_byte(utp++) : pgm_read_byte(p+i);		// get byte
			
			if(byte){
				uint8_t yy = y0 + fHeight - y - 8;					// lastBit = y ? 0 : (8 - (fHeight & 7)) & 7

				while(byte){
					if(byte & 0x80)
						paint.DrawAbsolutePixel(yy, x0+spcLeft+x);

					byte <<= 1;
					yy++;
				}
			}
            if((cts += 2) > 6){										// advance shift counter and pointer
				cts = 0; 
				ctp++;
			}           
        }
    }
}
