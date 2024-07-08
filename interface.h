#ifndef INTERFACE
#define INTERFACE

#include <stdio.h>
#include <iostream>
#include <conio.h>

// TODO after import to keil you have to change keys values
enum keys {
	SIGN,                                          // (ZNAK)
	INPUT,                                         // (VVOD)
	VFR,                                           // visual flight rules (PVP)
	FNK = 27, FNK_hold10sec,                       // What's a FNK button on controller?
	encoderLeft = 'a', encoderRight = 'd', encoderEnter = 13
};

struct Configuration
{
	uint32_t ICAO;

	void inputICAO();
};


#endif // INTERFACE