
#include <stdio.h>
#include "systemManager.h"
#include "stateMachine.h"
#include "keyboard.h"
#include "myFunctions.h"
#include "TCPServer.h"
#include "TCPClient.h"
#include "TelnetServer.h"
#include <sysLib.h>
#include <ioLib.h>


extern "C" {
#include "hwFunc.h"
}


int n, m, value;
bool direction;
char textOutput[200];
char clean[200];
unsigned int initialSpeed = 200;
int arrayPosition=0;
int rampArrayPosition = 0;
int valuesInArrayOfProfile[160];
bool localMode=true;

StateMachine * myStateMachine;
Keyboard * myKeyboard;
TCPServer * myTCPServer;
TelnetServer * myTelnetServer;
TCPClient * myTCPClient;




SystemManager :: SystemManager() {
	
	
	// Initialize table for all diagrams, event time in ms (POSIX)
	// The maximum size of the table is defined in stateTable.h:
	// MAXDIA = 9, MAXLINES = 66
	// Should these be exceeded, please correct!

	tab[0][0] = new TableEntry ("idleState",        "chainIdle",        "setCommandChain", 0, myAction00,myCondition01); //condition02 ist immer true!
	tab[0][1] = new TableEntry ("idleState",        "localIdle",        "setCommandLocal", 0, myAction01,myCondition02);
	tab[0][2] = new TableEntry ("chainIdle",        "localIdle",        "toLocalIdle",     0, myAction02,myCondition03);
	tab[0][3] = new TableEntry ("localIdle",        "chainIdle",        "toChainIdle",     0, myAction03,myCondition04);

	tab[1][0] = new TableEntry ("localIdle",        "localIdle",        "setSpeed++",      0, myAction10,myCondition10); //Geschwindigkeit erhöhen
	tab[1][1] = new TableEntry ("localIdle",        "localIdle",        "setSpeed--",      0, myAction11,myCondition11); //Geschwindigkeit herabsetzen
	tab[1][2] = new TableEntry ("localIdle",        "localIdle",        "directionRight",  0, myAction12,myCondition12); //Richtung rechts wählen
	tab[1][3] = new TableEntry ("localIdle",        "localIdle",        "directionLeft",   0, myAction13,myCondition13); //Richtung links wählen
	tab[1][4] = new TableEntry ("localIdle",        "move",             "startProfile",    0, myAction14,myCondition14);	// Profil abfahren
	tab[1][5] = new TableEntry ("move",             "move",             "ProfileTimer",   50, myAction15,myCondition15); //Inkrement hochzählen
	tab[1][6] = new TableEntry ("move",             "localIdle",        "profileFinished", 0, myAction16,myCondition16); //Inkrement hochzählen
	
	// getStatus(Request) und send(Wait) muss noch in jede Action implementiert werden!
	// subcase in Programmcode nicht möglich.
	tab[2][0] = new TableEntry ("chainIdle",      	"slowMovementLeft",	"getStatus",       	0, myAction20,myCondition20); //start in Funktion getStatus implementieren
	tab[2][1] = new TableEntry ("slowMovementLeft", "slowMovementLeft",	"ChainModeTimer", 	50,myAction16,myCondition25); //action16 ist "noAction"
	tab[2][2] = new TableEntry ("slowMovementLeft", "movingProfile",   	"send(Release)",  	0, myAction21,myCondition21); //send und movingProfile in stop() implementieren
	tab[2][3] = new TableEntry ("movingProfile",  	"movingProfile",   	"ChainModeTimer", 	50,myAction15,myCondition15); //Inkrement hochzählen
	tab[2][4] = new TableEntry ("movingProfile",  	"packageDelivery", 	"profileFinished", 	0, myAction22,myCondition22); //stop in Funktion stop implementieren
	tab[2][5] = new TableEntry ("packageDelivery",	"slowMovementRight","start",		    0, myAction23,myCondition23);
	tab[2][6] = new TableEntry ("slowMovementRight","chainIdle",        "releaseReceived", 	0, myAction26,myCondition26);
	tab[2][7] = new TableEntry ("slowMovementRight","chainIdle",    	"transferFinished", 0, myAction24,myCondition24); //stop und busy=false noch implementieren
	
	tab[3][0] = new TableEntry ("StateK",           "StateK",           "Timer1",          100, myAction30,myCondition30);

	// Initialize timer names for all diagrams
	// Timer names are always Timer followed by the diagram number
	timerNames[1] = "ProfileTimer";
	timerNames[2] = "ChainModeTimer";
	timerNames[3] = "Timer1";
	
	

	// Initialize line numbers for all diagrams
	lines[0] = 4;
	lines[1] = 7;
	lines[2] = 8;
	lines[3] = 1;

	// Initialize first state for all diagrams
	actualState[0] = "idleState";
	actualState[1] = "localIdle";
	actualState[2] = "chainIdle";
	actualState[3] = "StateK";
	
	// Set the actual number of diagrams
	diagrams = 4;
	
	// Create instance of my Keyboard
	myKeyboard = new Keyboard;

	// Create instance of state machine
	myStateMachine = new StateMachine;
	
	// Create instance of TCP Server
	
	myTCPServer = new TCPServer;
	myTCPServer->init();
	
	
	
	// Create instance of Telnet Server
	
	myTelnetServer = new TelnetServer;
	myTelnetServer->init();

	
	// Create instance of TCP Client
	
	
	myTCPClient = new TCPClient;
	//myTCPClient->init("91.0.0.113");
	

	// Start timer for each diagram which needs one in the first state!

	myStateMachine->diaTimerTable[1]->startTimer(tab[1][5]->eventTime);
	myStateMachine->diaTimerTable[3]->startTimer(tab[3][0]->eventTime);

	// Initial actions can be done here, if needed!
	n = 0;
	m = 0;
	direction = true;
	
//Initialoutput**********************************************************************************
	
	
	sprintf(textOutput,"Speed is ([B]-inc; [C]-dec):                       %i		     ", initialSpeed);
	writeToDisplay (0, 0, textOutput );
		
	sprintf(textOutput,"Direction is ([E]-right;[F]-left):                 right         ");
	writeToDisplay (1, 0, textOutput );
	
	sprintf(textOutput,"actual state (to [1]-chainIdle; to [2]-localIdle): idleState     ");
	writeToDisplay (3, 0, textOutput );
	
	sprintf(textOutput,"State of profile movement:                         Motor Off     ");
	writeToDisplay (4, 0, textOutput);
	
	sprintf(textOutput,"[0] Start slow Movement and Profile in chainIdle");
	writeToDisplay (22, 0, textOutput);
	
	sprintf(textOutput,"[8] Start slow Movement (Packagetransfer to right conveyer belt)");
	writeToDisplay (23, 0, textOutput);
	
	sprintf(textOutput,"[A] Motorstart in localIdle");
	writeToDisplay (24, 0, textOutput);
	
	
	sprintf(textOutput,"Client Commands             Server Commands");
	writeToDisplay (12, 0, textOutput);
	sprintf(textOutput,"-------------------------------------------");
	writeToDisplay (13, 0, textOutput);
	sprintf(textOutput,"Right 91.0.0.XXX               Ready");
	writeToDisplay (14, 0, textOutput);
	sprintf(textOutput,"Request                        Release");
	writeToDisplay (15, 0, textOutput);

//************************************************************************************************
	
	return;
}

SystemManager :: ~SystemManager() {
	return;
}

// Funktionen für erstes Use-Case-Diagramm

//action00 -> Methode von idle in chain oder local mode
void SystemManager :: action00() {                                               //Taste 1

	m=2;
	direction = true;
	localMode=false;
			
	printf(" idle State -> Transition00 -> chainIdle\n\r");
				
	sprintf(textOutput,"actual state (to [5]-localIdle):                   chainIdle     ");
	writeToDisplay (3, 0, textOutput );
	sprintf(textOutput,"Direction is ([E]-right;[F]-left):                 right         ");
	writeToDisplay (1, 0, textOutput );
	
return;
	
}

void SystemManager :: action01() {												//Taste 2
	m=1;
	printf(" idleState -> Transition00 -> localIdle\n\r");
		
	sprintf(textOutput,"actual state (to [4]-chainIdle):                   localIdle     ");
	writeToDisplay (3, 0, textOutput );

return;
	
}

// Methode um von chainMode in localMode zu springen
void SystemManager :: action02(){													//Taste 5

	m=1;
	localMode=true;
	
	printf(" chain Mode -> Transition02 -> local Mode\n\r"); 
		
	sprintf(textOutput,"actual state (to [4]-chainIdle):                   localIdle     ");
	writeToDisplay (3, 0, textOutput );
	
return;
}

// Mehode um von localMode in chainMode zu springen
void SystemManager :: action03(){													//Taste 4
	
	m=2;
	direction = true;
	localMode=false;
	
	printf(" local Mode -> Transition03 -> chain Mode\n\r"); 
			
	sprintf(textOutput,"actual state (to [5]-localIdle):                   chainIdle     ");
	writeToDisplay (3, 0, textOutput );
	sprintf(textOutput,"Direction is ([E]-right;[F]-left):                 right         ");
	writeToDisplay (1, 0, textOutput );	
return;
}


// Funktionen für zweites Use-Case-Diagramm (local Mode)

// Methode um Geschwindigkeit um 1(100rpm) zu erhöhen
void SystemManager ::action10(){												//Taste B

		
		//int value = readAnalog(0,2);
		if (initialSpeed < 2200) {
		initialSpeed = initialSpeed + 100;
		
					
	sprintf(textOutput,"Speed is ([B]-inc; [C]-dec):                       %i		     ", initialSpeed);
	sprintf(clean,"                                                                 ");
	writeToDisplay (0, 0, clean );
	writeToDisplay (0, 0, textOutput );
		}

	printf("current value of speed is: %d", value);
	
return;
}

// Methode um Geschwindikeit um 1(100rpm) zu verkleinern
void SystemManager :: action11(){															//Taste C
	
	if (initialSpeed >= 200) {
	initialSpeed = initialSpeed - 100;
	
		
	sprintf(textOutput,"Speed is ([B]-inc; [C]-dec):                       %i		     ", initialSpeed);
	sprintf(clean,"                                                                 ");
				writeToDisplay (0, 0, clean );
				writeToDisplay (0, 0, textOutput );
	}

}

// Methode um Richtung nach rechts einzustellen
void SystemManager :: action12(){													//Taste E
		
	direction = true;
	sprintf(textOutput,"Direction is ([E]-right;[F]-left):                 right         ");
	writeToDisplay (1, 0, textOutput );
			
}

// Methode um Richtung nach links einzustellen
void SystemManager :: action13(){													//Taste F
		
	direction = false;
	sprintf(textOutput,"Direction is ([E]-right;[F]-left):                 left          ");
	writeToDisplay (1, 0, textOutput );
			
}

// Methode um Profil in local Mode abzufahren
void SystemManager :: action14(){														//Taste A
	     
		
	    printf(" local Profile activated\n\r");
	 
	 
	    //start motor; sendReady
	    if (direction==true){
	        motorOff();
	        if(arrayPosition==0){
	            int zielwert = 2100-(2100/2200.0*initialSpeed); 
	            int step = (2100-zielwert)/19;
	            for(unsigned int i=0; i<20;i++){
	                valuesInArrayOfProfile[i]=2100-(step*i);
	            }
	            for(unsigned int i=20; i<140;i++){
	                valuesInArrayOfProfile[i]=zielwert;
	            }
	            for(unsigned int i=140; i<160;i++){
	                valuesInArrayOfProfile[i]=zielwert+(step*(-140+i));
	            }
	        }
	    }
	    else{
	        motorOff();
	        if(arrayPosition==0){
	        	int zielwert = 2100+(2100/2200.0*initialSpeed); 
	        	int step = (zielwert-2100)/19;
	            for(unsigned int i=0; i<20;i++){
	                valuesInArrayOfProfile[i]=2100+(step*i);
	            }
	            for(unsigned int i=20; i<140;i++){
	                valuesInArrayOfProfile[i]=zielwert;
	            }
	            for(unsigned int i=140; i<160;i++){
	                valuesInArrayOfProfile[i]=zielwert-(step*(-140+i));
	            }
	        }
	    }
	     
	   /* for(unsigned i=0; i<160;i++){
	        printf("%i wertetabelle\n\r",motorProfileArray[i]);
	    }*/
	     
	    motorOn();
	 
	    printf(" event sent for starting\n\r");
	    
	    return;
			
			
}


void SystemManager :: action15(){ 
	
    
	printf(" local Profile activated\n\r");
		 
	
		    writeAnalog(0,valuesInArrayOfProfile[arrayPosition]);
		    
		 
		    printf(" event sent for starting\n\r");
		    			
    return;
}

void SystemManager :: action16(){ 
	
}


// Funktionen für drittes Use-Case-Diagramm
void SystemManager :: action20(){													//Taste 0
	
	sprintf(textOutput,"State of profile movement:			   Slow Movement             ");
	writeToDisplay (4, 0, textOutput);
	
	myTCPServer->sendMsg("Ready");
	writeAnalog(0,2200);
	motorOn();
	return;
}

void SystemManager :: action21(){
	printf(" start motor profile\n\r"); 
	    //start motor; sendReady
	    motorOff();
	    //TCPServer Befehl
	    myTCPServer->sendMsg("Release");
	    //sendrelease to the left neighbour
	    if(arrayPosition==0){
	        int zielwert = 500; //0 fastetst 2047 almost 0
	        int step = (2047-zielwert)/19;
	        for(unsigned i=0; i<20;i++){
	            valuesInArrayOfProfile[i]=2047-(step*i);
	        }
	        for(unsigned i=20; i<140;i++){
	            valuesInArrayOfProfile[i]=zielwert;
	        }
	        for(unsigned i=140; i<160;i++){
	            valuesInArrayOfProfile[i]=zielwert+(step*(-140+i));
	        }
	    }
	   
/*	    for(unsigned i=0; i<160;i++){
	        printf("%i wertetabelle\n\r",motorProfileArray[i]);
	    }
	    
	    	    
*/	  
	 

		sprintf(textOutput,"State of profile movement:			   Packagetransfer           ");
		writeToDisplay (4, 0, textOutput);

	    //start motor with ;
	    writeAnalog(0,valuesInArrayOfProfile[arrayPosition]);
	    motorOn();
	    
	return;
}

void SystemManager :: action22(){

	printf("request Right\n\r"); 
	myTCPClient->sendMsg("Request");
	motorOff();
	
	sprintf(textOutput,"State of profile movement:			   Prof. fin. wait for Ready[8]    ");
	writeToDisplay (4, 0, textOutput);
	
	
	return;
}


void SystemManager :: action23(){
	printf(" Transition to TransfertoRight because of Key 8 pressed\n\r"); 

	sprintf(textOutput,"State of profile movement:		   	   Received Ready start transfer  ");
	writeToDisplay (4, 0, textOutput);
	
	writeAnalog(0,2200);
	motorOn();
	return;
}

void SystemManager :: action24(){
	printf("motor stopped, new packet?\n\r");
	myTCPClient->sendMsg("Release");
	motorOff();
	sprintf(textOutput,"State of profile movement:			   Waiting for next packet       ");
	writeToDisplay (4, 0, textOutput);
	
	
	return;
}

void SystemManager :: action26(){

	motorOff();

	
	
	return;
}

void SystemManager :: action30(){
	char key = myKeyboard->getPressedKey();
	
	
	char tempKey = myKeyboard->getPressedKey();
	
	
	switch (tempKey)
	{
	case '1':
		
		myStateMachine->sendEvent("setCommandChain");
		
		break;
		
	case '2':

		myStateMachine->sendEvent("setCommandLocal");
		
		break;
		
	case '4':

		myStateMachine->sendEvent("toChainIdle");
		
		break;
		
	case '5':
	
		myStateMachine->sendEvent("toLocalIdle");
		
		break;
		
	case 'A':
		
		myStateMachine->sendEvent("startProfile");
		
		break;
		
	case 'B':
	
		myStateMachine->sendEvent("setSpeed--");
		
		break;
		
	case 'C':
	
		myStateMachine->sendEvent("setSpeed++");
		
		break;
		
	case 'E':
		
		myStateMachine->sendEvent("directionRight");
		
		break;
		
	case 'F':
		
		myStateMachine->sendEvent("directionLeft");
		break;	
	
	case '0':
		
		myStateMachine->sendEvent("getStatus");
		break;
		
	case '8':
		
		myStateMachine->sendEvent("start");	
	
		break;
		}
	
	return;
}



bool SystemManager :: condition15(){
	
    arrayPosition++;
    printf("in condition 15 ");
    //implement control for motorProfile which is feeded with table for values of the profile
   
    if (arrayPosition < 160) { 
    	printf(" Profile not finished %i \n\r", arrayPosition);

        return TRUE;
        
    }
    else {
        printf(" Profile finished\n\r"); 
        myStateMachine->sendEvent("profileFinished");
        arrayPosition=0;
        motorOff();
        return FALSE;
    }
    
         
}

bool SystemManager :: condition25(){
    rampArrayPosition++;
    printf(" rampArrayPosition: %i \n\r", rampArrayPosition);   
    if (rampArrayPosition < 20) { 
        return TRUE;
    }
    else {
        printf("1 second reached\n\r"); 
        rampArrayPosition=0;
   
        myStateMachine->sendEvent("send(Release)");
        return FALSE;
    }
         
}

bool SystemManager :: condition26(){
    rampArrayPosition++;
    printf(" rampArrayPosition: %i \n\r", rampArrayPosition);   
    if (rampArrayPosition < 20) { 
        return TRUE;
    }
    else {
        printf("1 second reached\n\r"); 
        rampArrayPosition=0;
    
        myStateMachine->sendEvent("transferFinished");
        return FALSE;
    }
         
}


bool SystemManager :: conditionTrue(){
	return TRUE;
}

bool SystemManager :: conditionTrue1(){
	if(m==1) return TRUE;
	else return FALSE;
}

bool SystemManager :: conditionTrue2(){
	if(m==2) return TRUE;
	else return FALSE;
}

