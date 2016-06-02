
#ifndef SYSTEMMANAGER_H_
#define SYSTEMMANAGER_H_

/*
#include <queue>
#include <semLib.h>

#include "diaTimer.h"
#include "stateTable.h"
*/

class SystemManager {
public:
	SystemManager();
	~SystemManager();
	void action00();
	void action01();
	void action02();
	void action03();
	void action10();
	void action11();
	void action12();
	void action13();
	void action14();
	void action15();
	void action16();
	void action20();
	void action21();
	void action22();
	void action23();
	void action24();
	void action30();
	
	bool conditionTrue();
	bool condition00();
	bool condition01();
	bool condition02();
	bool condition03();
	bool condition04();
	
	bool condition11();
	bool condition12();
	bool condition13();
	bool condition14();
	bool condition15();
	bool condition16();
	
	bool condition20();
	bool condition21();
	bool condition22();
	bool condition23();
	bool condition24();
	
	bool condition30();
	
	

private:
	
};

#endif // SYSTEMMANAGER_H_
