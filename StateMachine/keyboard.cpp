#include <stdio.h>
#include <sysLib.h>
#include <stdLib.h>
#include "keyboard.h"

extern "C" {
#include "hwFunc.h"
}

int keyCount;

Keyboard :: Keyboard() {
	printf("Keyboard Konstruktor!\n\r");	
	return;
}

Keyboard :: ~Keyboard() {
	pressedKey = 0;
	return;
}

char Keyboard::getPressedKey( )
{
	pressedKey = getKey();
	if(pressedKey != '\0'){
	printf("pressed Key is: %c", pressedKey);
	}
	return pressedKey;
}
