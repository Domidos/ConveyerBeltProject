
/* tcpServer.c - TCP server example */
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
#include "TCPServer.h"
#include"TCPClient.h"


extern "C" {
#include "hwFunc.h"
}


char textOutput[200];

TCPClient * myTCPClient;
StateMachine * myStateMachine; 
STATUS tcpServer(void);	
void tcpServerSendMsg(char * msg);
int sFdServer;
int newFd; /* socket descriptor from accept */

TCPServer :: TCPServer() {
	printf("tcpServer Konstruktor!\n\r");	
	return;
}

TCPServer :: ~TCPServer() {
	return;
}


void TCPServer::init( ){

	//spawn TCP Server
	taskSpawn("tcpServer", 152, 0, 0x10000,(FUNCPTR) tcpServer, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	return;
}


void TCPServer :: sendMsg(char *msg){
	tcpServerSendMsg(msg);
	return;
}



/* function declarations */
VOID tcpServerWorkTask(int sFdServer, char * address, u_short port);


STATUS tcpServer(void) {
	struct sockaddr_in serverAddr; /* server's socket address */
	struct sockaddr_in clientAddr; /* client's socket address */
	int sockAddrSize; /* size of socket address structure */
	//int sFdServer; /* socket file descriptor */

	int ix = 0; /* counter for work task names */
	char workName[16]; /* name of work task */
	/* set up the local address */
	sockAddrSize = sizeof(struct sockaddr_in);
	bzero((char *) &serverAddr, sockAddrSize);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_len = (u_char) sockAddrSize;
	serverAddr.sin_port = htons(SERVER_PORT_NUM);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	/* create a TCP-based socket */
	if ((sFdServer = socket(AF_INET, SOCK_STREAM, 0)) == ERROR) {
		perror("socket");
		return (ERROR);
	}
	/* bind socket to local address */
	if (bind(sFdServer, (struct sockaddr *) &serverAddr, sockAddrSize) == ERROR) {
		perror("bind");
		close(sFdServer);
		return (ERROR);
	}
	/* create queue for client connection requests */
	if (listen(sFdServer, SERVER_MAX_CONNECTIONS) == ERROR) {
		perror("listen");
		close(sFdServer);
		return (ERROR);
	}
	/* accept new connect requests and spawn tasks to process them */
	while (TRUE) {
		socklen_t len = sizeof(clientAddr);
		if ((newFd = accept(sFdServer, (struct sockaddr *) &clientAddr, &len))
				== ERROR) {
			perror("accept");
			close(sFdServer);
			return (ERROR);
		}
		sprintf(workName, "tTcpWork%d", ix++);
		if (taskSpawn(workName, SERVER_WORK_PRIORITY, 0, SERVER_STACK_SIZE,
				(FUNCPTR) tcpServerWorkTask, newFd,
				(int) inet_ntoa(clientAddr.sin_addr),
				ntohs(clientAddr.sin_port), 0, 0, 0, 0, 0, 0, 0) == ERROR) {
			/* if taskSpawn fails, close fd and return to top of loop */
			perror("taskSpawn");
			close(newFd);
		}
	}
}



VOID tcpServerWorkTask(
		int sFdServer, /* server's socket fd */
		char * address, /* client's socket address */
		u_short port /* client's socket port */
) {
	char request[256];
	int row = 2;
	int column = 2;
	char stringBuffer[80];
//	struct request request; /* request/message from client */
	int nRead; /* number of bytes read */
	static char replyMsg[] = "Server received your message";
	/* read client request, display message */
	static char welcomeMsg[] = "Dominik und Barthman heissen sie herzlich willkommen auf 5555";
	if ((write(sFdServer, welcomeMsg, strlen(welcomeMsg))) == ERROR) {
		//error
	}
	while ((nRead = fioRdString(sFdServer, (char *) &request, sizeof(request))) > 0) {

		if (strcmp(request,"Request\r")==0) {
			
			if(localMode==false){
				
								
				sprintf(stringBuffer, "Request received\r");
				
				myStateMachine->sendEvent("getStatus");
	
			}else{
				printf("in wrong state, first change to chainIdle");
				sprintf(stringBuffer, "in wrong state, first change to chainIdle \r");
			}
		}
		
		else if (request[0]=='i' && request[1]=='p') {
			for(int i=1;i<20;i++){
				request[i-2]=request[i];
			}
			printf("TCP SERVER %s",request);
			sprintf(stringBuffer, "IP Address of the right neighbor is %s \r",request);
			
			myTCPClient->init(request);
		}

		else{
			static char errorMsg[] = "falsche Eingabe\n\r";
			write(sFdServer, errorMsg, strlen(errorMsg));
			sprintf(stringBuffer, "");
		}

		if(write(sFdServer, stringBuffer ,strlen(stringBuffer))==ERROR){
			//error
		}

	}
	if (nRead == ERROR) /* error from read() */
		perror("read");
	close(sFdServer); /* close server socket connection */
}

void tcpServerSendMsg(char * msg){
	
	char buffer[256];
	sprintf(buffer,msg);
	
	if (strcmp(buffer,"Release")==0) {
		printf("send RELEASE\n\r");
		static char msg[]= "RELEASE\r";
		write(newFd, msg, strlen(msg));
		
	}
	else if (strcmp(buffer,"Wait")==0){
		printf("send WAIT\n\r");
		static char msg[]= "WAIT";
		write(newFd, msg, strlen(msg));

	}
	else if (strcmp(buffer,"Ready")==0){
		printf("send READY\n\r");
		static char msg[]= "READY\r";
		write(newFd, msg, strlen(msg));
		myStateMachine->sendEvent("getStatus");

	}
	else{
		static char errorMsg[] = "unknown message\r";
		write(newFd, errorMsg, strlen(errorMsg));
	}
}
