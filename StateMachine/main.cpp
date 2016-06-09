
#include <taskLib.h>
#include <stdio.h>
#include <intLib.h>
#include <sysLib.h>
#include <stdLib.h>
#include "ifLib.h"
#include "systemManager.h"
#include "stateMachine.h"

extern "C" {
#include "hwFunc.h"
}

SystemManager * mySystemManager;
StateMachine * myStateMachine;

void setLocalIp();

int main (void) {

	// Set tick to 5 ms. This is the time resolution!
	sysClkRateSet(200);
	
	initHardware(0);
	
	// Set local IP address according to MAC table
	setLocalIp();

	// Create instance of top class
	mySystemManager = new SystemManager;

	// Start the state machine. This method blocks, so no while(1) is needed.
	myStateMachine->runToCompletion();
	
}

void myAction00(){
	mySystemManager->action00();
	return;
}

void myAction01(){
	mySystemManager->action01();
	return;
}

void myAction02(){
	mySystemManager->action02();
	return;
}

void myAction03(){
	mySystemManager->action03();
	return;
}

void myAction10(){
	mySystemManager->action10();
	return;
}

void myAction11(){
	mySystemManager->action11();
	return;
}

void myAction12(){
	mySystemManager->action12();
	return;
}

void myAction13(){
	mySystemManager->action13();
	return;
}

void myAction14(){
	mySystemManager->action14();
	return;
}

void myAction15(){
	mySystemManager->action15();
}

void myAction16(){
	mySystemManager->action16();
}

void myAction20(){
	mySystemManager->action20();
	return;
}

void myAction21(){
	mySystemManager->action21();
	return;
}

void myAction22(){
	mySystemManager->action22();
	return;
}

void myAction23(){
	mySystemManager->action23();
	return;
}

void myAction24(){
	mySystemManager->action24();
	return;
}

void myAction30(){
	mySystemManager->action30();
	return;
}

bool myCondition00(){
	return mySystemManager->condition00();
}

bool myCondition01(){
	return mySystemManager->conditionTrue();
}

bool myCondition02(){
	return mySystemManager->conditionTrue();
}

bool myCondition03(){
	return mySystemManager->conditionTrue();
}

bool myCondition04(){
	return mySystemManager->conditionTrue();
}

bool myCondition10(){
	return mySystemManager->conditionTrue1();
}

bool myCondition11(){
	return mySystemManager->conditionTrue1();
}

bool myCondition12(){
	return mySystemManager->conditionTrue1();
}

bool myCondition13(){
	return mySystemManager->conditionTrue1();
}

bool myCondition14(){
	return mySystemManager->conditionTrue1();
}

bool myCondition15(){
	return mySystemManager->condition15();
}

bool myCondition16(){
	return mySystemManager->conditionTrue1();
}

bool myCondition20(){
	return mySystemManager->conditionTrue2();
}

bool myCondition21(){
	return mySystemManager->conditionTrue2();
}

bool myCondition22(){
	return mySystemManager->conditionTrue2();
}

bool myCondition23(){
	return mySystemManager->conditionTrue2();
}

bool myCondition24(){
	return mySystemManager->conditionTrue2();
}

bool myCondition25(){
	return mySystemManager->condition25();
}

bool myCondition26(){
	return mySystemManager->condition26();
}

bool myCondition30(){
	return mySystemManager->conditionTrue();
}
