#ifndef INTERFACE
#define INTERFACE

#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <cmath>

// TODO after import to keil you have to change keys values
enum keys {
	SIGN,                                                    // (ZNAK)
	INPUT,                                                   // (VVOD)
	VFR,                                                     // visual flight rules (PVP)
	FNK = 27, FNK_hold10sec,                                 // functional button
	encoderLeft = 'a', encoderRight = 'd', encoderEnter = 13 // encoder
};

struct Configuration {
	uint32_t ICAO;
	uint16_t codeA;
	uint16_t codeVFR;

	void inputICAO();
	void inputCodeA();
	void inputCodeVFR();
};


void showInput(const uint8_t data[], const uint8_t dataLength, const uint8_t base); // It's on you, Andrew
uint8_t receiveKey();                                                               // It's for Pavel
void controlPanel(uint8_t data[], const uint8_t dataLength, const uint8_t base);

void codeToWord(uint32_t code, uint8_t word[], const uint8_t wordLength, const uint8_t base);
uint32_t wordToCode(uint8_t word[], const uint8_t wordLength, const uint8_t base);

#endif // INTERFACE