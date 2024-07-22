#include "display.h"

//@brief put some text into display with chosen row
//@param[in] y - coodinate of row
//@param[in] str[] - just string
//@param[in] strSize - size of str, including '\0'
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

//@brief put some value (ICAO address, code A, flight number etc) into display with chosen row, highlight selected symbol
//@param[in] y - coodinate of row
//@param[in] str[] - just value
//@param[in] strSize - size of str, including '\0'
//@param[in] chosenSymbol - index of selected symbol that necessay to highlight, if chosenSymbol is equal -1, none of them highlight
void putStrValue(uint8_t y, char str[], uint8_t strSize, int8_t chosenSymbol) {
	DWORD dw, write;
	COORD here;
	here.X = 0;
	here.Y = y;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) {
		printf("Invalid handle");
	}

	LPCSTR tempStr = str;

	if (chosenSymbol >= -1)
		FillConsoleOutputAttribute(hStdOut, 0b11110000, 1, (COORD) { here.X + chosenSymbol, here.Y }, & write);

	WriteConsoleOutputCharacterA(hStdOut, tempStr, strSize - 1, here, &dw);
}

//@brief put some text into display with chosen row, highlight all text
//@param[in] y - coodinate of row
//@param[in] str[] - just string
//@param[in] strSize - size of str, including '\0'
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

	FillConsoleOutputAttribute(hStdOut, 0b11110000, strSize - 1, here, &write);
	WriteConsoleOutputCharacterA(hStdOut, str, strSize - 1, here, &dw);
}

//@brief put some text into display with chosen row and column
//@param[in] x, y - coodinates of row and column
//@param[in] str[] - just string
//@param[in] strSize - size of str, including '\0'
void putStrInField(uint8_t x, uint8_t y, char str[], uint8_t strSize) {
	DWORD dw;
	COORD here;
	here.X = x;
	here.Y = y;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) {
		printf("Invalid handle");
	}

	LPCSTR tempStr = str;

	WriteConsoleOutputCharacterA(hStdOut, tempStr, strSize - 1, here, &dw);
}

//@brief clean all screen
void cleanScreen() {
	system("cls");
}

//@brief clean selected row
//@param[in] y - coodinate of row
void cleanRow(uint8_t y) {
	DWORD dw, write;
	COORD here;
	here.X = 0;
	here.Y = y;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) {
		printf("Invalid handle");
	}

	FillConsoleOutputAttribute(hStdOut, 0b00000111, strlen("                 "), here, &write);
	WriteConsoleOutputCharacterA(hStdOut, "                 ", strlen("                 "), here, &dw); // just put empty string to overlap another string
}

//@brief clean selected row
//@param[in] x, y - coodinates of row column
void cleanField(uint8_t x, uint8_t y) {
	DWORD dw, write;
	COORD here;
	here.X = x;
	here.Y = y;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) {
		printf("Invalid handle");
	}

	FillConsoleOutputAttribute(hStdOut, 0b00000111, strlen("         "), here, &write);
	WriteConsoleOutputCharacterA(hStdOut, "         ", strlen("         "), here, &dw); // just put empty string to overlap another string

}