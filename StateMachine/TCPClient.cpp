
/* TCPClient.c - TCP server example */
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
#include "hostLib.h"
#include "fioLib.h"
#include "systemManager.h"
#include "stateMachine.h"
#include "TCPClient.h"



StateMachine * myStateMachine; 	
STATUS tcpClient(char * serverName);	
STATUS tcpClientSendMsg(char * msg);
static int sFdClient;
char ipAddress[20]="";

TCPClient :: TCPClient() {
	printf("TCPClient Konstruktor!\n\r");	
	return;
}

TCPClient :: ~TCPClient() {
	return;
}


void TCPClient::init(char ip[40]){
	
	
	for(int i=0; i<20; i++){
	ipAddress[i]=ip[i];
	}


	printf(" setipcheck server address: %s\n\r",ip);

	taskSpawn("tcpClient", 152, 0, 0x10000,(FUNCPTR) tcpClient, (int)ipAddress, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	printf("TCP_Client :: init() server address: %s\n\r",ipAddress);
	printf("Halloo!\n\r");
	return;
}

void TCPClient :: sendMsg(char *msg){
	tcpClientSendMsg(msg);
	return;
}


STATUS tcpClient
	 (
	 char * serverName /* name or IP address of server */
	 )
	 {
	 //struct request myRequest; /* request to send to server */
	 struct sockaddr_in serverAddr; /* server's socket address */
	 char replyBuf[REPLY_MSG_SIZE]; /* buffer for reply */
	 char reply; /* if TRUE, expect reply back */
	 int sockAddrSize; /* size of socket address structure */
	 //int sFdClient; /* socket file descriptor */
	 int mlen; /* length of message */
	 int nRead;
	 /* create client's socket */
	 printf("Hallooo!\n\r");
	 printf("adresse:%s", ipAddress );
	 if ((sFdClient = socket (AF_INET, SOCK_STREAM, 0)) == ERROR)
	 {
		 perror ("socket");
		 return (ERROR);
	 }
	 /* bind not required - port number is dynamic */
	 /* build server socket address */
	 sockAddrSize = sizeof (struct sockaddr_in);
	 bzero ((char *) &serverAddr, sockAddrSize);
	 serverAddr.sin_family = AF_INET;
	 serverAddr.sin_len = (u_char) sockAddrSize;
	 serverAddr.sin_port = htons (SERVER_PORT_NUM);
	 printf("adresse:%s", ipAddress );
	 if (((serverAddr.sin_addr.s_addr = inet_addr (ipAddress)) == ERROR) && ((serverAddr.sin_addr.s_addr = hostGetByName (ipAddress)) == ERROR))
		 {
		 perror ("unknown server name");
		 close (sFdClient);
		 return (ERROR);
		 }
	 /* connecting to server */
	 if (connect (sFdClient, (struct sockaddr *) &serverAddr, sockAddrSize) == ERROR)
	 {
		 perror ("connect");
		 close (sFdClient);
		 return (ERROR);
	 }
	 
	 static char msg[]= "Vorhandene Verbindung";
//	 write(sFdClient, msg, strlen(msg));
	 while ((nRead = fioRdString(sFdClient,  (char *) &replyBuf, sizeof(replyBuf))) > 0) {


	 		printf("read %s\n\r",replyBuf);
	 		
	 		if(strcmp(replyBuf,"Release\r")==0)
	 		{
	 			printf("TCP-Client; transferFinished; %d\r\n",sFdClient);
	 			myStateMachine->sendEvent("releaseReceived");
	 		}
	 		else if(strcmp(replyBuf,"Wait\r")==0){
	 			printf("TCP-Client: Wait; %d\r\n",sFdClient);
	 			
	 		}
	 		else if (strcmp(replyBuf,"Ready\r")==0){
	 			printf("TCP-Client: start; %d\r\n",sFdClient);
	 			myStateMachine->sendEvent("start");
	 		} 
	 	}
	 
	 	return (OK);
	 	
	 }


STATUS tcpClientSendMsg(char * msg){
	
	char buffer[256];
	sprintf(buffer,msg);
	
	if (strcmp(buffer,"Release")==0) {
		printf("Sock: %i (Client) release\n\r",sFdClient);
		static char msg[]= "Release\r\n";
		write(sFdClient, msg, strlen(msg));
	}
	else if (strcmp(buffer,"Wait")==0){
		printf("Sock: %i (Client) wait\n\r",sFdClient);
		static char msg[]= "Wait\r\n";
		write(sFdClient, msg, strlen(msg));

	}
	else if (strcmp(buffer,"Ready")==0){
		printf("Sock: %i (Client) ready\n\r",sFdClient);
		static char msg[]= "Ready\r\n";
		write(sFdClient, msg, strlen(msg));
	}
	else if (strcmp(buffer,"Request")==0){
		printf("Sock: %i (Client) request right \n\r",sFdClient);
		static char msg[]= "Request\r\n";
		write(sFdClient, msg, strlen(msg));
	}
	
	else{
		static char errorMsg[] = "unknown message\r";
		write(sFdClient, errorMsg, strlen(errorMsg));
	}
	return (OK);
}
