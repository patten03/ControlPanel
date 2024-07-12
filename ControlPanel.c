#include "interface.h"

int main() {
	uint8_t mode = 0;
	chooseMode(&mode, sensorModesArray, sizeSensorArray);

	mainMenu();


	return 0;
}