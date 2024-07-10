#include "interface.h"

void Configuration::init(){
	ICAO = 0;
	codeA = 0;
	codeVFR = 0;

	memset(flightNumber, 0, sizeof(flightNumber));
	velocityCategory = 0;

	ACCat.setA = 0;
	ACCat.setB = 0;
	ACCat.setC = 0;

	// sensor surface/air
	// SIL

	length = 0;
	width = 0;
}

void Configuration::inputICAO() {
	uint8_t address[6];      // ICAO address as array of digits
	uint8_t base(16);        // hexademical base

	codeToWord(ICAO, address, sizeof(address), base);

	// input some title onto display (Andrew)

	uint8_t save = controlPanel(address, sizeof(address), base);

	if (save == INPUT) {
		ICAO = wordToCode(address, sizeof(address), base);
	}
}

void Configuration::inputCodeA() {
	uint8_t code[4];        // code A array of digits
	uint8_t base(8);        // octal base

	codeToWord(codeA, code, sizeof(code), base);

	// input some title onto display (Andrew)

	uint8_t save = controlPanel(code, sizeof(code), base);

	if (save == INPUT) {
		codeA = wordToCode(code, sizeof(code), base);
	}
}

void Configuration::inputCodeVFR() {
	uint8_t code[4];        // code VFR array of digits
	uint8_t base(8);        // octal base

	codeToWord(codeA, code, sizeof(code), base);

	// input some title onto display (Andrew)

	uint8_t save = controlPanel(code, sizeof(code), base);

	if (save == INPUT) {
		codeA = wordToCode(code, sizeof(code), base);
	}
}

void Configuration::inputACCategory() {
	uint8_t tempSetA, tempSetB, tempSetC;      // 3 sets of categories
	uint8_t base(8);            // octal base
	uint8_t *category_ptr;

}

void mainMenu(){
	uint8_t mode = Off;
	Configuration con;
	con.init();

	printf("Turn on device by On button\n");
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
		con.inputICAO();
		con.inputCodeA();
		con.inputCodeVFR();
		// con.inputFlightNumber();
		// con.inputVelocityCategory();
		// con.inputACCategory();
		// sensor surface/air
		// sil
		// con.inputSize();
	}
}

// It's on you, Andrew
void showInput(const uint8_t data[], const uint8_t dataLength, const uint8_t base) {
	system("cls");

	for (int i = 0; i < dataLength; i++) {
		printf("%X ", data[i]);
	}
	printf("\n");
}

uint8_t receiveKey() {
	uint8_t res = _getch();
	return res;
}

uint8_t controlPanel(uint8_t data[], const uint8_t dataLength, const uint8_t base) {
	uint8_t res; // last inputed key

	bool done(false);        // loop value
	uint8_t iterator(0);     // index of digit (left to rigth)

	uint8_t key = 0;
	
	// choose page with setting or move to next
	showInput(data, dataLength, base);
	printf("To change settings press INPUT, in order to move to next page press FNK\n");
	while (key != FNK && key != INPUT) {
		key = receiveKey();
		res = key;
	}
		

	while (!done && key != FNK) {
		// show the current result
		showInput(data, dataLength, base);

		key = receiveKey();

		switch (key) {
		case encoderEnter:
		{
			if (iterator >= dataLength - 1) // looping input of number
				iterator = 0;
			else
				iterator++;
		} break;

		case encoderLeft:
		{
			if (data[iterator] <= 0)        // looping input of digits
				data[iterator] = base - 1;
			else
				data[iterator]--;
		} break;

		case encoderRight:                  // looping input of digits
		{
			if (data[iterator] >= base - 1)
				data[iterator] = 0;
			else
				data[iterator]++;
		} break;

		case FNK:
		{
			done = true;
			res = FNK;
		} break;

		case INPUT:
		{
			done = true;
			res = INPUT;
		}

		case FNK_hold10sec:
		{

			// TODO some functionality

		} break;

		default:
			break;
		}
	}

	system("cls");
	return res;
}

void codeToWord(uint32_t code, uint8_t word[], const uint8_t wordLength, const uint8_t base) {
	memset(word, 0, wordLength); // set all elements of array to 0
	uint8_t i(wordLength - 1);

	while (code > 0) {
		word[i] = code % base;
		code /= base;
		i--;
	}
}

uint32_t wordToCode(uint8_t word[], const uint8_t wordLength, const uint8_t base) {
	uint32_t res = 0;
	for (int i = 0; i < wordLength; i++) {
		res += word[i] * uint32_t(pow(base, wordLength - i - 1));
	}

	return res;
}