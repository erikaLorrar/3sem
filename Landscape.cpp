#include <tuple>
#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <list>

#include "Warrior.h"

using namespace std;



class LandScape {
public:
	virtual string info() = 0;
	virtual bool isItPossibleToPass(Warrior*) = 0;
};

class Forest :public LandScape {
private:
	set<WarriorType>whoCanNotBeHere;
public:
	Forest() {
		whoCanNotBeHere.insert(Orisa_T);
		whoCanNotBeHere.insert(Mercy_S);
	}
	bool isItPossibleToPass(Warrior* unit)override {
		return(!(whoCanNotBeHere.count(unit->type())));
	}
	string info()override {
		return"Forest";
	}
};

class Sand :public LandScape {
private:
	set<WarriorType>whoCanNotBeHere;
public:
	Sand() {
		whoCanNotBeHere.insert(Brigitte_S);
		whoCanNotBeHere.insert(Soldier_D);
	}
	bool isItPossibleToPass(Warrior* unit)override {
		return(!(whoCanNotBeHere.count(unit->type())));
	}
	string info()override {
		return"Sand";
	}
};

class Water :public LandScape {
private:
	set<WarriorType>whoCanNotBeHere;
public:
	Water() {
		whoCanNotBeHere.insert(Reaper_D);
		whoCanNotBeHere.insert(Zarya_T);
	}
	bool isItPossibleToPass(Warrior* unit)override {
		return(!(whoCanNotBeHere.count(unit->type())));
	}
	string info()override {
		return"Water";
	}
};