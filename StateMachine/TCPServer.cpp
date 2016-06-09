
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



extern int glTemp, glPot;
float modTemp, modPot;
int requestCount=0;

TCPClient * myTCPClient;
StateMachine * myStateMachine; 	//??
STATUS tcpServer(void);	//??
void tcpServerSendMsg(char * msg);
void decrementRequestCount(void);
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

void TCPServer :: decrementRequestCount(){
	if(requestCount>0){
		requestCount--;
	}else{
		requestCount=0;
	}
}

void TCPServer :: sendMsg(char *msg){
	tcpServerSendMsg(msg);
	return;
}



/* function declarations */
VOID tcpServerWorkTask(int sFdServer, char * address, u_short port);
/****************************************************************************
 *
 * tcpServer - accept and process requests over a TCP socket
 *
 * This routine creates a TCP socket, and accepts connections over the socket
 * from clients. Each client connection is handled by spawning a separate
 * task to handle client requests.
 *
 * This routine may be invoked as follows:
 * -> sp tcpServer
 * task spawned: id = 0x3a6f1c, name = t1
 * value = 3829532 = 0x3a6f1c
 * -> MESSAGE FROM CLIENT (Internet Address 192.0.2.10, port 1027):
 * Hello out there
 *
 * RETURNS: Never, or ERROR if a resources could not be allocated.
 */
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
/****************************************************************************
 *
 * tcpServerWorkTask - process client requests
 *
 * This routine reads from the server's socket, and processes client
 * requests. If the client requests a reply message, this routine
 * will send a reply to the client.
 *
 * RETURNS: N/A.
 */
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
	static char welcomeMsg[] = "Server opened on port 5555 :) ";
	if ((write(sFdServer, welcomeMsg, strlen(welcomeMsg))) == ERROR) {
		//error
	}
	while ((nRead = fioRdString(sFdServer, (char *) &request, sizeof(request))) > 0) {

		if (strcmp(request,"REQUEST\r")==0) {
			
			if(localMode==false){
				
				sprintf(stringBuffer, "REQ received\r");
				
				if(requestCount<2){
					
					if(requestCount>0){
						sprintf(stringBuffer, "new REQ received\r");
						newRequest=true;
						printf("send WAIT because of allready working\n\r");
						static char msg[]= "WAIT\r";
						write(sFdServer, msg, strlen(msg));
						printf("newRequest set to true");
					}
					else{
						myStateMachine->sendEvent("requestReceived");
						printf("request Received %i", requestCount);
						/*printf("send READY because or REQUEST\n\r");
						static char msg[]= "READY";
						write(sFdServer, msg, strlen(msg));
						printf("newRequest set to true");*/
					}
					requestCount++;
					
				}else{
					
					printf("max number of requests received");
					sprintf(stringBuffer, "max Request Received \r");
				}
				
			}else{
				printf("in local mode");
				sprintf(stringBuffer, "in LOCAL MODE \r");
			}
		}
		
		else if (request[0]=='T') {
			for(int i=1;i<20;i++){
				request[i-1]=request[i];
			}
			printf("key T pressed TCP SERVER %s",request);
			sprintf(stringBuffer, "ip Address to send %s \r",request);
			
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
		/*	printf("MESSAGE FROM CLIENT (Internet Address %s, port %d):\n%s\n",
		 address, port, request.message);
		 free(address);  free malloc from inet_ntoa() 
		 if (request.reply)
		 if (write(sFdServer, replyMsg, sizeof(replyMsg)) == ERROR)
		 perror("write");
		 */
	}
	if (nRead == ERROR) /* error from read() */
		perror("read");
	close(sFdServer); /* close server socket connection */
}

void tcpServerSendMsg(char * msg){
	
	char buffer[256];
	sprintf(buffer,msg);
	
	if (strcmp(buffer,"RELEASE")==0) {
		printf("send RELEASE\n\r");
		static char msg[]= "RELEASE\r";
		write(newFd, msg, strlen(msg));
	}
	else if (strcmp(buffer,"WAIT")==0){
		printf("send WAIT\n\r");
		static char msg[]= "WAIT";
		write(newFd, msg, strlen(msg));

	}
	else if (strcmp(buffer,"READY")==0){
		printf("send READY\n\r");
		static char msg[]= "READY\r";
		write(newFd, msg, strlen(msg));

	}
	else{
		static char errorMsg[] = "unknown message\r";
		write(newFd, errorMsg, strlen(errorMsg));
	}
}
