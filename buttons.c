#include "buttons.h"

//@brief recieve pressed key
//@return code of pressed key
uint8_t receiveKey() {
	uint8_t res = _getch();
	return res;
}