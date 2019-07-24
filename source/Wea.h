#pragma once

#include <Arduino.h>

#define RX_LOGIC        1						// RX logic, 0 negative, 1 positive
#define RX_PIN			2						// 2, PB2, INT2

#define USE_AVERAGE		1						// 0 do not use, 1 use average

#define SAVCT			6						// average constant slow temperature	(2^6 = 64 minutes)
#define SAVCH			6						//					     humidity
#define FAVCT			2						//					fast temperature	(2^2 = 4 minutes)
#define FAVCH			2						//						 humidity		

#define FOSC		    16L                     // fosc in MHz
#define FDIV			8L						// div timer

// device	S3318		GJ1061		GT-WT-02
// low 		2000		1800		2500
// high		4000		3800		5000
// row		8000		9100		8000
// reset	9400	   10000	   12000
// bits		  42		  36		  37 
	
#define PPMMIN		   (500L*FOSC/FDIV)			// t in ms * 1000 * FOSC / FDIV
#define PPMLOW		   (2500L*FOSC/FDIV)							
#define PPMHIG		   (4500L*FOSC/FDIV)		
#define PPMROW		   (10500L*FOSC/FDIV)					

#define RB36			36						// GJ1061-00B, (TFA-Twin-Plus-30.3049), (Conrad KW9010), (Ea2 BL999)
#define RB37			37						// (GT-WT-02)
#define RB42			42						// Conrad S3318
#define RBI				RB42
#define RBY			   (RBI / 8 + 1)

#define ROWBUFS			6
#define ROWIDENT		2
#define DATBUFS			3

//#define RECTOT		255						// receive timeout time, 4.25 minutes
#define RECTOT			90						//						 90 s

#define RECNO			0						// receive not initialized
#define RECCU			1						// receive currently			
#define RECOK			2						// receive OK
#define RECTO			3						// receive timeout

class Wea
{
public:
	Wea();
	~Wea();

	static void init();
	static uint8_t getStatus(uint8_t);
	static uint16_t getTemp(uint8_t);
	static uint8_t getHumi(uint8_t);
	static uint8_t getBat(uint8_t);
	static uint8_t getTx(uint8_t);
	static void resetChan(uint8_t);
	static void advanceRecTime();
	static void startRecTime();

	static void RX();
	static void bitStart();
	static void bitEnd();

private:
	static uint8_t cmpRow(uint8_t, uint8_t);
	//static uint8_t crc4(uint8_t);

	static uint8_t rowbuf[ROWBUFS][RBY];
	static uint8_t datbuf[DATBUFS][RBY]; 
	static uint8_t row, bit;

#if USE_AVERAGE
#define NUMTST	5								// number of threshold steps

public:
	static uint16_t getTrend(uint8_t);

private:
	static void buildAvg();

	static uint8_t avgCyc;
	static uint16_t sAvsT[DATBUFS];
	static uint8_t sAvgT[DATBUFS];
	static uint16_t fAvsT[DATBUFS];
	static uint8_t fAvgT[DATBUFS];
	static uint16_t sAvsH[DATBUFS];
	static uint8_t sAvgH[DATBUFS];
	static uint16_t fAvsH[DATBUFS];
	static uint8_t fAvgH[DATBUFS];
#endif
};

// analog comperator calculation (unused)
//
// U = 3.7 V (RX signal max), U2 = 1.1 V (bandgap), R1 U<->AIN1, R2 AIN1<->GND
// R1 = R2 * (U * f - U2) / U2, f = (R1 + R2) * U2 / (R2 * U)
