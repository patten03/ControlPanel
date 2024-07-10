#include "interface.h"

extern const char base16[] = "0123456789ABCDEF";

void init(struct Configuration* con) {
	con->ICAO = 0;
	con->codeA = 0;
	con->codeVFR = 0;

	memset(con->flightNumber, 0, sizeof(con->flightNumber));
	con->velocityCategory = 0;

	con->ACCat.setA = 0;
	con->ACCat.setB = 0;
	con->ACCat.setC = 0;

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
}

void inputSize(uint16_t* length, uint16_t* width) {
	uint8_t tempLength[3]; // array of digits for AC length
	uint8_t tempWidth[3];  // array of digits for AC width
	uint8_t base = 10;     // demical base

	codeToWord(*length, tempLength, sizeof(tempLength), base);
	codeToWord(*width, tempWidth, sizeof(tempWidth), base);



	

}

void mainMenu() {
	uint8_t mode = Off;
	struct Configuration con;
	init(&con);

	while (mode == Off) {
		mode = receiveKey();
		switch (mode)
		{
		case On: break;
		case SBY: break;
		case GND: break;
		case Alt: break;

		default: {
			mode = Off;
		} break;
		}
	}

	while (mode != Off) {
		inputICAO(&con.ICAO);
		inputCodeA(&con.codeA);
		inputCodeVFR(&con.codeVFR);
		// con.inputFlightNumber();
		// con.inputVelocityCategory();
		// con.inputACCategory();
		// sensor surface/air
		// sil
		inputSize(&con.length, &con.width);
	}
}

// It's on you, Andrew
void showInput(const uint8_t data[], const uint8_t dataLength, const uint8_t base) {
	system("cls");

	for (int i = 0; i < dataLength - 1; i++) {
		printf("%X ", data[i]);
	}
	printf("\n");
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

uint8_t receiveKey() {
	uint8_t res = _getch();
	return res;
}

uint8_t controlPanel(uint8_t data[], const uint8_t dataLength, const uint8_t base) {
	uint8_t res; // last inputed key

	bool done = false;       // loop value
	uint8_t iterator = 0;     // index of digit (left to rigth)

	uint8_t key = 0;

	// choose page with setting or move to next

	putStrDirectly(2, data, dataLength);
	while (key != FNK && key != Input) {
		key = receiveKey();
		res = key;
	}


	while (!done && key != FNK) {
		// show the current result
		putStrDirectly(2, data, dataLength);
		//showInput(data, dataLength, base);

		key = receiveKey();

		switch (key) {
		case encoderEnter:
		{
			if (iterator >= dataLength - 2) // looping input of number
				iterator = 0;
			else
				iterator++;
		} break;

		case encoderLeft: {
			if (data[iterator] == base16[0])          // case, when we need to change to the highest number of base (7, 9, F)
				data[iterator] = base16[base - 1];
			else if (data[iterator] == base16[10])    // case, when number equal A and it's necessary to change to 9
				data[iterator] = base16[9];
			else
				data[iterator]--;                    // rest cases
		} break;

		case encoderRight: {
			if (data[iterator] == base16[base - 1])   // case, when we need to change to 0
				data[iterator] = base16[0];
			else if (data[iterator] == base16[9])    // case, when number equal 9 and it's necessary to change to A
				data[iterator] = base16[10];
			else
				data[iterator]++;                     // rest cases
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
		word[i] = base16[code % base];

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
