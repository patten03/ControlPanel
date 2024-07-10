#ifndef INTERFACE
#define INTERFACE

#include <stdio.h>
#include <iostream>
#include <conio.h>
#include <cmath>

// TODO after import to keil you have to change keys values
enum keys {
	// Toggle of modes
	Off,
	SBY,
	GND,
	On = 'q',
	Alt,

	// Other
	SIGN,                                                     // (ZNAK)
	INPUT = 's',                                              // (VVOD)
	VFR,                                                      // visual flight rules (PVP)
	FNK = 'a', FNK_hold10sec,                                 // functional button
	encoderLeft = 'd', encoderRight = 'f', encoderEnter = ' ' // encoder
};

struct ACCategory { // A/C - aircraft
	uint8_t setA;
	uint8_t setB;
	uint8_t setC;
};

struct Configuration {
	uint32_t ICAO;
	uint16_t codeA;
	uint16_t codeVFR;
	char flightNumber[8];
	uint8_t velocityCategory;
	ACCategory ACCat;

	// sensor surface/air
	// SIL

	// aircraft size
	uint16_t length;
	uint16_t width;

	void init();
	void loadFromUART();

	void inputICAO();
	void inputCodeA();
	void inputCodeVFR();
	// void inputFlightNumber();
	// void inputVelocityCategory();
	void inputACCategory();
	// sensor surface/air
	// SIL
	void inputSize();
};

void mainMenu();

void showInput(const uint8_t data[], const uint8_t dataLength, const uint8_t base); // It's on you, Andrew
uint8_t receiveKey();                                                               // It's for Pavel
uint8_t controlPanel(uint8_t data[], const uint8_t dataLength, const uint8_t base);

void codeToWord(uint32_t code, uint8_t word[], const uint8_t wordLength, const uint8_t base);
uint32_t wordToCode(uint8_t word[], const uint8_t wordLength, const uint8_t base);

#endif // INTERFACE