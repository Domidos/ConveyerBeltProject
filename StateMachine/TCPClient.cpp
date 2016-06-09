
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
//void SetIP(char *ipAddress);
//char ipAddress[20]= "91.0.0.108";

TCPClient :: TCPClient() {
	printf("TCPClient Konstruktor!\n\r");	
	return;
}

TCPClient :: ~TCPClient() {
	return;
}

/*void TCPClient :: SetIP(char ipAddre[20]){
	printf(" setip server address: %s\n\r",ipAddre);
	for(int i=0; i<20; i++){
	ipAddress[i]=ipAddre[i];
	}
	printf(" setipcheck server address: %s\n\r",ipAddress);
	init(ipAddre);
	return;
}*/


void TCPClient::init(char ip[40]){
	
	//printf(" setip server address: %s\n\r",ipad);
	
	for(int i=0; i<20; i++){
	ipAddress[i]=ip[i];
	}


	printf(" setipcheck server address: %s\n\r",ip);
	//spawn TCP Server
	taskSpawn("tcpClient", 152, 0, 0x10000,(FUNCPTR) tcpClient, (int)ipAddress, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	printf("TCP_Client :: init() server address: %s\n\r",ipAddress);
	printf("Hello Baby!\n\r");
	return;
}

void TCPClient :: sendMsg(char *msg){
	tcpClientSendMsg(msg);
	return;
}



/* function declarations */

/****************************************************************************
* tcpClient - send requests to server over a TCP socket
*
* This routine connects over a TCP socket to a server, and sends a
* user-provided message to the server. Optionally, this routine
* waits for the server's reply message.
*
* This routine may be invoked as follows:
* -> tcpClient "remoteSystem"
* Message to send:
* Hello out there
* Would you like a reply (Y or N):
* y
* value = 0 = 0x0
* -> MESSAGE FROM SERVER:
* Server received your message
*
* RETURNS: OK, or ERROR if the message could not be sent to the server.
*/

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
	 printf("Hello Baby2!\n\r");
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
		 perror ("unknown server name LECK MICH FETT");
		 close (sFdClient);
		 return (ERROR);
		 }
	 /* connect to server */
	 if (connect (sFdClient, (struct sockaddr *) &serverAddr, sockAddrSize) == ERROR)
	 {
		 perror ("connect");
		 close (sFdClient);
		 return (ERROR);
	 }
	 /* build request, prompting user for message 
	 printf ("Message to send: \n");
	 mlen = read (STD_IN, myRequest.message, REQUEST_MSG_SIZE);
	 myRequest.msgLen = mlen;
	 myRequest.message[mlen - 1] = '\0';
	 printf ("Would you like a reply (Y or N): \n");
	 read (STD_IN, &reply, 1);
	 switch (reply)
	 {
	 case 'y':
	 case 'Y': myRequest.reply = TRUE;
	 break;
	 default: myRequest.reply = FALSE;
	 break;
	 }
	 // send request to server 
	 if (write (sFdClient, (char *) &myRequest, sizeof (myRequest)) == ERROR)
	 {
	 perror ("write");
	 close (sFdClient);
	 return (ERROR);
	 }
	 if (myRequest.reply) // if expecting reply, read and display it */ 
	 static char msg[]= "VERBINDUNG VORHANDEN";
	 write(sFdClient, msg, strlen(msg));
	 while ((nRead = fioRdString(sFdClient,  (char *) &replyBuf, sizeof(replyBuf))) > 0) {
	 	//if (read (sFdClient, replyBuf, REPLY_MSG_SIZE) < 0)
	 	/*{
	 		perror ("read");
	 		//close (sFdClient);
	 		return (ERROR);
	 	}
	 	else {*/
	 		printf("read %s\n\r",replyBuf);
	 		
	 		if(strcmp(replyBuf,"RELEASE\r")==0)
	 		{
	 			printf("TCP-Client; receiveRelease; %d\r\n",sFdClient);
	 			myStateMachine->sendEvent("receiveRelease");
	 		}
	 		else if(strcmp(replyBuf,"WAIT\r")==0){
	 			printf("TCP-Client: Wait; %d\r\n",sFdClient);
	 			//myStateMachine->sendEvent("receiveWait");
	 		}
	 		else if (strcmp(replyBuf,"READY\r")==0){
	 			printf("TCP-Client: Ready; %d\r\n",sFdClient);
	 			myStateMachine->sendEvent("receiveReady");
	 		}
	 	//}
	 	//printf ("MESSAGE FROM SERVER:\n%s\n", replyBuf);
	 	}
	 	//close (sFdClient);
	 	return (OK);
	 	
	 }


STATUS tcpClientSendMsg(char * msg){
	
	char buffer[256];
	sprintf(buffer,msg);
	
	if (strcmp(buffer,"RELEASE")==0) {
		printf("release\n\r");
		static char msg[]= "RELEASE\r";
		write(sFdClient, msg, strlen(msg));
	}
	else if (strcmp(buffer,"WAIT")==0){
		printf("wait\n\r");
		static char msg[]= "WAIT\r";
		write(sFdClient, msg, strlen(msg));

	}
	else if (strcmp(buffer,"READY")==0){
		printf("ready\n\r");
		static char msg[]= "READY";
		write(sFdClient, msg, strlen(msg));
	}
	else if (strcmp(buffer,"REQUEST")==0){
		printf("request right (tcp)\n\r");
		static char msg[]= "REQUEST\r";
		write(sFdClient, msg, strlen(msg));
	}
	
	else{
		static char errorMsg[] = "unknown message\r";
		write(sFdClient, errorMsg, strlen(errorMsg));
	}
	return (OK);
}
