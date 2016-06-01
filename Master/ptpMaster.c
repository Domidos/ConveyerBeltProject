
/* This is a test file for the PTP master clock server 
* Sends a new time value each 64 seconds, maximum allowed by PTP
*/

#include "ptpIncludes.h"
#include "FHV.h"
#include <semLib.h>

// Need to know whom to send, or use multicast
// Should modify UDP reoutines to be able to use multicast!

SEM_ID volatile udpSem;

extern UCHAR slaves[11];

STATUS procReq (int debug);

struct request mySendRequest;
struct request myReceivedRequest;

STATUS sendClk (int debug) {

	unsigned char i;
	char buffer [20];
	
	// Initialize mySendRequest
	mySendRequest.PTP_version = PTP_CURRENT_VERSION; /* PTP version used */
	mySendRequest.message_type = 0; /* PTP mesage type is here */
	mySendRequest.epoch_number = 0; /* part of timestamp */
	mySendRequest.seconds= 0; /* part of timestamp */
	mySendRequest.nanoseconds = 0; /* part of timestamp */

	// Spawn tasks to answer to delay requests

	udpSem   = semBCreate(SEM_Q_PRIORITY, SEM_FULL);

	taskSpawn("procReq",100,0,0x1000,(FUNCPTR) procReq,debug,0,0,0,0,0,0,0,0,0);
	
	while (1) {

	i = 0;
	do {
		// Set slave address
		sprintf (buffer, "91.0.0.%d", slaves[i]);
		strcpy(mySendRequest.inetAddr, buffer);

		// Set time
		mySendRequest.seconds = time(NULL);

		// Send sync
		mySendRequest.message_type = SYNC_MESSAGE;
		semTake(udpSem, WAIT_FOREVER);
		sendUDP (&mySendRequest);
		semGive(udpSem);

		if (debug) printf ("Sync sent at time: %d\n",mySendRequest.seconds);
	
		// Send follow-up. Does not really make sense, since I do not have a precise time
		mySendRequest.message_type = FOLLOW_UP_MESSAGE;
		semTake(udpSem, WAIT_FOREVER);
		sendUDP (&mySendRequest);
		semGive(udpSem);

		if (debug) printf ("Follow up sent also!\n");

		i++;
	} while (slaves[i] != 0);

	beLazy (4000);
	}
	return (OK);
}


STATUS procReq (int debug) {

	// Initialize myReceiveRequest
	// Initialize mySendRequest
	myReceivedRequest.PTP_version = PTP_CURRENT_VERSION; /* PTP version used */
	myReceivedRequest.message_type = 0; /* PTP mesage type is here */
	myReceivedRequest.epoch_number = 0; /* part of timestamp */
	myReceivedRequest.seconds= 0; /* part of timestamp */
	myReceivedRequest.nanoseconds = 0; /* part of timestamp */

	while (1) {

		if (debug) printf ("waiting for delay request ...\n");

		// wait for delay request
		receiveUDP (&myReceivedRequest);

		// get receive time
		myReceivedRequest.seconds = time(NULL);
	
		if (myReceivedRequest.message_type != DELAY_REQ_MESSAGE) {
			// error
			printf ("Wrong command - no delay request!\n");
		}
		else {
			if (debug) printf ("Received delay request from %s \n", myReceivedRequest.inetAddr);
			// send delay response
			myReceivedRequest.message_type = DELAY_RESP_MESSAGE;
			semTake(udpSem, WAIT_FOREVER);
			sendUDP (&myReceivedRequest);
			semGive(udpSem);
			if (debug) printf ("Delay response sent at time: %d\n",mySendRequest.seconds);
		}
	}
	return (OK);
}
