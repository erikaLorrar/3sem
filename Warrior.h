#include <iostream>
#include <tuple>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <list>

using namespace std;
const long long INF = 1e8;

// Наблюдатель
class Observer {
public:
	virtual ~Observer() {};
	virtual void upd(const std::string& message_from_subject) = 0;
	virtual void unitHasDie() = 0;
};

class Subject {
public:
	virtual ~Subject() {};
	virtual void add(Observer* observer) = 0;
	virtual void erase(Observer* observer) = 0;
	virtual void notification() = 0;
};


enum WarriorType {
	Reaper_D = 0,
	Soldier_D,
	Orisa_T,
	Zarya_T,
	Mercy_S,
	Brigitte_S,
};
enum Squad {
	DamageSquad = 0,
	TankSquad,
	SupportSquad,
};

class Warrior :Subject {//1

private:
	list<Observer*> observers;
	string message;

public:
	void add(Observer* _observer)override {
		observers.push_back(_observer);
	}
	void erase(Observer* _observer)override {
		observers.remove(_observer);
	}
	void notification()override {
		for (auto x : observers) {
			x->unitHasDie();
			x->upd(message);
		}
	}
	string makeMessage(string _message) {
		message = _message;
		notification();
		return message;
	}

	virtual int getHealth() = 0;

	virtual int getArmour() = 0;

	virtual int getAttack() = 0;

	virtual int removeHealth(int) = 0;

	virtual int addHealth(int) = 0;
	virtual string info() = 0;

	virtual WarriorType type() = 0;

	virtual Warrior* operator % (Warrior* unit) = 0;


	virtual ~Warrior() = default;
};//1

//1 класс
class Damage : public Warrior {//2
public:
	Warrior* operator % (Warrior* unit)override {
		if ((unit->getHealth() + unit->getArmour() - this->getAttack()) > (this->getHealth() + this->getArmour() - unit->getAttack())) {
			return unit;
		}
		else if ((unit->getHealth() + unit->getArmour() - this->getAttack()) < (this->getHealth() + this->getArmour() - unit->getAttack())) {
			return this;
		}
		else
			return nullptr;
	}
	Damage() {
		health = 150;
		attack = 120;
		armour = 80;
	}
private:
	int health;
	int attack;
	int armour;

	int getHealth() {
		return health;
	}

	int getAttack() {
		return attack;
	}

	int getArmour() {
		return armour;
	}

	int addHealth(int amount) {
		health += amount;
		return health;
	}

	int removeHealth(int amount) {
		health -= amount;
		return health;
	}


	string info() {
		return "Damage";
	};

};//2

class Reaper : public Damage {//3
public:
	string info() {
		return "Рипер";
	};
	WarriorType type() {
		return Reaper_D;
	}
};

class Soldier : public Damage {//3
public:
	string info() {
		return "Солдат";
	};
	WarriorType type() {
		return Soldier_D;
	}
};

//2 класс
class Tank : public Warrior {//2
public:
	Warrior* operator % (Warrior* unit)override {
		if ((unit->getHealth() + unit->getArmour() - this->getAttack()) > (this->getHealth() + this->getArmour() - unit->getAttack())) {
			return unit;
		}
		else if ((unit->getHealth() + unit->getArmour() - this->getAttack()) < (this->getHealth() + this->getArmour() - unit->getAttack())) {
			return this;
		}
		else
			return nullptr;
	}
	Tank() {
		health = 150;
		attack = 140;
		armour = 180;
	}
private:
	int health;
	int attack;
	int armour;


	int getHealth() {
		return health;
	}

	int getAttack() {
		return attack;
	}

	int getArmour() {
		return armour;
	}

	int addHealth(int amount) {
		health += amount;
		return health;
	}

	int removeHealth(int amount) {
		health -= amount;
		return health;
	}

	string info() {
		return "Сavalry";
	};
};

class Orisa : public Tank {//3
public:
	string info() {
		return "Ориса";
	};
	WarriorType type() {
		return Orisa_T;
	}
};

class Zarya : public Tank {//3
public:
	string info() {
		return "Заря";
	};
	WarriorType type() {
		return Zarya_T;
	}
};

//3 класс
class Support : public Warrior {//2
public:
	Support() {
		health = 100;
		attack = 100;
		armour = 100;
	}
	Warrior* operator % (Warrior* unit)override {
		if ((unit->getHealth() + unit->getArmour() - this->getAttack()) > (this->getHealth() + this->getArmour() - unit->getAttack())) {
			return unit;
		}
		else if ((unit->getHealth() + unit->getArmour() - this->getAttack()) < (this->getHealth() + this->getArmour() - unit->getAttack())) {
			return this;
		}
		else
			return nullptr;
	}
private:
	int health;
	int attack;
	int armour;

	int getHealth() {
		return health;
	}

	int getAttack() {
		return attack;
	}

	int getArmour() {
		return armour;
	}

	int addHealth(int amount) {
		health += amount;
		return health;
	}

	int removeHealth(int amount) {
		health -= amount;
		return health;
	}

	string info() {
		return "Support";
	};
};

class Mercy : public Support {//3
public:
	string info() {
		return "Мерси";
	};
	WarriorType type() {
		return Mercy_S;
	}
};

class Brigitte : public Support {//3

public:
	string info() {
		return "Бригитта";
	};
	WarriorType type() {
		return Brigitte_S;
	}
};

//Абстрактная фабрика
class Factory {
public:
	virtual Warrior* createWarrior(Squad squad, WarriorType type) = 0;

	virtual ~Factory() = default;
};

class DamageFactory : public Factory {
public:
	Warrior* createWarrior(Squad squad, WarriorType type) override {
		switch (squad, type) {
		case (DamageSquad, Reaper_D):
			return new Reaper;
		case (DamageSquad, Soldier_D):
			return new Soldier;
		}
	}
};

class TankFactory : public Factory {
public:
	Warrior* createWarrior(Squad squad, WarriorType type) override {
		switch (squad, type) {
		case (TankSquad, Orisa_T):
			return new Orisa;
		case (TankSquad, Zarya_T):
			return new Zarya;
		}
	}
};

class SupportFactory : public Factory {
public:
	Warrior* createWarrior(Squad squad, WarriorType type) override {
		switch (squad, type) {
		case (SupportSquad, Mercy_S):
			return new Mercy;
		case (SupportSquad, Brigitte_S):
			return new Brigitte;
		}
	}
};



class Base :public Observer {

public:
	Base(/*Warrior& _subject*/) /*: subject(_subject)*/ {
		//this->subject.add(this);
		health = 100;
		maxUnits = 5;
		cntOfUnits = 0;
	}
	void unitHasDie()override {
		cntOfUnits--;
	}
	void upd(const std::string& message_from_subject) override {
		message_from_subject_ = message_from_subject;
		PrintInfo();
	}
	//void RemoveMeFromTheList() {
		//subject.erase(this);
	//}
	void PrintInfo() {
		cout << this->message_from_subject_ << "\n";
	}

	Warrior* createUnit(Squad squad, WarriorType warriorType) {
		if (cntOfUnits >= maxUnits) {
			cout << "the maximum number of units has been created\n";
			return nullptr;
		}
		cntOfUnits++;
		auto damageFactory = new DamageFactory;
		auto tankFactory = new TankFactory;
		auto supportFactory = new SupportFactory;

		Warrior* battleUnit = nullptr;

		switch (squad) {
		case DamageSquad:
			battleUnit = (damageFactory->createWarrior(squad, warriorType));
			battleUnit->add(this);
			subjects.insert(battleUnit);
			return battleUnit;
		case TankSquad:
			battleUnit = (tankFactory->createWarrior(squad, warriorType));
			battleUnit->add(this);
			subjects.insert(battleUnit);
			return battleUnit;

		case SupportSquad:
			battleUnit = (supportFactory->createWarrior(squad, warriorType));
			battleUnit->add(this);
			subjects.insert(battleUnit);
			return battleUnit;
		}
		cout << "incorrect input\n";
		return battleUnit;
	}
	void eraseObserverInfo() {
		for (auto x : subjects)
			x->erase(this);
	}
	int getHealth() {
		return health;
	}
	int getCntOfUnits() {
		return cntOfUnits;
	}
	int getMaximumCntOfUnits() {
		return maxUnits;
	}
	int removeHealth(int amount) {
		health -= amount;
		return health;
	}
private:
	int health, maxUnits, cntOfUnits;
	string message_from_subject_;
	set<Warrior*> subjects;
};
