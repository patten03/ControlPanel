#ifndef INTERFACE
#define INTERFACE

#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

#include <Windows.h>

extern const char baseAndLetters[];

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

enum displayRow {
	top = 0,
	middle = 2,
	bottom = 4
};


// Sensor air-surface
extern const char* sensorModesArray[];
extern const uint8_t sizeSensorArray;
enum sensorAS_Mode { // A/S - air-surface
	sensorOn = 0,
	manualMode = 1,
	sensorOff = 2
};


// SIL - Safety Integrity Level
extern const char* SIL_Array[];
extern const uint8_t sizeSIL_Array;
enum SIL_Level {
	low = 0,
	medium = 1,
	high = 2
};

// A/C category
struct ACCategory { // A/C - aircraft
	uint8_t set;           // set can be A, B and C (D reserved)
	uint8_t category;
};
extern const char* ACCategoryArray[];
extern const uint8_t ACCategoryArraySize;
enum ACSet {
	A = 0,
	B = 1,
	C = 2
};

// configuration of A/C
struct Configuration {
	uint32_t ICAO;
	uint16_t codeA;
	uint16_t codeVFR;
	char flightNumber[9];
	uint8_t velocityCategory;
	struct ACCategory ACCat;
	uint8_t sensorAS;
	uint8_t SIL;

	// aircraft size
	uint16_t length;
	uint16_t width;
};

// structure functions
void init(struct Configuration* con);
void loadFromUART(struct Configuration* con);

// structure functions, submenus to input data
void inputICAO(uint32_t* ICAO);
void inputCodeA(uint16_t* codeA);
void inputCodeVFR(uint16_t* codeVFR);
void inputFlightNumber(char flightNumber[], uint8_t numLength);
// void inputVelocityCategory();
void inputACCategory(struct ACCategory* ACCat);
void inputSensorAS(uint8_t* sensorMode);
void inputSIL(uint8_t* SIL_value);
void inputSize(uint16_t* length, uint16_t* width);


void mainMenu();

// display work
void putStrDirectly(uint8_t y, char str[], uint8_t strSize);
void putStrValue(uint8_t y, char str[], uint8_t strSize, uint8_t chosenSymbol);
void putStrMode(uint8_t y, char str[], uint8_t strSize);
void cleanScreen();
void cleanRow(uint8_t y);


uint8_t receiveKey();
uint8_t controlPanel(uint8_t data[], const uint8_t dataLength, const uint8_t base);
uint8_t chooseMode(uint8_t* mode, char** arrayModes, uint8_t arraySize);

void codeToWord(uint32_t code, char word[], const uint8_t wordLength, const uint8_t base);
uint32_t wordToCode(char word[], const uint8_t wordLength, const uint8_t base);

#endif // INTERFACE