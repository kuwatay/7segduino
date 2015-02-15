/*
  SSeg.cpp - Arduino library for 7seg 4digit/8digit LED matrix.
  Copyright 2011 morecat_lab
 
  base on Dots library.
  Copyright 2010 arms22. All right reserved.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
*/

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WConstants.h>
#endif
#include <pins_arduino.h>
#include "Sseg.h"

const uint8_t Sseg::numConv[] = {
	NUM_PAT_0, NUM_PAT_1, NUM_PAT_2, NUM_PAT_3,
	NUM_PAT_4, NUM_PAT_5, NUM_PAT_6, NUM_PAT_7,
	NUM_PAT_8, NUM_PAT_9, NUM_PAT_A, NUM_PAT_B,
	NUM_PAT_C, NUM_PAT_D, NUM_PAT_E, NUM_PAT_F};

// 2 digit
Sseg::Sseg(uint8_t a,uint8_t b,uint8_t c,uint8_t d,
		   uint8_t e,uint8_t f,uint8_t g,uint8_t dp,
		   uint8_t d1,uint8_t d2)
{
	_segPins[0] = a; _segPins[1] = b; _segPins[2] = c; _segPins[3] = d;
	_segPins[4] = e; _segPins[5] = f; _segPins[6] = g; _segPins[7] = dp;
	
	_digPins[0] = d1; _digPins[1] = d2;
	
	_numOfDigs = 2;
	_updateInterval = (8333 / 2);
	_zeroSupress = 1;
	_kcommon = 0;
}

// 4 digit
Sseg::Sseg(uint8_t a,uint8_t b,uint8_t c,uint8_t d,
		   uint8_t e,uint8_t f,uint8_t g,uint8_t dp,
		   uint8_t d1,uint8_t d2,uint8_t d3,uint8_t d4)
{
	_segPins[0] = a; _segPins[1] = b; _segPins[2] = c; _segPins[3] = d;
	_segPins[4] = e; _segPins[5] = f; _segPins[6] = g; _segPins[7] = dp;
	
	_digPins[0] = d1; _digPins[1] = d2; _digPins[2] = d3; _digPins[3] = d4;
	
	_numOfDigs = 4;
	_updateInterval = (8333 / 4);
	_zeroSupress = 1;
	_kcommon = 0;
}

// 8 digit
Sseg::Sseg(uint8_t a,uint8_t b,uint8_t c,uint8_t d,
		   uint8_t e,uint8_t f,uint8_t g,uint8_t dp,
		   uint8_t d1,uint8_t d2,uint8_t d3,uint8_t d4,
		   uint8_t d5,uint8_t d6,uint8_t d7,uint8_t d8)
{
	_segPins[0] = a; _segPins[1] = b; _segPins[2] = c; _segPins[3] = d;
	_segPins[4] = e; _segPins[5] = f; _segPins[6] = g; _segPins[7] = dp;
	
	_digPins[0] = d1; _digPins[1] = d2; _digPins[2] = d3; _digPins[3] = d4;
	_digPins[4] = d5; _digPins[5] = d6; _digPins[6] = d7; _digPins[7] = d8;
	
	_numOfDigs = 8;
	_updateInterval = (8333 / 8);
	_zeroSupress = 1;
	_kcommon = 0;
}

void Sseg::begin(void) {
	uint8_t i;
	for(i=0;i<8;i++){
		pinMode(_segPins[i], OUTPUT);
	}
	for(i=0;i<_numOfDigs;i++){
		pinMode(_digPins[i], OUTPUT);
	}
	clear();
}

void Sseg::setAcommon(void) {
	_kcommon = 0;
}

void Sseg::setKcommon(void) {
	_kcommon = 1;
}

uint8_t Sseg::segCh(uint8_t i) {
	return Sseg::numConv[i];
}

void Sseg::setDot(uint8_t d) {
	_buffer[d] |= 0x01;
}

void Sseg::clearDot(uint8_t d) {
	_buffer[d] &= 0xfe;
}

void Sseg::writeNum(int n) {
	if (_numOfDigs == 2) {
		writeNum2(n);
	} else if (_numOfDigs == 4) {
		writeNum4(n);
	} else if (_numOfDigs == 8) {
		writeNum8((long)n);
	}
}

void Sseg::writeNum(long n) {
	if (_numOfDigs == 2) {
		writeNum8((int)n);
	} else if (_numOfDigs == 4) {
		writeNum4((int)n);
	} else if (_numOfDigs == 8) {
		writeNum8(n);
	}
}


void Sseg::writeNum2(int n) {
	if (n < 100) {
		_buffer[0] = segCh((n % 100) / 10);
		_buffer[1] = segCh(n % 10);
		Sseg::supressZero();
	} else {
		_buffer[0] = _buffer[1] = 0b00000010;// overflow
	}
}

void Sseg::writeNum4(int n) {
	if (n < 10000) {
		_buffer[0] = segCh((n % 10000) / 1000);
		_buffer[1] = segCh((n % 1000) / 100);
		_buffer[2] = segCh((n % 100) / 10);
		_buffer[3] = segCh(n % 10);
		Sseg::supressZero();
	} else {
		_buffer[0] = _buffer[1] = _buffer[2] = _buffer[3] = 0b00000010;// overflow
	}
}

void Sseg::writeNum8(long n) {
	_buffer[0] = segCh((n % 100000000) / 10000000);
	_buffer[1] = segCh((n % 10000000) / 1000000);
	_buffer[2] = segCh((n % 1000000) / 100000);
	_buffer[3] = segCh((n % 100000) / 10000);
	_buffer[4] = segCh((n % 10000) / 1000);
	_buffer[5] = segCh((n % 1000) / 100);
	_buffer[6] = segCh((n % 100) / 10);
	_buffer[7] = segCh(n % 10);
	Sseg::supressZero();
}

void Sseg::writeNum(uint8_t d1, uint8_t d2) {
	_buffer[0] = segCh(d1);
	_buffer[1] = segCh(d2);
	Sseg::supressZero();
}

void Sseg::writeNum(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4) {
	_buffer[0] = segCh(d1);
	_buffer[1] = segCh(d2);
	_buffer[2] = segCh(d3);
	_buffer[3] = segCh(d4);
	Sseg::supressZero();
}

void Sseg::writeNum(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4,
					uint8_t d5, uint8_t d6, uint8_t d7, uint8_t d8)
{
	_buffer[0] = segCh(d1);
	_buffer[1] = segCh(d2);
	_buffer[2] = segCh(d3);
	_buffer[3] = segCh(d4);
	_buffer[4] = segCh(d5);
	_buffer[5] = segCh(d6);
	_buffer[6] = segCh(d7);
	_buffer[7] = segCh(d8);
	Sseg::supressZero();
}

void Sseg::writeHex(int n) {
	if(_numOfDigs == 2) {
		_buffer[0] = segCh((n >> 4) & 0xf);
		_buffer[1] = segCh(n & 0xf);
	} else if (_numOfDigs == 4) {
		_buffer[0] = segCh((n >> 12) & 0xf);
		_buffer[1] = segCh((n >> 8) & 0xf);
		_buffer[2] = segCh((n >> 4) & 0xf);
		_buffer[3] = segCh(n & 0xf);
	}
	Sseg::supressZero();
}

void Sseg::writeHex(long n) {
	_buffer[0] = segCh((n >> 28) & 0xf);
	_buffer[1] = segCh((n >> 24) & 0xf);
	_buffer[2] = segCh((n >> 20) & 0xf);
	_buffer[3] = segCh((n >> 16) & 0xf);
	_buffer[4] = segCh((n >> 12) & 0xf);
	_buffer[5] = segCh((n >> 8) & 0xf);
	_buffer[6] = segCh((n >> 4) & 0xf);
	_buffer[7] = segCh(n & 0xf);
	Sseg::supressZero();
}

void Sseg::setZeroSupress(uint8_t t) {
	_zeroSupress = t;
}

void Sseg::supressZero() {
	uint8_t i;
	if (_zeroSupress == 1) {
		for (i = 0 ; i < (_numOfDigs-1) ; i++) {
			if (_buffer[i] == segCh(0)) {
				_buffer[i] = _buffer[i] & 0x1;
			} else {
				break;
			}
		}
	}
}

void Sseg::writeRawData(uint8_t d1, uint8_t d2) {
	_buffer[0] = d1;
	_buffer[1] = d2;
}

void Sseg::writeRawData(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4) {
	_buffer[0] = d1;
	_buffer[1] = d2;
	_buffer[2] = d3;
	_buffer[3] = d4;
}

void Sseg::writeRawData(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4,
						uint8_t d5, uint8_t d6, uint8_t d7, uint8_t d8)
{
	_buffer[0] = d1;
	_buffer[1] = d2;
	_buffer[2] = d3;
	_buffer[3] = d4;
	_buffer[4] = d5;
	_buffer[5] = d6;
	_buffer[6] = d7;
	_buffer[7] = d8;
}

void Sseg::write(uint8_t x, uint8_t y, uint8_t value) {
	uint8_t tmp,msk;
	tmp = _buffer[y];
	msk = 0x80 >> x;
	tmp = tmp & ~msk;
	tmp = tmp | (value ? msk : 0);
	_buffer[y] = tmp;
}

void Sseg::write(uint8_t y, uint8_t value) {
	_buffer[y] = value;
}

void Sseg::write(uint8_t y, const uint8_t values[], uint8_t size) {
	uint8_t i;
	for(i=0;i<size;i++)
		_buffer[(y++) & 0x07] = values[i];
}

void Sseg::clear(void) {
	uint8_t i;
	for(i=0;i<8;i++){
		_buffer[i] = 0;
	}
	_dig = _numOfDigs - 1;
}

void Sseg::turnOff(void) {
	digitalWrite(_digPins[_dig], (_kcommon == 0) ? LOW: HIGH);
}

void Sseg::turnOn(void) {
	digitalWrite(_digPins[_dig], (_kcommon == 0) ? HIGH: LOW);
}

void Sseg::updateSeg(void) {
	uint8_t i,data,mask;
	_dig++;
	if(_dig >= _numOfDigs){
		_dig = 0;
	}
	data = _buffer[_dig];
	mask = 0x80;
	for(i=0;i<8;i++){
		if(data & mask){
			digitalWrite(_segPins[i], (_kcommon == 0) ? LOW : HIGH);
		}else{
			digitalWrite(_segPins[i], (_kcommon == 0) ? HIGH : LOW);
		}
		mask >>= 1;
	}
}

bool Sseg::update(void) {
	unsigned long t = micros();
	bool sync = false;
	if((t - _lastUpdateTime) > _updateInterval){
		turnOff();
		updateSeg();
		turnOn();
		_lastUpdateTime = t;
//		sync = (_dig == (_numOfDigs-1));
		sync = (_dig == 0);
	}
	return sync;
}

void Sseg::updateWithDelay(unsigned long ms) {
	unsigned long start = millis();
	do {
		bool sync = update();
		if(sync){
			unsigned long t = millis();
			if((t - start) >= ms){
				break;
			}
		}
	} while(1);
}

void Sseg::updateOnce(void) {
	uint8_t i;
	_dig = _numOfDigs - 1;
	turnOff();
	for (i = 0 ; i < _numOfDigs ; i++) {
		updateSeg();
		turnOn();
//		delay(_updateInterval);
		delay(1);
		turnOff();
	}
}

// EOF
