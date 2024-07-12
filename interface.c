#include "interface.h"

// In order to input octal, demical and hexademical bases and letters (including space)
extern const char baseAndLetters[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

// Sensor air/surface
extern const char* sensorModesArray[] = { "Yes", "Manual mode", "No" };
extern const uint8_t sizeSensorArray = 3;

// SIL
extern const char* SIL_Array[] = { "Low", "Medium", "High" };
extern const uint8_t sizeSIL_Array = 3;

void init(struct Configuration* con) {
	con->ICAO = 0;
	con->codeA = 0;
	con->codeVFR = 0;

	memset(con->flightNumber, ' ', sizeof(con->flightNumber));
	con->flightNumber[sizeof(con->flightNumber) - 1] = '\0';

	con->velocityCategory = 0;

	con->ACCat.set = 'A';
	con->ACCat.category = 0;

	// sensor surface/air
	// SIL

	con->length = 0;
	con->width = 0;
}

void inputICAO(uint32_t* ICAO) {
	char address[7];          // ICAO address as array of digits
	uint8_t base = 16;        // hexademical base

	codeToWord(*ICAO, address, sizeof(address), base);

	// input some title onto display (Andrew)
	putStrDirectly(0, "ICAO address", 13);
	putStrDirectly(4, "Configuration", 14);

	uint8_t save = controlPanel(address, sizeof(address), base);

	if (save == Input) {
		*ICAO = wordToCode(address, sizeof(address), base);
	}

	// erase display data (Andrew)
	system("cls");
}

void inputCodeA(uint16_t* codeA) {
	char code[5];            // code A array as array of digits
	uint8_t base = 8;        // octal base

	codeToWord(*codeA, code, sizeof(code), base);

	// input some title onto display (Andrew)
	putStrDirectly(0, "Code A", 7);
	putStrDirectly(4, "Configuration", 14);

	uint8_t save = controlPanel(code, sizeof(code), base);

	if (save == Input) {
		*codeA = wordToCode(code, sizeof(code), base);
	}

	// erase display data (Andrew)
	system("cls");
}

void inputCodeVFR(uint16_t* codeVFR) {
	char code[5];            // code VFR array of digits
	uint8_t base = 8;        // octal base

	codeToWord(*codeVFR, code, sizeof(code), base);

	// input some title onto display (Andrew)
	putStrDirectly(0, "Code VFP", 9);
	putStrDirectly(4, "Configuration", 14);

	uint8_t save = controlPanel(code, sizeof(code), base);

	if (save == Input) {
		*codeVFR = wordToCode(code, sizeof(code), base);
	}

	// erase display data (Andrew)
	system("cls");
}

void inputFlightNumber(char flightNumber[], uint8_t numLength) {
	char tempFlightNumber[9]; // flight number 
	uint8_t base = 37;        // include all digits, letter and space

	strcpy_s(tempFlightNumber, sizeof(tempFlightNumber), flightNumber);

	// input some title onto display (Andrew)
	putStrDirectly(top, "Flight number", sizeof("Flight number") + 1);
	putStrDirectly(bottom, "Configuration", sizeof("Configuration") + 1);

	uint8_t save = controlPanel(tempFlightNumber, sizeof(tempFlightNumber), base);

	if (save == Input) {
		strcpy_s(flightNumber, numLength, tempFlightNumber);
	}

	// erase display data (Andrew)
	system("cls");
}

void inputACCategory(struct ACCategory* ACCat) {
	char tempSet;        // set of categories for A/C
	uint8_t category;    // category of A/C
	uint8_t base = 8;    // octal base

	char titleCurACCat[
		sizeof("Cat. _ *")
	];
	strcpy_s(titleCurACCat, sizeof(titleCurACCat), "Cat. ");
	strcat_s(titleCurACCat, sizeof(titleCurACCat), ACCat->set);
	strcat_s(titleCurACCat, sizeof(titleCurACCat), ' ');
	strcat_s(titleCurACCat, sizeof(titleCurACCat), (char)('0' + ACCat->category));

	// input some title onto display (Andrew)
	putStrDirectly(0, "Category A/C", sizeof("Category A/C") + 1);
	putStrDirectly(2, titleCurACCat, sizeof(titleCurACCat) + 1);
	putStrDirectly(4, "Configuration", sizeof("Configuration") + 1);

	uint8_t key = 0;
	// receive key in order to get to menu or go to next 
	while (key != FNK && key != Input) {
		key = receiveKey();
	}

	// if user chose Input, change parametrs
	if (key == Input) {
		system("cls");




	}
}

//void inputSensorAS(uint8_t* sensorMode) {
//	uint8_t tempSensorMode;  // Mode of air-surface sensor
//
//	// input some title onto display (Andrew)
//	putStrDirectly(top, "Sensor A-S", sizeof("Sensor A-S"));
//	putStrDirectly(middle, "Configuration", sizeof("Configuration"));
//
//	uint8_t save = chooseRegime(tempSensorMode, sensorModesArray, sizeSensorArray);
//
//	if (save == Input) {
//		*sensorMode = tempSensorMode;
//	}
//}

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

	// input some title onto display (Andrew)
	putStrDirectly(0, "Size, m", sizeof("Size, m") + 1);
	putStrDirectly(2, titleCurSize, sizeof(titleCurSize) + 1);
	putStrDirectly(4, "Configuration", sizeof("Configuration") + 1);


	uint8_t key = 0;
	// receive key in order to get to menu or go to next 
	while (key != FNK && key != Input) {
		key = receiveKey();
	}

	// if user chose Input, change parametrs
	if (key == Input) {
		system("cls");

		putStrDirectly(0, "Length, m", sizeof("Length, m") + 1);
		putStrDirectly(4, "Configuration", sizeof("Configuration") + 1);
		uint8_t save1 = controlPanel(tempLength, sizeof(tempLength), base);
		putStrDirectly(0, "Width, m", sizeof("Width, m") + 1);
		uint8_t save2 = controlPanel(tempWidth, sizeof(tempWidth), base);

		if (save1 == Input)
			*length = wordToCode(tempLength, sizeof(tempLength), base);
		if (save2 == Input)
			*width = wordToCode(tempWidth, sizeof(tempWidth), base);
	}

	system("cls");
}

void mainMenu() {
	uint8_t mode = Off;
	struct Configuration con;
	init(&con);

	while (mode == Off) {
		mode = receiveKey();
		switch (mode) {
		case On: break;
		case SBY: break;
		case GND: break;
		case Alt: break;

		default:
		{
			mode = Off;
		} break;
		}
	}

	while (mode != Off) {
		inputICAO(&con.ICAO);
		inputCodeA(&con.codeA);
		inputCodeVFR(&con.codeVFR);
		inputFlightNumber(&con.flightNumber, sizeof(&con.flightNumber) + 1); // I don't know why, but sizeof gives 8 instead of 9
		// con.inputVelocityCategory();
		// con.inputACCategory();
		// sensor surface/air
		// sil
		inputSize(&con.length, &con.width);
	}
}

// it's only for console, on stm32 you need to replace it
void putStrDirectly(uint8_t y, char str[], uint8_t strSize) {
	DWORD dw;
	COORD here;
	here.X = 0;
	here.Y = y;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) {
		printf("Invalid handle");
	}

	LPCSTR tempStr = str;

	WriteConsoleOutputCharacterA(hStdOut, tempStr, strSize - 1, here, &dw);
}

void putStrMode(uint8_t y, char str[], uint8_t strSize) {
	DWORD dw, write;
	COORD here;
	here.X = 0;
	here.Y = y;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) {
		printf("Invalid handle");
	}

	LPCSTR tempStr = str;

	FillConsoleOutputAttribute(hStdOut, 240, strSize - 1, here, &write);
	WriteConsoleOutputCharacterA(hStdOut, str, strSize - 1, here, &dw);
}

void cleanScreen() {
	system("cls");
}

void cleanRow(uint8_t y) {
	DWORD dw, write;
	COORD here;
	here.X = 0;
	here.Y = y;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) {
		printf("Invalid handle");
	}

	FillConsoleOutputAttribute(hStdOut, 7, strlen("           "), here, &write);
	WriteConsoleOutputCharacterA(hStdOut, "           ", strlen("           "), here, &dw); // just put empty string to overlap another string
}

uint8_t receiveKey() {
	uint8_t res = _getch();
	return res;
}

uint8_t controlPanel(uint8_t data[], const uint8_t dataLength, const uint8_t base) {
	uint8_t res;              // last inputed key

	bool done = false;        // loop value
	uint8_t iterator = 0;     // index of digit (left to rigth)

	uint8_t key = 0;

	putStrDirectly(2, data, dataLength);

	// choose page with setting or move to next
	while (key != FNK && key != Input) {
		key = receiveKey();
		res = key;
	}


	while (!done && key != FNK) {
		// show the current result
		putStrDirectly(2, data, dataLength);

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
	}

	return res;
}

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

uint8_t chooseMode(uint8_t* mode, char** arrayModes, uint8_t arraySize) {
	uint8_t res;              // last inputed key

	bool done = false;        // loop value

	uint8_t key = 0;

	putStrDirectly(middle, arrayModes[*mode], strlen(arrayModes[*mode]) + 1);

	// choose page with setting or move to next
	while (key != FNK && key != Input) {
		key = receiveKey();
		res = key;
	}


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
		cleanRow(middle);
	}

	return res;
}
