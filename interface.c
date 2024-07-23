#include "interface.h"

// In order to input octal, demical and hexademical bases and letters (including space)
extern const char baseAndLetters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

// Sensor air/surface
extern const char* sensorModesArray[] = { "Yes", "Manual mode", "No" };
extern const uint8_t sizeSensorArray = 3;

// SIL
extern const char* SIL_Array[] = { "Low", "Medium", "High" };
extern const uint8_t sizeSIL_Array = 3;

// ACCategory
extern const char* ACCategoryArray[] = { "A", "B", "C" };
extern const uint8_t ACCategoryArraySize = 3;

// A/C height
extern const char* heightUnitsArray[] = { "Feet", "Meters" };
extern const uint8_t heightUnitsArraySize = 2;

//@brief set all fields of structure to zeros, spaces and standarts values
//@param[out] Con - structure that we inintialize
void initConfiguration(struct Configuration* Con) {
	Con->ICAO = 0;
	Con->codeA = 0;
	Con->codeVFR = 0;

	// fill all letters to space
	memset(Con->flightNumber, ' ', sizeof(Con->flightNumber));
	Con->flightNumber[sizeof(Con->flightNumber) - 1] = '\0';

	Con->velocityCategory = 0;

	Con->ACCat.set = A;
	Con->ACCat.category = 0;

	Con->sensorAS = sensorOff;
	Con->SIL = low;

	Con->heightUnit = meter;

	Con->length = 0;
	Con->width = 0;
}

//@brief set all field of structure to zeros
//@param[out] stat - structure that we inintialize
void initState(struct State* stat) {
	stat->switchMode = 0;
	stat->assistField = 0;
	stat->height = 0;
	stat->longitude = 0.f;
	stat->latitude = 0.f;
}

//@brief submenu to input ICAO address
//@param[out] ICAO - address ICAO in hexademical format
void inputICAO(uint32_t* ICAO) {
	char address[ICAO_ADDRESS_SIZE + 1];   // ICAO address as array of digits
	uint8_t base = 16;                     // hexademical base

	codeToWord(*ICAO, address, sizeof(address), base);

	// input some title onto display
	putStrDirectly(top, "ICAO address", sizeof("ICAO address"));
	putStrValue(middle, address, sizeof(address), -1);
	putStrDirectly(bottom, "Configuration", sizeof("Configuration"));

	uint8_t save = controlPanel(address, sizeof(address), base);

	if (save == Input) {
		*ICAO = wordToCode(address, sizeof(address), base);
	}

	cleanScreen();
}

//@brief submenu to input code A
//@param[out] codeA - code A in octal format
void inputCodeA(uint16_t* codeA) {
	char code[CODE_A_SIZE + 1];  // code A array as array of digits
	uint8_t base = 8;            // octal base

	codeToWord(*codeA, code, sizeof(code), base);

	// input some title onto display
	putStrDirectly(top, "Code A", sizeof("Code A"));
	putStrValue(middle, code, sizeof(code), -1);
	putStrDirectly(bottom, "Configuration", sizeof("Configuration"));

	uint8_t save = controlPanel(code, sizeof(code), base);

	if (save == Input) {
		*codeA = wordToCode(code, sizeof(code), base);
	}

	cleanScreen();
}

//@brief submenu to input code for visual flight rule
//@param[out] codeVFR - code of VFR in octal format
void inputCodeVFR(uint16_t* codeVFR) {
	char code[CODE_VFR_SIZE + 1];   // code VFR array of digits
	uint8_t base = 8;               // octal base

	codeToWord(*codeVFR, code, sizeof(code), base);

	// input some title onto display
	putStrDirectly(top, "Code VFP", sizeof("Code VFP"));
	putStrValue(middle, code, sizeof(code), -1);
	putStrDirectly(bottom, "Configuration", sizeof("Configuration"));

	uint8_t save = controlPanel(code, sizeof(code), base);

	if (save == Input) {
		*codeVFR = wordToCode(code, sizeof(code), base);
	}

	cleanScreen();
}

//@brief submenu to input flight number
//@param[out] flightNumber[] - string with flight number, including '\0'
//@param[in] numLength - size of flightNumber string, includeing '\0'
void inputFlightNumber(char flightNumber[], uint8_t numLength) {
	char tempFlightNumber[FLIGHT_NUM_SIZE + 1]; // flight number 
	uint8_t base = 37;                          // include all digits, letter and space

	strcpy_s(tempFlightNumber, sizeof(tempFlightNumber), flightNumber);

	// input some title onto display (Andrew)
	putStrDirectly(top, "Flight number", sizeof("Flight number"));
	putStrValue(middle, tempFlightNumber, sizeof(tempFlightNumber), -1);
	putStrDirectly(bottom, "Configuration", sizeof("Configuration"));

	uint8_t lastKey = controlPanel(tempFlightNumber, sizeof(tempFlightNumber), base);

	if (lastKey == Input) {
		strcpy_s(flightNumber, numLength, tempFlightNumber);
	}

	cleanScreen();
}

//@brief submenu to input aircraft category
//@param[out] ACCat - structure that include set (A, B, C) and number (0-7)
void inputACCategory(struct ACCategory* ACCat) {
	uint8_t tempSetIndex = ACCat->set;                     // set of categories for A/C
	char tempCategory[] = { ACCat->category + '0', '\0' }; // category of A/C
	uint8_t base = 8;                                      // octal base

	char middleTitle[sizeof("Set _ Cat. *")];
	strcpy_s(middleTitle, sizeof(middleTitle), "Set ");
	strcat_s(middleTitle, sizeof(middleTitle), ACCategoryArray[ACCat->set]);
	strcat_s(middleTitle, sizeof(middleTitle), " Cat. ");
	strcat_s(middleTitle, sizeof(middleTitle), tempCategory);

	// input some title onto display
	putStrDirectly(top, "Category A/C", sizeof("Category A/C") + 1);
	putStrDirectly(middle, middleTitle, sizeof(middleTitle));
	putStrDirectly(bottom, "Configuration", sizeof("Configuration") + 1);

	uint8_t lastKey = chooseMode(&tempSetIndex, ACCategoryArray, ACCategoryArraySize);
	if (lastKey == Input) {
		putStrDirectly(middle, tempCategory, sizeof(tempCategory));
		controlPanel(&tempCategory, sizeof(tempCategory), base);

		ACCat->category = tempCategory[0] - '0'; // convert char to int
		ACCat->set = tempSetIndex;

	}
	cleanScreen();
}

//@brief submenu to input sensor air-surface mode
//@param[out] sensorMode - index of current mode of sensor, indexes declared in enum sensorAS_Mode
// and array of values declared in sensorModesArray[]
void inputSensorAS(uint8_t* sensorMode) {
	uint8_t tempSensorMode = *sensorMode;  // Mode of air-surface sensor

	// input some title onto display
	putStrDirectly(top, "Sensor A-S", sizeof("Sensor A-S"));
	putStrDirectly(middle, sensorModesArray[tempSensorMode], strlen(sensorModesArray[tempSensorMode]) + 1);
	putStrDirectly(bottom, "Configuration", sizeof("Configuration"));


	uint8_t lastKey = chooseMode(&tempSensorMode, sensorModesArray, sizeSensorArray);

	if (lastKey == Input) {
		*sensorMode = tempSensorMode;
	}
	cleanScreen();
}

//@brief submenu to input safety integrity level
//@param[out] SIL_value - index of current level, indexes declared in enum SIL_Level
// and array of level declared in SIL_Array[]
void inputSIL(uint8_t* SIL_value) {
	uint8_t tempSIL_value = *SIL_value; // - Security Integrity Level

	// input some title onto display
	putStrDirectly(top, "SIL", sizeof("SIL"));
	putStrDirectly(middle, SIL_Array[tempSIL_value], strlen(SIL_Array[tempSIL_value]) + 1);
	putStrDirectly(bottom, "Configuration", sizeof("Configuration"));

	uint8_t lastKey = chooseMode(&tempSIL_value, SIL_Array, sizeSIL_Array);

	if (lastKey == Input) {
		*SIL_value = tempSIL_value;
	}
	cleanScreen();
}

//@brief submenu to input size of aircraft
//@param[out] length - length of aircraft in meters, can be set up to 999 meters
//@param[out] width - width of aircraft in meters, can be set up to 999 meters
void inputSize(uint16_t* length, uint16_t* width) {
	char tempLength[4]; // array of digits for A/C length
	char tempWidth[4];  // array of digits for A/C width
	uint8_t base = 10;  // demical base

	codeToWord(*length, tempLength, sizeof(tempLength), base);
	codeToWord(*width, tempWidth, sizeof(tempWidth), base);


	// title with current size
	char titleCurSize[
		sizeof(tempLength) +
			sizeof(tempLength) +
			sizeof("L W")
			- 2
	];
	strcpy_s(titleCurSize, sizeof(titleCurSize), "L");
	strcat_s(titleCurSize, sizeof(titleCurSize), tempLength);
	strcat_s(titleCurSize, sizeof(titleCurSize), " W");
	strcat_s(titleCurSize, sizeof(titleCurSize), tempWidth);

	// input some title onto display
	putStrDirectly(top, "Size, m", sizeof("Size, m") + 1);
	putStrDirectly(middle, titleCurSize, sizeof(titleCurSize) + 1);
	putStrDirectly(bottom, "Configuration", sizeof("Configuration") + 1);


	uint8_t key = 0;
	// receive key in order to get to menu or go to next 
	while (key != FNK && key != Input) {
		key = receiveKey();
	}

	// if user chose Input, change parameters
	if (key == Input) {
		cleanScreen();

		putStrDirectly(top, "Length, m", sizeof("Length, m") + 1);
		putStrValue(middle, tempLength, sizeof(tempWidth), -1);
		putStrDirectly(bottom, "Configuration", sizeof("Configuration") + 1);
		uint8_t save1 = controlPanel(tempLength, sizeof(tempLength), base);

		putStrDirectly(top, "Width, m", sizeof("Width, m") + 1);
		putStrValue(middle, tempWidth, sizeof(tempWidth), -1);
		uint8_t save2 = controlPanel(tempWidth, sizeof(tempWidth), base);

		if (save1 == Input)
			*length = wordToCode(tempLength, sizeof(tempLength), base);
		if (save2 == Input)
			*width = wordToCode(tempWidth, sizeof(tempWidth), base);
	}

	cleanScreen();
}

//@brief submenu, where user changes units of measurement for A/C's height
//@param[out] heightUnit - index of current measurement in heightUnitsArray[]
void changeHeightInits(uint8_t* heightUnit) {
	uint8_t temp_heightUnit = *heightUnit;

	// input some title onto display
	putStrDirectly(top, "Meters/Feet", sizeof("Meters/Feet"));
	putStrDirectly(middle, heightUnitsArray[temp_heightUnit], strlen(heightUnitsArray[temp_heightUnit]) + 1);
	putStrDirectly(bottom, "Configuration", sizeof("Configuration"));

	uint8_t lastKey = chooseMode(&temp_heightUnit, heightUnitsArray, heightUnitsArraySize);

	if (lastKey == Input) {
		*heightUnit = temp_heightUnit;
	}
	cleanScreen();
}

//@brief submenu that fulfills quit from configuration menu, works until Input or FNK key aren't pressed 
//@return last inputed key, only can return Input (quit) or FNK (continue)
uint8_t quitConfiguration() {
	putStrDirectly(top, "Quit", sizeof("Quit"));
	putStrDirectly(bottom, "Configuration", sizeof("Configuration"));

	// waiting for Input or FNK key
	uint8_t res = 0;
	while (res != Input && res != FNK)
		res = receiveKey();

	cleanScreen();
	return res;
}

//@brief main function of program
void mainMenu() {
	initConfiguration(&Con);
	initState(&Stat);

	while (true) {
		char buffStr[CODE_A_SIZE + 1];
		codeToWord(Con.codeA, buffStr, sizeof(buffStr), 10);
		putStrInField(right, top, buffStr, strlen(buffStr) + 1);
		putStrInField(left, middle, Con.flightNumber, strlen(Con.flightNumber) + 1);

		uint8_t key;
		key = receiveKey();

		switch (key) {
		case FNK_hold10sec:
		{
			cleanScreen();
			configurationMenu();
		} break;

		case FNK:
		{
			cleanScreen();
			coordMenu();
		} break;

		default: break;
		}
	}
}

//@brief part of menu, where user chooses value of ICAO, code A, flight number etc, 
//@param[out] data[] - string with symbols that user wants to change, include '\0' that can't be changed
//@param[in] dataLength - size of data[], including '\0'
//@param[in] base - base that limits input, like octal, demical and hexademical bases. Also allow to use 37 base to input letters
//@return last inputed key, only can be Input or FNK
uint8_t controlPanel(char data[], const uint8_t dataLength, const uint8_t base) {
	uint8_t res;              // last inputed key

	bool done = false;        // loop value
	uint8_t iterator = 0;     // index of digit (left to rigth)

	uint8_t key = 0;

	// putStrDirectly(middle, data, dataLength);

	// choose page with setting or move to next
	while (key != FNK && key != Input) {
		key = receiveKey();
		res = key;
	}


	while (!done && key != FNK) {
		// show the current result
		putStrValue(middle, data, dataLength, iterator);

		key = receiveKey();

		switch (key) {
		case encoderEnter:
		{
			if (iterator >= dataLength - 2) // looping input of number and letters
				iterator = 0;
			else
				iterator++;
		} break;

		case encoderLeft:
		{
			if (data[iterator] == baseAndLetters[0])          // case, when we need to change to the highest digit of base (7, 9, F, space)
				data[iterator] = baseAndLetters[base - 1];
			else if (data[iterator] == 'A')                   // case, when digit equal A and it's necessary to change to 9
				data[iterator] = '9';
			else if (data[iterator] == ' ')                   // case, when symbol equal space and it's necessary to change to Z
				data[iterator] = 'Z';
			else
				data[iterator]--;                             // rest cases
		} break;

		case encoderRight:
		{
			if (data[iterator] == baseAndLetters[base - 1])   // case, when we need to change to 0
				data[iterator] = baseAndLetters[0];
			else if (data[iterator] == '9')                   // case, when digit equal 9 and it's necessary to change to A
				data[iterator] = 'A';
			else if (data[iterator] == 'Z')                   // case, when letter equal Z and it's necessary to change to space
				data[iterator] = ' ';
			else
				data[iterator]++;                             // rest cases
		} break;

		case FNK:
		{
			done = true;
			res = FNK;
		} break;

		case Input:
		{
			done = true;
			res = Input;
		}

		case FNK_hold10sec:
		{

			// TODO some functionality

		} break;

		default:
			break;
		}
		cleanRow(middle);
	}

	return res;
}

//@brief convert number to string of digits
//@param[in] code - number which should be converted
//@param[out] word - string, that will be showed onto display
void codeToWord(uint32_t code, char word[], const uint8_t wordLength, const uint8_t base) {
	memset(word, '0', wordLength - 1); // set all elements of array to 0, except last '\0'
	uint8_t i = wordLength - 2;

	while (code > 0) {
		word[i] = baseAndLetters[code % base];

		code /= base;
		i--;
	}
	word[wordLength - 1] = '\0';
}

//@brief convert string of digits to number
//@param[in] word[] - string, that's necessary to convert
//@param[in] wordLength - size of word[], including '\0'
//@param[in] base - base of number (octal, demical, hexademical)
uint32_t wordToCode(char word[], const uint8_t wordLength, const uint8_t base) {
	uint32_t res = 0;
	for (int i = 0; i < wordLength - 1; i++) {

		switch (word[i]) {
		case 'A': word[i] = 10; break;
		case 'B': word[i] = 11; break;
		case 'C': word[i] = 12; break;
		case 'D': word[i] = 13; break;
		case 'E': word[i] = 14; break;
		case 'F': word[i] = 15; break;
		default: word[i] -= '0';  break;
		}

		res += word[i] * pow(base, wordLength - i - 2);
	}
	return res;
}

//@brief part of menu, where user chooses mode of sensor air-surface, SIL level or set of category in ACCategory() 
//@param[out] mode - current mode as index of arrayModes
//@param[in] arrayModes - array of modes that user will see
//@param[int] arraySize - size of array
//@return last inputed key, only can be Input or FNK
uint8_t chooseMode(uint8_t* mode, char** arrayModes, uint8_t arraySize) {
	uint8_t res;              // last inputed key

	bool done = false;        // loop value

	uint8_t key = 0;

	// choose page with setting or move to next
	while (key != FNK && key != Input) {
		key = receiveKey();
		res = key;
	}
	cleanRow(middle);

	while (!done && key != FNK) {
		// show the current result
		putStrMode(middle, arrayModes[*mode], strlen(arrayModes[*mode]) + 1);

		key = receiveKey();

		switch (key) {
		case encoderLeft:
		{
			if (*mode <= 0)             // case when we need came to beginning and we need to loop choice of mode
				*mode = arraySize - 1;
			else {                      // the rest cases
				(*mode)--;
			}
		} break;

		case encoderRight:
		{
			if (*mode >= arraySize - 1) // case when we need came to end and we need to loop choice of mode
				*mode = 0;
			else {
				(*mode)++;              // the rest cases
			}
		} break;

		case FNK:
		{
			done = true;
			res = FNK;
		} break;

		case Input:
		{
			done = true;
			res = Input;
		} break;

		default:
			break;
		}
		cleanRow(middle);               // clean row after selecting another mode
	}

	return res;
}

//@brief menu with submenus to change configurations of A/C
void configurationMenu() {
	uint8_t lastKey = 0;

	// pressed Input means, that user wants to quit
	while (lastKey != Input) {
		inputICAO(&Con.ICAO);
		inputCodeA(&Con.codeA);
		inputCodeVFR(&Con.codeVFR);
		inputFlightNumber(&Con.flightNumber, sizeof(&Con.flightNumber) + 1); // I don't know why, but sizeof() gives 8 instead of 9
		//inputVelocityCategory();
		inputACCategory(&Con.ACCat);
		inputSensorAS(&Con.sensorAS);
		inputSIL(&Con.SIL);
		changeHeightInits(&Con.heightUnit);
		inputSize(&Con.length, &Con.width);

		lastKey = quitConfiguration();
	}
}

void coordMenu() {
	return;
}

//@brief find index of closest number from array to a target, is used in convertHeight()
//@param[in] arr - just array
//@param[in] size - size of array
//@param[in] target - given number, to that we need find the closest value
//@return index from array to the closest number to the target
uint8_t findClosest(int16_t arr[], uint8_t size, int16_t target) {
	// finding the closest number to target by binary search
	int8_t low = 0;
	int8_t mid = 0;
	int8_t high = size - 1;
	while (low <= high) {
		mid = low + (high - low) / 2;

		// check if target is present at mid
		if (arr[mid] == target)
			return mid;

		// if target greater, ignore left half
		if (arr[mid] < target) {
			low = mid + 1;
		}


		// if target is smaller, ignore right half
		else {
			high = mid - 1;
		}

	}

	// only single element left after search
	// check neighbors, are they closer to the target
	if ((abs(arr[mid] - target) > abs(arr[mid - 1] - target)) && mid != 0)
		mid--;
	if (abs(arr[mid] - target) > abs(arr[mid + 1] - target) && mid != (size - 1))
		mid++;

	return mid;
}

//@brief round height by table for IFR and convert it to chosen unit of measurement
//@param[in] heightTarget - heigth that it converts
//@param[in] unit - unit of measurement of returning height
//@return rounded and converted number in meters or feet
int16_t convertHeight(int16_t heightTarget, enum heightUnit unit) {
	// height's table for Instrument Flight Rules (IFR)
	const uint16_t metersTable[] = {
		300,
		900,
		1500,
		2150,
		2750,
		3350,
		3950,
		4550,
		5200,
		5800,
		6400,
		7000,
		7600,
		8250,
		8850,
		9450,
		10050,
		10650,
		11300,
		11900,
		12500,
		13700,
		14950
	};

	const uint16_t FL_Table[] = {
		10,
		30,
		50,
		70,
		90,
		110,
		130,
		150,
		170,
		190,
		210,
		230,
		250,
		270,
		290,
		310,
		330,
		350,
		370,
		390,
		410,
		450,
		490
	};

	// find the closest value in meters
	uint8_t index = findClosest(metersTable, sizeof(metersTable) / sizeof(metersTable[0]), heightTarget);
	
	// return value in choosen unit of measurement (found index match to 2 tables)
	if (unit == meter)
		return metersTable[index];
	else
		return FL_Table[index];
}
