#include "interface.h"

void Configuration::inputICAO() {
	uint8_t address[]{ 0,0,0,0,0,0 };
	uint8_t base(16);        // hexademical base

	controlPanel(address, sizeof(address), base);

}

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