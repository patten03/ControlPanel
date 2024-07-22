#ifndef INTERFACE
#define INTERFACE

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

#include <Windows.h>
#include <conio.h>

extern const char baseAndLetters[];

enum keys {
	// Toggle of modes
	Off,
	SBY,
	GND,
	On,
	Alt,

	// Other
	Sign,       
	Input = 's',
	VFR,                                                      // visual flight rules (PVP)
	FNK = 'a', FNK_hold10sec = 'q',                           // functional button
	encoderLeft = 'd', encoderRight = 'f', encoderEnter = ' ' // encoder
};

enum displayRow {
	top = 0,
	middle = 2,
	bottom = 4
};

enum displayColumn {
	left = 0,
	right = 10
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
struct ACCategory {        // A/C - aircraft
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

// Height of A/C
extern const char* heightUnitsArray[];
extern const uint8_t heightUnitsArraySize;
enum heightUnit {
	foot = 0,
	meter = 1
};

// current state of A/C
struct State {
	uint8_t switchMode;
	uint32_t height;
	uint8_t assistField;

	float longitude;
	float latitude;
};

// configuration of A/C
struct Configuration {
	uint32_t ICAO;
	uint16_t codeA;
	uint16_t codeVFR;
	char flightNumber[9];
	uint8_t velocityCategory;
	struct ACCategory ACCat;
	uint8_t sensorAS;           // sensor air-surface
	uint8_t SIL;                // safety integrity level

	uint8_t heightUnit;

	// aircraft size
	uint16_t length;
	uint16_t width;
};

// global structures

struct Configuration con; // configuration of A / C
struct State state;       // state of A/C

// structure configuration functions

void initConfiguration(struct Configuration* con);
void loadFromUART(struct Configuration* con);

// structure status functions

void initStatus(struct Status* status);

// structure functions configuration, submenus to input data

void inputICAO(uint32_t* ICAO);
void inputCodeA(uint16_t* codeA);
void inputCodeVFR(uint16_t* codeVFR);
void inputFlightNumber(char flightNumber[], uint8_t numLength);
// void inputVelocityCategory();
void inputACCategory(struct ACCategory* ACCat);
void inputSensorAS(uint8_t* sensorMode);
void inputSIL(uint8_t* SIL_value);
void inputSize(uint16_t* length, uint16_t* width);
void changeHeightInits(uint8_t* heightUnit);

uint8_t quitConfiguration();

// main loop of program

void mainMenu();
void configurationMenu();
void coordMenu();

// display work

void putStrDirectly(uint8_t y, char str[], uint8_t strSize);
void putStrValue(uint8_t y, char str[], uint8_t strSize, uint8_t chosenSymbol);
void putStrMode(uint8_t y, char str[], uint8_t strSize);
void putStrInField(uint8_t x, uint8_t y, char str[], uint8_t strSize);
void cleanScreen();
void cleanRow(uint8_t y);
void cleanField(uint8_t x, uint8_t y);

// function that gives pressed key code

uint8_t receiveKey();

// input menus

uint8_t controlPanel(char data[], const uint8_t dataLength, const uint8_t base);
uint8_t chooseMode(uint8_t* mode, char** arrayModes, uint8_t arraySize);

// work with encoding word to code and reversed

void codeToWord(uint32_t code, char word[], const uint8_t wordLength, const uint8_t base);
uint32_t wordToCode(char word[], const uint8_t wordLength, const uint8_t base);

#endif // INTERFACE