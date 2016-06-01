
/* This is a test file for the PTP slave clock server 
* Waits for info from master and resends delay requests randomly.
*/

#include "ptpIncludes.h"
#include "FHV.h"

// Need to know whom to send, or use multicast
// Should modify UDP reoutines to be able to use multicast!

int propDelay, timeOffset;

STATUS syncClk (int debug) {

	struct request myRequest;
	int t0, t1, t2, t3;
	int i = 0;
	
	// Initialize myReceiveRequest
	myRequest.PTP_version = PTP_CURRENT_VERSION; /* PTP version used */
	myRequest.message_type = 0; /* PTP mesage type is here */
	myRequest.epoch_number = 0; /* part of timestamp */
	myRequest.seconds = 0; /* part of timestamp */
	myRequest.nanoseconds = 0; /* part of timestamp */
	strcpy(myRequest.inetAddr, "99.0.0.1");

	while (1) {

		// Wait for sync
		do {
			receiveUDP (&myRequest);
		} while (myRequest.message_type != SYNC_MESSAGE);
		t1 = time(NULL);
		if (debug) printf ("Sync recieved at t1: %d\n",t1);

		// Wait for follow-up
		receiveUDP (&myRequest);
		t0 = myRequest.seconds;
		if (debug) printf ("Sync was sent at t0: %d\n",t0);
	
		if (i == 0) {
			i++;
		
			// Send delay request
			myRequest.message_type = DELAY_REQ_MESSAGE;
			t2 = time(NULL);
			sendUDP (&myRequest);
			if (debug) printf ("Delay req was sent at t2: %d\n",t2);

			// Get delay response
			receiveUDP (&myRequest);
			t3= myRequest.seconds;
			if (debug) printf ("Delay resp received at t3: %d\n",t3);

		}
		else {
		// wenn eine Random-Zahl modulo 13 ist, dann i=0
			if ((rand() % 13) == 0) i = 0; 
		}
	
		// Hier kommt die Offset/Delay-Berechnung hinein
		timeOffset = (t1-t0-t3+t2)/2;
		propDelay = (t1-t0+t3-t2)/2;

		if (debug) printf ("Time offset is: %d\n",timeOffset);
		if (debug) printf ("Prop delay is: %d\n",propDelay);
	
	}
	return (OK);
}
