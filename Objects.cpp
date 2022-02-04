#include <string>
#include "Landscape.cpp"

using namespace std;

//Стратегия
class Temple {
public:
	virtual string info() = 0;
	virtual int therapy(Warrior*) = 0;
	virtual bool CanTreatedHere(Warrior*) = 0;
};

class damageTemple :public Temple {
private:
	bool CanTreatedHere(Warrior* unit) {
		return(unit->info() == "Рипер" || unit->info() == "Солдат");
	}
public:
	string info()override {
		return "Temple damage";
	}
	int therapy(Warrior* unit) {
		if (!CanTreatedHere(unit)) {
			cout << "Этот юинт не может лечиться здесь\n";
			return -1;
		}
		unit->addHealth(50);
		return unit->getHealth();
	}
};

class tankTemple :public Temple {
private:
	bool CanTreatedHere(Warrior* unit) {
		return(unit->info() == "Ориса" || unit->info() == "Заря");
	}
public:
	string info()override {
		return "Temple tank";
	}
	int therapy(Warrior* unit) {
		if (!CanTreatedHere(unit)) {
			cout << "Этот юнит не может здесь лечиться\n";
			return -1;
		}
		unit->addHealth(50);
		return unit->getHealth();
	}
};

class supportTemple :public Temple {
private:
	bool CanTreatedHere(Warrior* unit) {
		return(unit->info() == "Мерси" || unit->info() == "Бригитта");
	}
public:
	string info()override {
		return "Temple support";
	}
	int therapy(Warrior* unit) {
		if (!CanTreatedHere(unit)) {
			cout << "Этот юнит не может здесь лечиться\n";
			return -1;
		}
		unit->addHealth(50);
		return unit->getHealth();
	}
};