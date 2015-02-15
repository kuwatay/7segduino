/*
  SSeg.cpp - Arduino library for 7seg 4digit/8digit LED matrix.
  Copyright 2011 morecat_lab
 
  base on Dots library.
  Copyright 2010 arms22. All right reserved.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
*/

#ifndef SSEG_H
#define SSEG_H

#include <inttypes.h>
#include <avr/pgmspace.h>


#define NUM_PAT_0 0b11111100
#define NUM_PAT_1 0b01100000
#define NUM_PAT_2 0b11011010
#define NUM_PAT_3 0b11110010
#define NUM_PAT_4 0b01100110
#define NUM_PAT_5 0b10110110
#define NUM_PAT_6 0b10111110
#define NUM_PAT_7 0b11100000
#define NUM_PAT_8 0b11111110
#define NUM_PAT_9 0b11110110
#define NUM_PAT_A 0b11101110
#define NUM_PAT_B 0b00111110
#define NUM_PAT_C 0b10011100
#define NUM_PAT_D 0b01111010
#define NUM_PAT_E 0b10011110
#define NUM_PAT_F 0b10001110

class Sseg
{
private:
	unsigned long _lastUpdateTime;
	uint16_t _updateInterval;
	uint8_t _segPins[8];
	uint8_t _digPins[8];
	uint8_t _buffer[8];
	uint8_t _numOfDigs;
	uint8_t _dig;       // support 4 or 8
	uint8_t _zeroSupress;
	uint8_t _kcommon;  // Cathode-common flag
	void initConv(void);
public:
	static const uint8_t numConv[16];
	// 2 digit
	Sseg(uint8_t a,uint8_t b,uint8_t c,uint8_t d,
		 uint8_t e,uint8_t f,uint8_t g,uint8_t dp,
		 uint8_t d1,uint8_t d2);
	// 4 digit
	Sseg(uint8_t a,uint8_t b,uint8_t c,uint8_t d,
		 uint8_t e,uint8_t f,uint8_t g,uint8_t dp,
		 uint8_t d1,uint8_t d2,uint8_t d3,uint8_t d4);
	// 8 digit
	Sseg(uint8_t a,uint8_t b,uint8_t c,uint8_t d,
		 uint8_t e,uint8_t f,uint8_t g,uint8_t dp,
		 uint8_t d1,uint8_t d2,uint8_t d3,uint8_t d4,
		 uint8_t d5,uint8_t d6,uint8_t d7,uint8_t d8);
	
	void begin(void);
	void setKcommon(void);
	void setAcommon(void);
	uint8_t segCh(uint8_t i);
	void setDot(uint8_t d);
	void clearDot(uint8_t d);
	void writeNum(int n);
	void writeNum(long n);
	void writeNum2(int n);
	void writeNum4(int n);
	void writeNum8(long l);
	void writeNum(uint8_t d1, uint8_t d2);
	void writeNum(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4);
	void writeNum(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4,uint8_t d5, uint8_t d6, uint8_t d7, uint8_t d8);
	void supressZero();
	void setZeroSupress(uint8_t t);
	void writeHex(int n);
	void writeHex(long n);
	void writeRawData(uint8_t d1, uint8_t d2);
	void writeRawData(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4);
	void writeRawData(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4,uint8_t d5, uint8_t d6, uint8_t d7, uint8_t d8);
	void write(uint8_t x, uint8_t y, uint8_t value);
	void write(uint8_t y, uint8_t value);
	void write(uint8_t y, const uint8_t values[], uint8_t size);
	void clear(void);
	void turnOff(void);
	void turnOn(void);
	void updateSeg(void);
	bool update(void);
	void updateWithDelay(unsigned long ms);
	void updateOnce(void);
};

#endif	// SSEG.h
