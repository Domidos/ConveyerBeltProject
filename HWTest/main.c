/* main.c - Main Program to test functionality */

#include "hwFunc.h"
#include "disp.h"
#include "FHV.h"
#include <sysLib.h>
#include <ioLib.h>

int main (void)
{
	char textBuffer[88];
	char temp, temp2;
	short value;
	int fd;
	float valueF;
	
	initHardware(0);

	writeToDisplay (3,20, "Hello World");
	printf ("Hello World!");
	
	writeToDisplay (21, 20, "1 = MotorOn,  2 = MotorOff");

	watchdogSet(1);
	
	temp2 = 0;
		
	while (TRUE)
	{
		beLazy(50);
		printf(".");

		if (temp2 == 0) watchdogTrigger();

		temp = getKey();
		if (temp == '1') motorOn();
		else if (temp == '2') motorOff(); 
		else if (temp == '0')
		{
			writeToDisplay (5,20,"Waiting for Watchdog");
			while (1) printf (".");
		}
		else if (temp == '3')
		{
			watchdogDisable();
			temp2 = 1;
			writeToDisplay (5,20,"Watchdog disabled   ");
		}
		else if (temp == '4')
		{
			temp2 = 0;
			writeToDisplay (5,20,"Watchdog reenabled  ");
		}

		// read motor revolution speed
		value = getEncoderPulsesZeroCorrected();
		sprintf (textBuffer,"EncoderPulses:           %i    ", value);
		writeToDisplay (7, 20, textBuffer);
		
//		value = getRotationDirection ();
//		printf ("Dir: %i \n", value);
		
		// read voltage; in 1;  +/-10V
		value = readAnalog (1, 3);
		sprintf (textBuffer,"Motorspannung: %+4.2f V  %+i    ", value/204.75, value);
		writeToDisplay (9, 20, textBuffer);

		// read current; in 0;  +/-10V
		value = readAnalog (0, 3);
		sprintf (textBuffer,"Motorstrom:    %+4.2f V  %+i    ", value/204.75, value);
		writeToDisplay (11, 20, textBuffer);

		// read potentiometer; in 2 ;0-5V
		value = readAnalog (2, 0);
		sprintf (textBuffer,"Potentiometer: %+4.2f V  %+i    ", value/819.0, value);
		writeToDisplay (13, 20, textBuffer);

		writeAnalog (0, value);
		
		// read temperature; in 5;  0-5V
		value = readAnalog (5, 2);
		valueF = value/409.5;
		sprintf (textBuffer,"Temperatur:    %+4.2fV   %+i    ", valueF, value);
		writeToDisplay (15, 20, textBuffer);

		valueF = valueF - 4.68;
		
		sprintf (textBuffer,"Temperatur2:   %+4.2fV          ", valueF, value);
		writeToDisplay (17, 20, textBuffer);
		
		valueF = valueF / 0.01872;

		sprintf (textBuffer,"Temperatur3:   %+4.2f°C         ", valueF, value);
		writeToDisplay (19, 20, textBuffer);

	} /* while */
	return 0;
} /* main */
