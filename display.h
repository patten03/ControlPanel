#ifndef DISPLAY
#define DISPLAY

#include "interface.h"

// display work

void putStrDirectly(uint8_t y, char str[], uint8_t strSize);
void putStrValue(uint8_t y, char str[], uint8_t strSize, uint8_t chosenSymbol);
void putStrMode(uint8_t y, char str[], uint8_t strSize);
void putStrInField(uint8_t x, uint8_t y, char str[], uint8_t strSize);
void cleanScreen();
void cleanRow(uint8_t y);
void cleanField(uint8_t x, uint8_t y);

#endif