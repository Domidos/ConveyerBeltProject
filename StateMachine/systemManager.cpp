
#include <stdio.h>
#include "systemManager.h"
#include "stateMachine.h"
#include "keyboard.h"
#include "myFunctions.h"



extern "C" {
#include "hwFunc.h"
}

int n, m, value;
bool direction;
char textOutput[200];
char clean[200];
unsigned int initialSpeed = 200;
bool onOff = false;
int arrayCount=0;
int motorProfileArray[160];

StateMachine * myStateMachine;
Keyboard * myKeyboard;
/*
TCP_Server * myTPCServer;
Telnet_Server * myTelnetServer;
TCP_Client * myTCPClient;
*/


SystemManager :: SystemManager() {
	// Initialize table for all diagrams, event time in ms (POSIX)
	// The maximum size of the table is defined in stateTable.h:
	// MAXDIA = 9, MAXLINES = 66
	// Should these be exceeded, please correct!

	tab[0][0] = new TableEntry ("idleState","chainIdle","setCommandChain",0,myAction00,myCondition01); //condition02 ist immer true!
	tab[0][1] = new TableEntry ("idleState","localIdle","setCommandLocal",0,myAction01,myCondition02);
	tab[0][2] = new TableEntry ("chainIdle","localIdle","toLocalIdle",0,myAction02,myCondition03);
	tab[0][3] = new TableEntry ("localIdle","chainIdle","toChainIdle",0,myAction03,myCondition04);

	tab[1][0] = new TableEntry ("localIdle","localIdle","setSpeed++",0,myAction10,myCondition10); //Geschwindigkeit erhöhen
	tab[1][1] = new TableEntry ("localIdle","localIdle","setSpeed--",0,myAction11,myCondition11); //Geschwindigkeit herabsetzen
	tab[1][2] = new TableEntry ("localIdle","localIdle","directionRight",0,myAction12,myCondition12); //Richtung rechts wählen
	tab[1][3] = new TableEntry ("localIdle","localIdle","directionLeft",0,myAction13,myCondition13); //Richtung links wählen
	tab[1][4] = new TableEntry ("localIdle","move","startProfile",0,myAction14,myCondition14);	// Profil abfahren
	tab[1][5] = new TableEntry ("move","move","ProfileTimer",50,myAction15,myCondition15); //Inkrement hochzählen
	tab[1][6] = new TableEntry ("move","localIdle","profileFinished",0,myAction16,myCondition16); //Inkrement hochzählen
	
	// getStatus(Request) und send(Wait) muss noch in jede Action implementiert werden!
	// subcase in Programmcode nicht möglich.
	tab[2][0] = new TableEntry ("chainIdle","slowMovement","getStatus",0,myAction20,myCondition20); //start in Funktion getStatus implementieren
	tab[2][1] = new TableEntry ("slowMovement","movingProfile","Timer0",1000,myAction21,myCondition21); //send und movingProfile in stop() implementieren
	tab[2][2] = new TableEntry ("movingProfile","packageDelivery","Timer0",8000,myAction22,myCondition22); //stop in Funktion stop implementieren
	tab[2][3] = new TableEntry ("packageDelivery","slowMovement","start",0,myAction23,myCondition23);
	tab[2][4] = new TableEntry ("MotorProfile","MotorProfile","ProfileTimer",50,myAction15,myCondition15);
	tab[2][5] = new TableEntry ("slowMovement","chainIdle","getStatus",0,myAction24,myCondition24); //stop und busy=false noch implementieren
	
	tab[3][0] = new TableEntry ("StateK","StateK","Timer1",100,myAction30,myCondition30);

	// Initialize timer names for all diagrams
	// Timer names are always Timer followed by the diagram number
	timerNames[1] = "ProfileTimer";
	timerNames[3] = "Timer1";
	
	

	// Initialize line numbers for all diagrams
	lines[0] = 4;
	lines[1] = 7;
	lines[2] = 6;
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
	/*
	myTCPServer = new TCP_Server;
	myTCPServer->init();
	*/
	
	// Create instance of Telnet Server
	/*
	myTelnetServer = new Telnet_Server;
	myTelnetServer->init();
	*/
	
	// Create instance of TCP Client
	/*
	myTCPClient = new TCP_Client;
	myTCPClient->init();
	*/

	// Start timer for each diagram which needs one in the first state!
	// In my case these are diagram 0 and 2
//	myStateMachine->diaTimerTable[0]->startTimer(tab[0][0]->eventTime);
//	myStateMachine->diaTimerTable[2]->startTimer(tab[2][1]->eventTime);
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
	
	sprintf(textOutput,"Message received: 								   non           ");
	writeToDisplay (2, 0, textOutput );
	
	sprintf(textOutput,"Message sent: 									   non           ");
	writeToDisplay (3, 0, textOutput );
	
	sprintf(textOutput,"actual state (to [1]-chainIdle; to [2]-localIdle): idleState     ");
	writeToDisplay (3, 0, textOutput );
	
	sprintf(textOutput,"State of profile movement:										 ");
	writeToDisplay (4, 0, textOutput);

	//************************************************************************************************
	
	return;
}

SystemManager :: ~SystemManager() {
	return;
}

// Funktionen für erstes Use-Case-Diagramm

//action00 -> Methode von idle in chain oder local mode
void SystemManager :: action00() {                                               //Taste 1
	
			
	printf(" idle State -> Transition00 -> chainIdle\n\r");
				
	sprintf(textOutput,"actual state (to [5]-localIdle):                   chainIdle     ");
	writeToDisplay (3, 0, textOutput );
	
	return;
	
}

void SystemManager :: action01() {												//Taste 2
	
	printf(" idleState -> Transition00 -> localIdle\n\r");
		
	sprintf(textOutput,"actual state (to [4]-chainIdle):                   localIdle     ");
	writeToDisplay (3, 0, textOutput );

return;
	
}

// Methode um von chainMode in localMode zu springen
void SystemManager :: action02(){													//Taste 5

	
	printf(" chain Mode -> Transition02 -> local Mode\n\r"); 
		
	sprintf(textOutput,"actual state (to [4]-chainIdle):                   localIdle     ");
	writeToDisplay (3, 0, textOutput );
	
	return;
}

// Mehode um von localMode in chainMode zu springen
void SystemManager :: action03(){													//Taste 4

	printf(" local Mode -> Transition03 -> chain Mode\n\r"); 
			
	sprintf(textOutput,"actual state (to [5]-localIdle):                   chainIdle     ");
	writeToDisplay (3, 0, textOutput );
		
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
	
	
	/*
	
	char tempKey = myKeyboard->getPressedKey();
			tempKey = getKey();
			if (tempKey == '4'){
				direction = false;
				writeToDisplay (2, 0, "direction = false (links)");
			}
			
	*/		
}

// Methode um Profil in local Mode abzufahren
void SystemManager :: action14(){														//Taste A
	     
		
	    printf(" local Profile activated\n\r");
	 
	 
	    //start motor; sendReady
	    if (direction==true){
	        motorOff();
	        if(arrayCount==0){
	            int zielwert = 2100-(2100/2200.0*initialSpeed); 
	            int step = (2100-zielwert)/19;
	            for(unsigned int i=0; i<20;i++){
	                motorProfileArray[i]=2100-(step*i);
	            }
	            for(unsigned int i=20; i<140;i++){
	                motorProfileArray[i]=zielwert;
	            }
	            for(unsigned int i=140; i<160;i++){
	                motorProfileArray[i]=zielwert+(step*(-140+i));
	            }
	        }
	    }
	    else{
	        motorOff();
	        if(arrayCount==0){
	        	int zielwert = 2100+(2100/2200.0*initialSpeed); 
	        	int step = (zielwert-2100)/19;
	            for(unsigned int i=0; i<20;i++){
	                motorProfileArray[i]=2100+(step*i);
	            }
	            for(unsigned int i=20; i<140;i++){
	                motorProfileArray[i]=zielwert;
	            }
	            for(unsigned int i=140; i<160;i++){
	                motorProfileArray[i]=zielwert-(step*(-140+i));
	            }
	        }
	    }
	     
	    for(unsigned i=0; i<160;i++){
	        printf("%i wertetabelle\n\r",motorProfileArray[i]);
	    }
	     
	    motorOn();
	 
	    printf(" event sent for starting\n\r");
	    
	    return;
			
			
}


void SystemManager :: action15(){ 
	
	//printf("balabalaaaa");
    
	printf(" local Profile activated\n\r");
		 
	
		    writeAnalog(0,motorProfileArray[arrayCount]);
		    
		 
		    printf(" event sent for starting\n\r");
		    
		
	
    return;
}

void SystemManager :: action16(){ 
	
}
// Funktionen für drittes Use-Case-Diagramm
void SystemManager :: action20(){
	myStateMachine->sendEvent("getStatus");
	//myKeyboard->getPressedKey();
	return;
}

void SystemManager :: action21(){
	myStateMachine->sendEvent("send(Release)");
	//myKeyboard->getPressedKey();
	return;
}

void SystemManager :: action22(){
	myStateMachine->sendEvent("send(Request)");
	//myKeyboard->getPressedKey();
	return;
}


void SystemManager :: action23(){
	myStateMachine->sendEvent("start");
	//myKeyboard->getPressedKey();
	return;
}

void SystemManager :: action24(){
	myStateMachine->sendEvent("getStatus");
	//myKeyboard->getPressedKey();
	return;
}

void SystemManager :: action30(){
	char key = myKeyboard->getPressedKey();
	
	//printf (".");
	
	char tempKey = myKeyboard->getPressedKey();
	
	
	switch (tempKey)
	{
	case '1':
		
		//printf(" idle State -> Transition00 -> chain Mode\n\r");
		myStateMachine->sendEvent("setCommandChain");
		
		break;
		
	case '2':
		//printf(" idle State -> Transition01 -> local Mode\n\r");
		myStateMachine->sendEvent("setCommandLocal");
		
		break;
		
	case '4':
		//printf(" idle State -> Transition01 -> local Mode\n\r");
		myStateMachine->sendEvent("toChainIdle");
		
		break;
		
	case '5':
		//printf(" idle State -> Transition01 -> local Mode\n\r");
		myStateMachine->sendEvent("toLocalIdle");
		
		break;
		
	case 'A':
		//printf(" idle State -> Transition01 -> local Mode\n\r");
		myStateMachine->sendEvent("startProfile");
		
		break;
		
	case 'B':
		//printf(" idle State -> Transition01 -> local Mode\n\r");
		myStateMachine->sendEvent("setSpeed++");
		
		break;
		
	case 'C':
		//printf(" idle State -> Transition01 -> local Mode\n\r");
		myStateMachine->sendEvent("setSpeed--");
		
		break;
		
	case 'E':
		//printf(" idle State -> Transition01 -> local Mode\n\r");
		myStateMachine->sendEvent("directionRight");
		
		break;
		
	case 'F':
		//printf(" idle State -> Transition01 -> local Mode\n\r");
		myStateMachine->sendEvent("directionLeft");
		
		break;
		}
	
	

	
	
	/*
	if (key == 'A') {
		
		Test*****************************************************************************************
		writeAnalog (0, 600); 												//Motor konfigurieren
		motorOn();															//Motor starten
		writeToDisplay (0, 0, "Start wurde gedrueckt (Stop mit Taste B)");
		writeToDisplay (20, 0, "                                                              ");
		printf ("Taste A gedrückt\n");
		*********************************************************************************************
		
		myStateMachine->sendEvent("");
	
	}
	*/
	/*
	else if (key == 'B'){
		
		Test*****************************************************************************************
		motorOff();	//Motor stoppen
		printf ("Taste B gedrückt\n");
		writeToDisplay (0, 0, "                                                               ");
		writeToDisplay (20, 0, "Stop wurde gedrueckt (Start mit Taste A)");
		*********************************************************************************************
		
	}
	*/
	
	return;
}



bool SystemManager :: condition15(){
	
    arrayCount++;
    printf("in condition 15 ");
    //implement control for motorProfile which is feeded with table for values of the profile
    //printf(" arrayCount: %i \n\r", arrayCount);   
    if (arrayCount < 160) { 
    	printf(" Profile not finished %i \n\r", arrayCount);
    	myStateMachine->sendEvent("startProfile");
        return TRUE;
        
    }
    else {
        printf(" Profile finished\n\r"); 
        myStateMachine->sendEvent("profileFinished");
        arrayCount=0;
        motorOff();
        return FALSE;
    }
    
         
}


bool SystemManager :: conditionTrue(){
	return TRUE;
}

bool SystemManager :: condition00(){
	if (n < 5) {
		return TRUE;
	}
	else return FALSE;
}

bool SystemManager :: condition01(){
	if (n >= 5) return TRUE;
	else return FALSE;
}



bool SystemManager :: condition11(){
	if (m < 4) return TRUE;
	else return FALSE;
}

bool SystemManager :: condition12(){
	if (m >= 4) return TRUE;
	else return FALSE;
}

