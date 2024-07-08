#include "interface.h"

void Configuration::inputICAO()
{
	bool done(false);        // loop value
	uint8_t iterator(0);     // index of digit (left to rigth 0-5)
	uint8_t address[]{ 0,0,0,0,0,0 };
	uint8_t base(16);        // hexademical base

	while (!done) {
		// show the current result
		system("cls");
		printf("%x %x %x %x %x %x\n",
			address[0], address[1], address[2], address[3], address[4], address[5]);

		uint8_t key;
		key = _getch();
		
		switch (key) {
		case encoderEnter: {
			if (iterator >= sizeof(address) - 1) // looping input of digits
				iterator = 0;
			else
				iterator++;
		} break;

		case encoderLeft: {
			if (address[iterator] <= 0)
				address[iterator] = base - 1;
			else
				address[iterator]--;
		} break;

		case encoderRight: {
			if (address[iterator] >= base - 1) 
				address[iterator] = 0;
			else
				address[iterator]++;
		} break;

		case FNK: {
			done = true;
		} break;
			
		case FNK_hold10sec: {

			// TODO some functionality

		} break;
		
		default:
			break;
		}
	}
}