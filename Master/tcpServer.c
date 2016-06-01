
#include <stdio.h>
#include <sysLib.h>
#include <stdLib.h>
#include <intLib.h>
#include <taskLib.h>
#include <sockLib.h>	//Für Sockets
#include <inetLib.h>	//?
#include <string.h>		//?
#include <fioLib.h>

/* defines */
#define SERVER_PORT_NUM 5555 /* server's port number for bind() */
#define SERVER_WORK_PRIORITY 100 /* priority of server's work task */
#define SERVER_STACK_SIZE 10000 /* stack size of server's work task */
#define SERVER_MAX_CONN_QUEUED 1 /* max clients connected at a time */
#define MAX_CONNECTIONS  1

/* prototypes */
void tcpServerWorkTask (int sFd, char * address);

int new_sfd;	

//-------------------------------Server task---------------------------------------

void tcpServerTask (void) {
	//Variablendefinitionen
	int id_TCPWorkTask;
	int sfd;							//Socket file descriptor
	int sockAddrSize;					//Größe des Socket file descriptors
	struct sockaddr_in serverAddr;		//socket addresse der servers 
	struct sockaddr_in clientAddr;		//socket addresse für client
	char workName[16];					//work name of the task
	int ix = 0;							//counter for work task names
	
	
	//Socket erzeugen
	
	/* socket (int adress_family, int type, int protocol);
	 * adress_family = AF_INET für Internet Protokoll
	 * type = SOCK_STREAM für TCP Verbindung
	 * protocol = 0, default-wert
	 * 
	 */ 
	//printf("Socket erzeugen..\n");
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	
	//Fehlerausgabe, falls socket nicht erfolgreich erstellt werden konnte
	if(sfd == -1){
		printf("Konnte socket nicht erfolgreich erstellen!\n");
	}
	
	//Struktur serverAddr auffüllen, damit im nächsten Schritt bind()
	// * ausgeführt werden kann
	sockAddrSize = sizeof(struct sockaddr_in);
	bzero((char *) &serverAddr, sockAddrSize);		//
	 
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT_NUM);
	serverAddr.sin_len = (u_char) sockAddrSize;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	//IP Adresse und Port des Servers mit bind() festlegen
	
	 /* STATUS bind(
	 * int socket file descriptor,	// socket descriptor
	 * struct sockaddr*	address,	// address to bind socket
	 * int addlen					// length of adress
	 * );
	 */ 
	//printf("Bind ausführen..\n");
	if(bind(sfd, (struct sockaddr *) &serverAddr, sockAddrSize) == ERROR){
		printf("Konnte bind nicht ausführen (TCP-Server)\n");
	}
	
	//Warteschlange einrichten
	//printf("listen..\n");
	if(listen(sfd, MAX_CONNECTIONS) == ERROR){
		printf("Konnte Warteschlange nicht einrichten!(TCP-Server)\n");
		close(sfd);		//?
	}
	//printf("Forever..\n");
	while(1){
		if((new_sfd = accept(sfd, (struct sockaddr *) &clientAddr, &sockAddrSize)) == ERROR){
			printf("accept() fehlgeschlagen!(TCP-Server)\n");
			close(sfd);
		}	
		sprintf(workName, "tTcpWork%d", ix++);
		if(id_TCPWorkTask = taskSpawn (workName, 120, 0, 0x10000, (FUNCPTR)tcpServerWorkTask,new_sfd, (int) inet_ntoa(clientAddr.sin_addr), 0, 0, 0, 0, 0, 0, 0, 0) == ERROR){
			printf("Konnte neuen task nicht erstellen!(TCP-Server)\n");
			close(new_sfd);
		}  
	}
} 

/*-------------------------------Server Work task---------------------------------------*/

void tcpServerWorkTask(int new_sfd, char * address){
	char commandBuffer[50];	
	char addressL[10];

	sprintf (addressL,"%s",address);
	printf("CLIENT IP: %s\n",addressL);	
	/*Solange die Konsole nicht geschlossen ist, führe die while 1 schleife aus*/
	while(fioRdString(new_sfd, commandBuffer, sizeof(commandBuffer)) > 0){	
		//Nachbar Links oder Nachbar rechts entscheiden..	
		printf("Server: Nachricht eingetroffen: %s\n", commandBuffer);
	}
	close(new_sfd);
}
