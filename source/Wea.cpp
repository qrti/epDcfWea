#include "Wea.h"

uint8_t Wea::rowbuf[ROWBUFS][RBY];
uint8_t Wea::datbuf[DATBUFS][RBY]; 
uint8_t Wea::row, Wea::bit;

#if USE_AVERAGE
uint8_t Wea::avgCyc;
uint16_t Wea::sAvsT[];
uint8_t Wea::sAvgT[];
uint16_t Wea::fAvsT[];
uint8_t Wea::fAvgT[];
uint16_t Wea::sAvsH[];
uint8_t Wea::sAvgH[];
uint16_t Wea::fAvsH[];
uint8_t Wea::fAvgH[];
#endif

Wea::Wea()
{
}

Wea::~Wea()
{
}

#define SWAP(x)		asm( "swap	%0" : "+r" (x) );				// +r input = output

void Wea::init()
{
	pinMode(RX_PIN, INPUT);										// RX input no pullup
	attachInterrupt(digitalPinToInterrupt(RX_PIN), RX, CHANGE);	//    IR, INT2, both flanks

	TCCR1A = 0;													// T1 flags reset
	TCCR1B = 1<<CS11;											//	  normal, div 8, start
}

void Wea::RX()
{
#if RX_LOGIC==0
	if(PINB & 1<<PB2)
		Wea::bitStart();
	else
		Wea::bitEnd();
#else
	if(!(PINB & 1<<PB2))
		Wea::bitStart();
	else
		Wea::bitEnd();
#endif
}

void Wea::bitStart()
{
	TCNT1 = 0;
}

void Wea::bitEnd()
{
	uint16_t t = TCNT1;
	uint8_t i, c;

	if(t < PPMMIN)											// ignore small pulses
		return;												

	if(t < PPMLOW){											// bit 0?
		c = 0;
		goto addBit;
	}

	if(t < PPMHIG){											// bit 1?
		c = 1;
		goto addBit;
	}

	if(t < PPMROW)											// row?
		goto addRow;

	goto resRow;											// reset row

addBit:	
	if(bit >= RBI)											// row bit len exceed?
		goto resRow;		

	rowbuf[row][bit>>3] = rowbuf[row][bit>>3] << 1 | c;		// add bit
	bit++;
	return;

addRow:
	if(bit == RB42){	
		rowbuf[row][RBY-1] &= 0x0f;
	}
	else if(bit == RB36){		
		rowbuf[row][RBY-2] &= 0x0f;
		rowbuf[row][RBY-1] = 0x00;
	}
	else{
		goto resRow;
	}

check:
	i = ROWBUFS;										// number of row bufs
	c = ROWIDENT - 1;									// ident counter

	do{													// compare rows
		i--;											// row--

		if(row!=i && cmpRow(row, i) && --c==0)			// count ident rows
			goto decode;								// if enough ident rows decode 
	}while(i);

nextRow:
	if(++row >= ROWBUFS)								// next row in ringbuffer
		row = 0;

resRow:
	bit = 0;
	return;

decode:

// PPiiiiII II??CCTT TTttttTT TThhhhHH HHWB??XX ----XXPP	raw
// iiiiIIII ??CCTTTT ttttTTTT hhhhHHHH WB00XXXX PP			prepared
//										 ^^					sensor type 00 = S3318 		
// I = sensor ID (changes on battery change)
// C = channel number
// T = temperature
// H = humidity
// W = tx-button (0 regular, 1 button)
// B = battery (0 normal, 1 voltage < ~2.7 V)
// X = CRC4 poly 3 init 0 xor last 4 bits
// P = Pre-/Postamble
// ? = unknown meaning

	if(bit == RB42){												// decode S3318
		c = rowbuf[row][1]>>2 & 0x03;								// get channel

		if(c > 2)													// channel ok?
			goto resRow;											// no, reset row 
		
		if(datbuf[c][RBY-1] && datbuf[c][RBY-1]<3)					// channel active and currently updated? 
			goto resRow;											// yes, reset row

		rowbuf[row][RBY-1] <<= 4;									// ----XXPP -> XXPP0000
		i = 0;														// bit index

		do{																			// prepare data
			rowbuf[row][i] = rowbuf[row][i]<<1 | (rowbuf[row][i+1] & 0x80)!=0;		// shift
			rowbuf[row][i] = rowbuf[row][i]<<1 | (rowbuf[row][i+1] & 0x40)!=0;		
		}while(++i < RBY-1);														// ignore last byte

		if(datbuf[c][RBY-1] && datbuf[c][0]!=rowbuf[row][0])		// data in use and id mismatch?
			goto resRow;											// yes, reset row

		i = RBY - 1;												// ignore last byte

		do															// copy new data
			datbuf[c][--i] = rowbuf[row][i];
		while(i);

		datbuf[c][4] &= 0b11001111;									// sensor type 00 = S3318
		datbuf[c][RBY-1] = 1;										// reset receive time
	}

// ????IIII iiiiBWCC SSSTTTTT ttttHHHH ----hhhh			raw
// iiiiIIII iiiiBWCC SSSTTTTT ttttHHHH --01hhhh			prepared
//										 ^^				sensor type 01 = GJ1061
// ? unknown (brand?)
// I sensor ID
// B battery ?
// W tx-button
// C channel
// T temperature S=000		TTTTTtttt / 10
//               S=111		(512 - TTTTTtttt) / 10
// H humidity

	else{															// decode GJ1061
		if((rowbuf[row][0] & 0xf0) != 0x50)							// brand ok?
			goto resRow;											// no, reset row

		c = rowbuf[row][1] & 0x03;									// get channel
	
		if(c > 2)													// channel ok?
			goto resRow;											// no, reset row

		if(datbuf[c][RBY-1] && datbuf[c][RBY-1]<3)					// channel active and currently updated? 
			goto resRow;											// yes, reset row

		rowbuf[row][0] = rowbuf[row][0] & 0x0f | rowbuf[row][1] & 0xf0;		// ????IIII | iiiiBWCC -> iiiiIIII

		if(datbuf[c][RBY-1] && datbuf[c][0]!=rowbuf[row][0])		// data in use and id mismatch?		
			goto resRow;											// yes, reset row

		i = RBY - 1;												// ignore last byte

		do															// copy new data
			datbuf[c][--i] = rowbuf[row][i];
		while(i);

		datbuf[c][4] = datbuf[c][4] & 0b11001111 | 0b00010000;		// sensor type 01 = GJ1061
		datbuf[c][RBY-1] = 1;										// reset receive time
	}

	//i = ROWBUFS;													// devalue rowbufs

	//do
	//	rowbuf[--i][1] = 0xff;									
	//while(i);

	goto resRow;
}

uint8_t Wea::cmpRow(uint8_t a, uint8_t b)
{
	uint8_t i = RBY - 1;									// bytes to compare

	while(rowbuf[a][i]==rowbuf[b][i] && i)					// compare row bytes
		i--;

	return i==0;											// return true if ident rows
}

// -----------------------------------------------------------------------------

uint8_t Wea::getStatus(uint8_t c)
{
	uint8_t r = datbuf[c][RBY-1];							// receive time byte
	return r ? (r==RECTOT ? RECTO : (r==1 ? RECCU : RECOK)) : RECNO;					
}

void Wea::advanceRecTime()
{
	for(uint8_t c=0; c<DATBUFS; c++)						// all channels
		if(datbuf[c][RBY-1]>1 && datbuf[c][RBY-1]<RECTOT)	// reveice time started and no timeout?
			datbuf[c][RBY-1]++;								// receive time++

#if USE_AVERAGE
	if(avgCyc-- == 0){										// average cycle
		buildAvg();											//		   build 
		avgCyc = 60 - 1;									//				 every 60 s
	}
#endif
}

void Wea::startRecTime()
{
	for(uint8_t c=0; c<DATBUFS; c++)						// all channels
		if(datbuf[c][RBY-1] == 1)							// receive current?
			datbuf[c][RBY-1]++;								// receive time start
}

uint16_t Wea::getTemp(uint8_t c)
{
	uint16_t te = 0;
	uint8_t sensType = datbuf[c][4] & 0b00110000;
																//						 3120 76541098
	if(sensType == 0x00){										// S3318	iiiiIIII ??CCTTTT ttttTTTT hhhhHHHH WB^^XXXX PP
		uint16_t t = (datbuf[c][2] & 0x0f) << 8 | datbuf[c][2] & 0xf0 | datbuf[c][1] & 0x0f;	// 12 bit t
		// float temp_f = (temp_raw - 900) * 0.1;
		uint16_t t18 = t<1220 ? 1220-t : t-1220;				// t in 1/18      °C
		uint8_t t1 = t18 / 18;									//      1
		uint8_t tm = (t18 % 18) * 5;							//      frac 5/18 
		uint8_t t10 = tm / 9 + (tm % 9 >= 5 ? 1 : 0);			//           1/10     rounded				
		te = t1 << 8 | (t<1220 ? 0x80 : 0) | t10;				// 0lll llll s000 rrrr,	l left, r right of decimal point
	}															//							  sss87654 3210
	else if(sensType == 0x10){									// GJ1061	iiiiIIII iiiiBWCC SSSTTTTT ttttHHHH --^^hhhh	
		uint8_t sign = datbuf[c][2] & 0xe0;
		uint16_t t = (datbuf[c][2] & 0x1f) << 4 | datbuf[c][3] >> 4;	// 9 bit t
		if(sign) t = 512 - t;
		uint8_t t1 = t / 10;
		uint8_t t10 = t % 10;
		te = t1<<8 | (sign ? 0x80 : 0) | t10;					// 0lll llll s000 rrrr
	}

	return te;
}

uint8_t Wea::getHumi(uint8_t c)
{
	uint8_t h = 0;
	uint8_t sensType = datbuf[c][4] & 0b00110000;
																//									   32107654
	if(sensType == 0x00){										// S3318	iiiiIIII ??CCTTTT ttttTTTT hhhhHHHH WB^^XXXX PP
		h = datbuf[c][3];										// 8 bit
		SWAP(h);												// h<<4 | h>>4
	}															//										   7654		3210
	else if(sensType == 0x10){									// GJ1061	iiiiIIII iiiiBWCC SSSTTTTT ttttHHHH --^^hhhh
		h = datbuf[c][3]<<4 | datbuf[c][4]&0x0f;				// 8 bit
	}

	if(h > 99)													// range
		h = 99;

	return h;															
}

uint8_t Wea::getBat(uint8_t c)
{
	uint8_t bt = 0;
	uint8_t sensType = datbuf[c][4] & 0b00110000;

	if(sensType == 0x00)										// S3318	iiiiIIII ??CCTTTT ttttTTTT hhhhHHHH WB^^XXXX PP
		bt = (datbuf[c][4] & 0x40) >> 6;						
	else if(sensType == 0x10)									// GJ1061	iiiiIIII iiiiBWCC SSSTTTTT ttttHHHH --^^hhhh
		bt = (datbuf[c][1] & 0x08) >> 3;

	return bt;
}

uint8_t Wea::getTx(uint8_t c)
{
	uint8_t tx = 0;
	uint8_t sensType = datbuf[c][4] & 0b00110000;

	if(sensType == 0x00)										// S3318	iiiiIIII ??CCTTTT ttttTTTT hhhhHHHH WB^^XXXX PP
		tx = (datbuf[c][4] & 0x80) >> 7;
	else if(sensType == 0x10)									// GJ1061	iiiiIIII iiiiBWCC SSSTTTTT ttttHHHH --^^hhhh
		tx = (datbuf[c][1] & 0x04) >> 2;							

	return tx;	
}

void Wea::resetChan(uint8_t c)
{
	datbuf[c][RBY-1] = 0;										// reset channel

#if USE_AVERAGE
	sAvsT[c] = 0;
	sAvgT[c] = 0;

	fAvsT[c] = 0;
	fAvgT[c] = 0;

	sAvsH[c] = 0;
	sAvgH[c] = 0;

	fAvsH[c] = 0;
	fAvgH[c] = 0;
#endif
}

#if USE_AVERAGE
void Wea::buildAvg()
{
	for(uint8_t c=0; c<DATBUFS; c++){
		if(datbuf[c][RBY-1]){								// datbuf active?
			uint8_t sensType = datbuf[c][4] & 0b00110000;
			uint8_t t, h;
			
			if(sensType == 0x00){							// S3318	iiiiIIII ??CCTTTT ttttTTTT hhhhHHHH WB^^XXXX PP
				t = ((datbuf[c][2] & 0x0f) << 8 | datbuf[c][2] & 0xf0 | datbuf[c][1] & 0x0f ) / 18;
				h = datbuf[c][3];							
				SWAP(h);
			}
			else if(sensType == 0x10){						// GJ1061	iiiiIIII iiiiBWCC SSSTTTTT ttttHHHH --^^hhhh
				t = ((datbuf[c][2] & 0xe0 ? 0x00 : 0x0200) | (datbuf[c][2] & 0x1f) << 4 | datbuf[c][3] >> 4) / 10;
				h = datbuf[c][3] << 4 | datbuf[c][4] & 0x0f;
			}			

			if(sAvsT[c] == 0){								// init avg and avs
				sAvsT[c] = t << SAVCT;
				sAvgT[c] = t;

				fAvsT[c] = t << FAVCT;
				fAvgT[c] = t;
				
				sAvsH[c] = h << SAVCH;
				sAvgH[c] = h;

				fAvsH[c] = h << FAVCH;
				fAvgH[c] = h;
			}
			else{
				sAvsT[c] += t - sAvgT[c];					// avs += current - avg
				sAvgT[c] = sAvsT[c] >> SAVCT;				// avg = avs / avc
				
				fAvsT[c] += t - fAvgT[c];
				fAvgT[c] = fAvsT[c] >> FAVCT;
				
				sAvsH[c] += h - sAvgH[c];
				sAvgH[c] = sAvsH[c] >> SAVCH;
				
				fAvsH[c] += h - fAvgH[c];
				fAvgH[c] = fAvsH[c] >> FAVCH;
			}
		}
	}
}

uint16_t Wea::getTrend(uint8_t c)
{
	int8_t dt = fAvgT[c] - sAvgT[c];				// delta = fast - slow
	if(dt < -NUMTST) dt = -NUMTST;					// ± 1 2 3 4 5 °C
	else if(dt > NUMTST) dt = NUMTST;				

	int8_t dh = fAvgH[c] - sAvgH[c];				// delta = fast - slow
	if(dh < -NUMTST) dh = -NUMTST;					// ± 1 2 3 4 5 %
	else if(dh > NUMTST) dh = NUMTST;				

	return dh<<8 | dt&0xff;							// s000 0hhh s000 0ttt
}
#endif

// crc4 check does not work correctly
// Serial.printf("%02x %02x ", crc4(row), rowbuf[row][4] & 0x0f);
//
// #define CRCBYTES	4
// #define CRCPOLY   (3 << 4)
// #define CRCINIT   (0 << 4)
// 
// uint8_t Wea::crc4(uint8_t c)
// {
//	uint8_t r = CRCINIT;						
// 	uint8_t n = 0;
// 
//     do{
//         r ^= rowbuf[c][n];
// 
//         for(uint8_t b=0; b<8; b++){
//             if(r & 0x80)
//                 r = (r << 1) ^ CRCPOLY;
//             else
//                 r = r << 1;
//         }
//     }while(++n < CRCBYTES);
// 
//     return r>>4 ^ rowbuf[c][n]>>4;		
// }
//