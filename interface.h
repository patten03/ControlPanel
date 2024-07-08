#ifndef INTERFACE
#define INTERFACE

#include <stdio.h>
#include <iostream>
#include <conio.h>

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

	void inputICAO();
};


void showInput(const uint8_t data[], const uint8_t dataLength, const uint8_t base);
uint8_t receiveKey();
void controlPanel(uint8_t data[], const uint8_t dataLength, const uint8_t base);

#endif // INTERFACE