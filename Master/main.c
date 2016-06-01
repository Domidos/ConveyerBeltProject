
// Main file for both use-cases and both master and slave

// #include <ifLib.h> ??
#include <stdio.h>
#include <sysLib.h>
#include <taskLib.h>
#include <inetLib.h>

#include "ptpMS.h"
#include "FHV.h"
#include "kbd.h"

#define masterX 0
// all the others are slaves

void tcpServerTask (void);
void initSlaves (int debug);
void initPlaying (int slave);

UCHAR slaves[11] = {6,4,2,10,5,8,7,0,0,0};

int main (int whoAmI, int debug, int inits, int start, int ptpOn) {

	char buffer [12];
	char newKey, boardNum;
	int ptpTask;
	
	sysOutByte (0x313, 0x99);
	if (whoAmI == masterX) {
		ifAddrSet("fei1", "91.0.0.91");
		if (debug != 0) printf ("\nMASTER, my IP address is: 91.0.0.91\n");
		if (ptpOn != 0) ptpTask = taskSpawn("sendClk",100,0,0x1000,(FUNCPTR) sendClk,debug,0,0,0,0,0,0,0,0,0);
		if (inits != 0) initSlaves(debug);
		beLazy (50);
		if (start != 0) initPlaying(slaves[0]);
		
		printf ("\n If you want new parcel to be sent enter number of board on the LEB keyboard \n");
		do {
			newKey = getKey();
			if ((newKey != 0) && (newKey != 'F')) {
				boardNum = newKey - 0x30;
				initPlaying (boardNum);
				printf ("Sent parcel to board #%d !\n",boardNum);
			}
			else if (newKey == 'F') {
				printf ("\n!!! Key F pressed: all tasks will be killed. For restart run the project again !!!\n");
				taskDelete (ptpTask);
				taskDelete (0);
			}
			beLazy(50);
		} while (1);
		
	return 0;
	}
	else if (whoAmI > masterX) {
		sprintf (buffer, "91.0.0.%d",whoAmI);
		ifAddrSet("fei1", buffer);
		if (debug != 0) printf ("\nSlave, my IP address is: %s\n", buffer);
		if (ptpOn != 0) syncClk (debug);
		if (inits != 0) taskSpawn ("tcpServer", 100, 0, 0x10000, (FUNCPTR)tcpServerTask, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	return 0;
	}
	else {
		printf ("Worng parameter!");
		return -1;
	}

} // End main
