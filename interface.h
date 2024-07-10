#ifndef INTERFACE
#define INTERFACE

#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

#include <Windows.h>

extern const char base16[];

// TODO after import to keil you have to change keys values
enum keys {
	// Toggle of modes
	Off,
	SBY,
	GND,
	On = 'q',
	Alt,

	// Other
	Sign,                                                     // (ZNAK)
	Input = 's',                                              // (VVOD)
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
	char flightNumber[9];
	uint8_t velocityCategory;
	struct ACCategory ACCat;

	// sensor surface/air
	// SIL

	// aircraft size
	uint16_t length;
	uint16_t width;
};

// structure functions
void init(struct Configuration* con);
void loadFromUART(struct Configuration* con);

void inputICAO(uint32_t* ICAO);
void inputCodeA(uint16_t* codeA);
void inputCodeVFR(uint16_t* codeVFR);
// void inputFlightNumber();
// void inputVelocityCategory();
// void inputACCategory(struct ACCategory* ACCat);
// sensor surface/air
// SIL
void inputSize(uint16_t* length, uint16_t* width);


void mainMenu();

void putStrDirectly(uint8_t y, char str[], uint8_t strSize);
uint8_t receiveKey();
uint8_t controlPanel(uint8_t data[], const uint8_t dataLength, const uint8_t base);

void codeToWord(uint32_t code, char word[], const uint8_t wordLength, const uint8_t base);
uint32_t wordToCode(char word[], const uint8_t wordLength, const uint8_t base);

#endif // INTERFACE