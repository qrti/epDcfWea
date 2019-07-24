#include "Keys.h"

uint8_t Keys::pin[];
void (*Keys::shortFunc[])();
void (*Keys::longFunc[])();
uint8_t Keys::cnt[];
uint8_t Keys::nuk;

Keys::Keys()
{
}

Keys::~Keys()
{
}

void Keys::init(uint8_t _pin, void (*_shortFunc)(), void (*_longFunc)())
{
	if(nuk > NUMKEYS)
		return;

	pinMode(_pin, INPUT_PULLUP);

	pin[nuk] = _pin;
	shortFunc[nuk] = _shortFunc;
	longFunc[nuk++] = _longFunc;
}

void Keys::check()
{
	for(uint8_t k=0; k<nuk; k++){
		if(digitalRead(pin[k]) == 0){				// press
			if(cnt[k] == CLONG)		
				longPress(k);

			if(cnt[k] < 255)
				cnt[k]++;
		}
		else{										// release
			if(cnt[k]>CSHORT-1 && cnt[k]<CLONG)
				shortPress(k);

			cnt[k] = 0;
		}
	}
}

void Keys::shortPress(uint8_t k)
{
	shortFunc[k]();
}

void Keys::longPress(uint8_t k)
{
	longFunc[k]();
}
