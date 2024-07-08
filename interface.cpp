#include "interface.h"

void Configuration::inputICAO() {
	uint8_t address[6];      // ICAO address as array of digits
	uint8_t base(16);        // hexademical base

	codeToWord(ICAO, address, sizeof(address), base);

	// input some title onto display (Andrew)

	controlPanel(address, sizeof(address), base);

	ICAO = wordToCode(address, sizeof(address), base);
}

void Configuration::inputCodeA() {
	uint8_t code[4];        // code A array of digits
	uint8_t base(8);        // hexademical base

	codeToWord(ICAO, code, sizeof(code), base);

	// input some title onto display (Andrew)

	controlPanel(code, sizeof(code), base);

	ICAO = wordToCode(code, sizeof(code), base);
}

// It's on you, Andrew
void showInput(const uint8_t data[], const uint8_t dataLength, const uint8_t base) {
	system("cls");

	for (int i = 0; i < dataLength; i++) {
		printf("%X ", data[i]);
	}
}

uint8_t receiveKey() {
	uint8_t res = _getch();
	return res;
}

void controlPanel(uint8_t data[], const uint8_t dataLength, const uint8_t base) {

	bool done(false);        // loop value
	uint8_t iterator(0);     // index of digit (left to rigth)

	while (!done) {
		// show the current result
		showInput(data, dataLength, base);

		uint8_t key;
		key = receiveKey();

		switch (key) {
		case encoderEnter:
		{
			if (iterator >= dataLength - 1) // looping input of digits
				iterator = 0;
			else
				iterator++;
		} break;

		case encoderLeft:
		{
			if (data[iterator] <= 0)
				data[iterator] = base - 1;
			else
				data[iterator]--;
		} break;

		case encoderRight:
		{
			if (data[iterator] >= base - 1)
				data[iterator] = 0;
			else
				data[iterator]++;
		} break;

		case FNK:
		{
			done = true;
		} break;

		case FNK_hold10sec:
		{

			// TODO some functionality

		} break;

		default:
			break;
		}
	}
}

void codeToWord(uint32_t code, uint8_t word[], const uint8_t wordLength, const uint8_t base) {
	uint8_t i(wordLength - 1);

	while (code > 0) {
		word[i] = code % base;
		code /= base;
		i--;
	}
}

uint32_t wordToCode(uint8_t word[], const uint8_t wordLength, const uint8_t base) {
	memset(word, 0, wordLength * sizeof(uint8_t)); // set all elements of array to 0

	uint32_t res = 0;
	for (int i = 0; i < wordLength; i++) {
		res += word[i] * pow(base, wordLength - i - 1);
	}

	return res;
}