#ifndef INTERFACE
#define INTERFACE

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

#include "display.h"

#include <Windows.h>
#include <conio.h>

// legthes of input values

#define ICAO_ADDRESS_SIZE 6
#define CODE_A_SIZE       4
#define CODE_VFR_SIZE     4
#define FLIGHT_NUM_SIZE   8

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
	FL = 0,
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
	char flightNumber[FLIGHT_NUM_SIZE + 1];
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

struct Configuration Con; // configuration of A / C
struct State Stat;       // state of A/C

// structure configuration functions

void initConfiguration(struct Configuration* Con);
void loadFromUART(struct Configuration* Con);

// structure status functions

void initStatus(struct State* state);

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

// input menus

uint8_t controlPanel(char data[], const uint8_t dataLength, const uint8_t base);
uint8_t chooseMode(uint8_t* mode, char** arrayModes, uint8_t arraySize);

// work with encoding word to code and reversed

void codeToWord(uint32_t code, char word[], const uint8_t wordLength, const uint8_t base);
uint32_t wordToCode(char word[], const uint8_t wordLength, const uint8_t base);

// convert received height to table by IFR

int16_t convertHeight(int16_t heightTarget, enum heightUnit unit);
uint8_t findClosest(int16_t arr[], uint8_t size, int16_t target);

#endif // INTERFACE