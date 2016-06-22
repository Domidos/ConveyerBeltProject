
/* TelnetServer.c - TCP server example */
/*
 DESCRIPTION
 This file contains the server-side of the TCP example code.
 The example code demonstrates the usage of several BSD 4.4-style
 socket routine calls.
 */
/* includes */
#include "vxWorks.h"
#include "sockLib.h"
#include "inetLib.h"
#include "taskLib.h"
#include "stdioLib.h"
#include "strLib.h"
#include "ioLib.h"
#include "fioLib.h"
#include "systemManager.h"
#include "stateMachine.h"
#include "TelnetServer.h"
#include "TCPClient.h"


StateMachine * myStateMachine; 	
STATUS telnetServer(void);	
//int sFd;
//int newFd;

TCPClient * myTCPClient;

TelnetServer :: TelnetServer() {
	printf("TelnetServer Konstruktor!\n\r");	
	return;
}

TelnetServer :: ~TelnetServer() {
	return;
}


void TelnetServer::init( ){

	//spawn TCP Server
	taskSpawn("telnetServer", 152, 0, 0x10000,(FUNCPTR) telnetServer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	return;
}





/* function declarations */
VOID telnetServerWorkTask(int sFd, char * address, u_short port); //changed
/****************************************************************************
 *
 * TelnetServer - accept and process requests over a TCP socket
 *
 * This routine creates a TCP socket, and accepts connections over the socket
 * from clients. Each client connection is handled by spawning a separate
 * task to handle client requests.
 *
 * This routine may be invoked as follows:
 * -> sp TelnetServer
 * task spawned: id = 0x3a6f1c, name = t1
 * value = 3829532 = 0x3a6f1c
 * -> MESSAGE FROM CLIENT (Internet Address 192.0.2.10, port 1027):
 * Hello out there
 *
 * RETURNS: Never, or ERROR if a resources could not be allocated.
 */
STATUS telnetServer(void) {
	struct sockaddr_in serverAddr; /* server's socket address */
	struct sockaddr_in clientAddr; /* client's socket address */
	int sockAddrSize; /* size of socket address structure */
	int sFd; /* socket file descriptor */
	int newFd; /* socket descriptor from accept */
	int ix = 0; /* counter for work task names */
	char workName[16]; /* name of work task */
	/* set up the local address */
	sockAddrSize = sizeof(struct sockaddr_in);
	bzero((char *) &serverAddr, sockAddrSize);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_len = (u_char) sockAddrSize;
	serverAddr.sin_port = htons(SERVER_PORT_NUM_TELNET);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	/* create a TCP-based socket */
	if ((sFd = socket(AF_INET, SOCK_STREAM, 0)) == ERROR) {
		perror("socket");
		return (ERROR);
	}
	/* bind socket to local address */
	if (bind(sFd, (struct sockaddr *) &serverAddr, sockAddrSize) == ERROR) {
		perror("bind");
		close(sFd);
		return (ERROR);
	}
	/* create queue for client connection requests */
	if (listen(sFd, SERVER_MAX_CONNECTIONS) == ERROR) {
		perror("listen");
		close(sFd);
		return (ERROR);
	}
	/* accept new connect requests and spawn tasks to process them */
	while (TRUE) {
		socklen_t len = sizeof(clientAddr);
		if ((newFd = accept(sFd, (struct sockaddr *) &clientAddr, &len))
				== ERROR) {
			perror("accept");
			close(sFd);
			return (ERROR);
		}
		sprintf(workName, "tTcpWork%d", ix++);
		if (taskSpawn(workName, SERVER_WORK_PRIORITY, 0, SERVER_STACK_SIZE,
				(FUNCPTR) telnetServerWorkTask, newFd,
				(int) inet_ntoa(clientAddr.sin_addr),
				ntohs(clientAddr.sin_port), 0, 0, 0, 0, 0, 0, 0) == ERROR) {
			/* if taskSpawn fails, close fd and return to top of loop */
			perror("taskSpawn");
			close(newFd);
		}
	}
}
/****************************************************************************
 *
 * TelnetServerWorkTask - process client requests
 *
 * This routine reads from the server's socket, and processes client
 * requests. If the client requests a reply message, this routine
 * will send a reply to the client.
 *
 * RETURNS: N/A.
 */
VOID telnetServerWorkTask(int sFd, /* server's socket fd */
char * address, /* client's socket address */
u_short port /* client's socket port */
) {
	char clientRequest[256];
	int row = 2;
	int column = 2;
	char stringBuffer[80];
//	struct request clientRequest; /* request/message from client */
	int nRead; /* number of bytes read */
	static char replyMsg[] = "Server received your message";
	/* read client request, display message */
	static char welcomeMsg[] = "Server on TELNET Port 4444 welcomes you.\n\r";
	if ((write(sFd, welcomeMsg, strlen(welcomeMsg))) == ERROR) {
		//error
	}
	while ((nRead = fioRdString(sFd, (char *) &clientRequest,
			sizeof(clientRequest))) > 0) {

		switch (clientRequest[0]) {
		case 'A': //change to chain mode
			
			myStateMachine->sendEvent("startProfile");
			sprintf(stringBuffer, "A Key Pressed ; start Profile\n\r");
			
			break;
			
		case 'B': //change to local mode	
			
			myStateMachine->sendEvent("setSpeed--");
			sprintf(stringBuffer, "B Key Pressed ; set speed --\n\r");
			
			break;
			
		case 'C': // Change direction
			
			myStateMachine->sendEvent("setSpeed++");
			sprintf(stringBuffer, "C Key Pressed ; set speed ++\n\r");
			
			break;
			
		case 'E': //decrease speed value 
			
			myStateMachine->sendEvent("directionRight");
			sprintf(stringBuffer, "Key E is Pressed ; change direction to right\n\r");
			
			break;
			
		case 'F': //increase speed value
			myStateMachine->sendEvent("directionLeft");
			sprintf(stringBuffer, "Key F is Pressed ; change direction to left\n\r");
					
			break;
			
		case '0': //start motor
			myStateMachine->sendEvent("getStatus");
			sprintf(stringBuffer, "Key 0 is Pressed ; start Transport of package\n\r");
						
			break;
			
		case '1': //start motor
			myStateMachine->sendEvent("setCommandChain");
			sprintf(stringBuffer, "Key 1 is Pressed ; from idleState to chainIdle\n\r");
								
			break;
			
		case '2': //start motor
			myStateMachine->sendEvent("setCommandLocal");
			sprintf(stringBuffer, "Key 2 is Pressed ; from idleState to localIdle\n\r");
										
			break;
							
		case '4': //start motor
			myStateMachine->sendEvent("toChainIdle");
			sprintf(stringBuffer, "Key 4 is Pressed ; from localIdle to chainIdle\n\r");
												
			break;
					
		case '5': //start motor
			myStateMachine->sendEvent("toLocalIdle");
			sprintf(stringBuffer, "Key 5 is Pressed ; from chainIdle to localIdle\n\r");
														
			break;
									
		case '8':
			myStateMachine->sendEvent("start");
			sprintf(stringBuffer, "Key 8 is Pressed ; start slow movement to right\n\r");
						
			break;
		}

		if(write(sFd, stringBuffer ,strlen(stringBuffer))==ERROR){
			//error
		}

	}
	if (nRead == ERROR) /* error from read() */
		perror("read");
	close(sFd); /* close server socket connection */
}
