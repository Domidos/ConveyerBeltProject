
#include <stdio.h>
#include <sockLib.h>
#include <inetLib.h>
#include "FHV.h"

#define SERVER_PORT_NUM 5555  	//server's port number for bind() 

extern UCHAR slaves[11];

void initSlaves (int debug) {

	UCHAR i;
	char buffer [20];

	i = 0;
	do {
		
		// set up a TCP client to communicate with the slave
		struct sockaddr_in serverAddr; 		/* server's socket address */
		int sockAddrSize; 					/* size of socket address structure */
		int sfd1; 							/* socket file descriptor */

		/* create client's socket */
		if ((sfd1 = socket(AF_INET, SOCK_STREAM, 0)) == ERROR){
			printf("Socket not created\n");
		}

		/* bind not required - port number is dynamic */

		/* build server socket address */
		sockAddrSize = sizeof (struct sockaddr_in);
		bzero ((char *) &serverAddr, sockAddrSize);
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_len = (u_char) sockAddrSize;
		serverAddr.sin_port = htons (SERVER_PORT_NUM);
		sprintf (buffer,"91.0.0.%d",slaves[i]);
		
		if (((serverAddr.sin_addr.s_addr = inet_addr (buffer)) == ERROR) 
				&& ((serverAddr.sin_addr.s_addr = hostGetByName (buffer)) == ERROR)){
			printf("Socket address failed\n");
			close (sfd1);
		}

		/* connect to server */
		if (connect (sfd1, (struct sockaddr *) &serverAddr, sockAddrSize) == ERROR){
			printf("Connect failed\n");
			close (sfd1);
		}

		/* set up right neighbor address */
		if (slaves[i+1] != 0) sprintf (buffer, "Right 91.0.0.%d\r\n", slaves[i+1]);
		else sprintf (buffer, "Right 91.0.0.%d\r\n", slaves[0]);
		write (sfd1, (char *) &buffer, strlen(buffer));
		if (debug !=0) {
			printf ("\nSent mesage to slave %i \n", slaves[i]);
			if (slaves[i+1] != 0) printf ("Its right neighbor shall be %i \n", slaves[i+1]);
			else printf ("Its right neighbor shall be %i \n", slaves[0]);
		}
		beLazy(50);
		/* close the socket again */
		close (sfd1);

		i++;
	} while(slaves[i] != 0);

}

void initPlaying (int slave) {

	char buffer [20];

	// set up a TCP client to communicate with the slave
	struct sockaddr_in serverAddr; 		/* server's socket address */
	int sockAddrSize; 					/* size of socket address structure */
	int sfd1; 							/* socket file descriptor */

	/* create client's socket */
	if ((sfd1 = socket(AF_INET, SOCK_STREAM, 0)) == ERROR){
		printf("Socket not created\n");
	}

	/* bind not required - port number is dynamic */

	/* build server socket address */
	sockAddrSize = sizeof (struct sockaddr_in);
	bzero ((char *) &serverAddr, sockAddrSize);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_len = (u_char) sockAddrSize;
	serverAddr.sin_port = htons (SERVER_PORT_NUM);
	sprintf (buffer,"91.0.0.%d",slave);

	if (((serverAddr.sin_addr.s_addr = inet_addr (buffer)) == ERROR) 
			&& ((serverAddr.sin_addr.s_addr = hostGetByName (buffer)) == ERROR)){
		printf("Socket address failed\n");
		close (sfd1);
	}

	/* connect to server */
	if (connect (sfd1, (struct sockaddr *) &serverAddr, sockAddrSize) == ERROR){
		printf("Connect failed\n");
		close (sfd1);
	}

	/* set up right neighbor address */
	sprintf (buffer, "Request\r\n");
	write (sfd1, (char *) &buffer, strlen(buffer));
	printf ("\n Sent first request to slave %d", slave);

	if (slave == 7) beLazy(50);
	/* close the socket again */
	close (sfd1);

}



