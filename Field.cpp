#include "Objects.cpp"
#include "Iter.cpp"
#include <Windows.h>
#include <sstream>
using namespace std;

class Scene {

private:
	//map<tuple<int, int>, Warrior*> unitsOnScene;
	map<tuple<int, int>, Base*> basesOnScene;
	map<tuple<int, int>, LandScape*> LandscapesOnScene;
	map<tuple<int, int>, Temple*> TempleOnScene;
	bool check(int i, int j) {
		return(i < fieldSize&& j < fieldSize&& i> 0 && j>0);
	}
	map<string, char>namesOfSmtOnScreen;
	void addRandLandscape(int x, int y) {
		//LandScape* landscape = nullptr;// = new Water;
		int random = rand() % 3;
		//cout << random << endl;
		if (random == 0)
			LandscapesOnScene.insert(make_pair(tuple<int, int>(x, y), new Forest));
		if (random == 1)
			LandscapesOnScene.insert(make_pair(tuple<int, int>(x, y), new Water));
		if (random == 2)
			LandscapesOnScene.insert(make_pair(tuple<int, int>(x, y), new Sand));
	}

	tuple<int, int> findTheCoordinatesOfTheUnit(Warrior* unit) {
		for (auto x : unitsOnScene) {
			if (x.second == unit) {
				return(x.first);
			}
		}
		return(tuple<int, int>(-INF, -INF));
	}

	tuple<int, int> findTheCoordinatesOfTheBase(Base* base) {
		for (auto x : basesOnScene) {
			if (x.second == base) {
				return(x.first);
			}
		}
		return(tuple<int, int>(-INF, -INF));
	}

	void moveUnit(Warrior* unit, int x, int y) {//åñëè êòî-òî áûë â êëåòêå, â êîòîðóþ ìû ïåðåìåùàåì, òî ýòîò êòî-òî óäàëÿåòñÿ//////////////////////////////
		if (!(check(x, y))) {
			cout << "Некорректные координаты\n";
			return;
		}
		if (!canBeHere(unit, x, y)) {
			cout << "Этот юнит не может здесь стоять, неподходящий ландшафт\n";
			return;
		}
		tuple<int, int> st(-INF, -INF);
		for (auto x : unitsOnScene) {
			if (x.second == unit) {
				st = x.first;
				//x.second = nullptr;
				unitsOnScene.erase(x.first);
				break;
			}
		}
		if (st == tuple<int, int>(-INF, -INF))
			cout << "Юнит не найден\n";
		else
			unitsOnScene[tuple<int, int>(x, y)] = unit;
		return;
	}
public:
	map<tuple<int, int>, Warrior*> unitsOnScene;
	//Scene() {
	//	srand(time(NULL));
	//}
	int fieldSize;
	//int si, sj;
	friend class Iter;
	Base createBase() {
		return(*new Base());
	}
	string createGameField() {
		//srand(time(0));
		std::cout << "Введите размер игрового поля:  ";
		std::cin >> fieldSize;
		stringstream ss;
		ss << fieldSize;
		string sizeOfField;
		ss >> sizeOfField;
		for (int i = 0; i < fieldSize; i++) {
			/*if (i == 0 or i == fieldSize - 1) {
				for (int j = 0; j < fieldSize; j++) {
					std::cout << "X ";
				}
				std::cout << "\n";
			}*/
			//else {
			for (int j = 0; j < fieldSize; j++) {
				if (j == 0) {
					//std::cout << "X ";
				}
				else if (j == fieldSize - 1) {
					//std::cout << "X\n";
				}
				else {
					addRandLandscape(i, j);
					//std::cout << "* ";
				}
				//	}
			}
		}
		return sizeOfField;
	}

	void printGameField() {
		system("cls");
		for (int i = 0; i < fieldSize; i++) {
			if (i == 0 or i == fieldSize - 1) {
				for (int j = 0; j < fieldSize; j++) {
					std::cout << "X ";
				}
				std::cout << "\n";
			}
			else {
				for (int j = 0; j < fieldSize; j++) {

					if (j == 0) {
						HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_RED);
						std::cout << "X ";
					}
					else if (j == fieldSize - 1) {
						HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_RED);
						std::cout << "X\n";
					}
					//namesOfSmtOnScreen["Battlecruiser"] = 'B';
					else if (unitsOnScene.count(tuple<int, int>(i, j)) != 0) {
						if (unitsOnScene[tuple<int, int>(i, j)]->info() == "Рипер")
							std::cout << "Р ";
						if (unitsOnScene[tuple<int, int>(i, j)]->info() == "Солдат")
							std::cout << "С ";
						if (unitsOnScene[tuple<int, int>(i, j)]->info() == "Ориса")
							std::cout << "О ";
						if (unitsOnScene[tuple<int, int>(i, j)]->info() == "Заря")
							std::cout << "З ";
						if (unitsOnScene[tuple<int, int>(i, j)]->info() == "Мерси")
							std::cout << "М ";
						if (unitsOnScene[tuple<int, int>(i, j)]->info() == "Бригитта")
							std::cout << "Б ";
						//std::cout << "!  ";
					}
					else if (basesOnScene.count(tuple<int, int>(i, j)) != 0) {
						std::cout << "# ";
					}
					else if (TempleOnScene.count(tuple<int, int>(i, j)) != 0) {
						std::cout << "+ ";
					}
					else if (LandscapesOnScene.count(tuple<int, int>(i, j)) != 0) {
						if (LandscapesOnScene[(tuple<int, int>(i, j))]->info() == "Water") {
							HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE);
							cout << "~ ";
						}
						if (LandscapesOnScene[(tuple<int, int>(i, j))]->info() == "Sand") {
							HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
							cout << "^ ";
						}
						if (LandscapesOnScene[(tuple<int, int>(i, j))]->info() == "Forest") {
							HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
							cout << "* ";
						}
					}
					else {
						HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_RED);
					}

					
					/*else
						std::cout << "* ";*/
				}
			}
		}
	}


	Temple* createTemple(Squad squad) {
		Temple* Temple = 0;
		switch (squad) {
		case DamageSquad:
			Temple = new damageTemple;
			return Temple;
		case TankSquad:
			Temple = new tankTemple;
			return Temple;

		case SupportSquad:
			Temple = new supportTemple;
			return Temple;
		}
		return Temple;
	};



	bool canBeHere(Warrior* unit, int x, int y) {
		return(LandscapesOnScene[tuple<int, int>(x, y)]->isItPossibleToPass(unit));
	}
	int addUnit(Warrior* unit, int x, int y) {
		if (!(check(x, y))) {
			cout << "Некорректные координаты\n";
			return -1;
		}
		if (!canBeHere(unit, x, y)) {
			cout << "Этот юнит не может находиться здесь из-за ландшафта\n";
			return -1;
		}
		unitsOnScene.insert(make_pair(tuple<int, int>(x, y), unit));
		return 0;
	}

	void addTemple(Temple* Temple, int x, int y) {
		if (!(check(x, y))) {
			cout << "Некорректные координаты\n";
			return;
		}
		//cout << x << y;
		TempleOnScene.insert(make_pair(tuple<int, int>(x, y), Temple));
		//totalTemplesOnMap();
		
	}

	void addBase(Base* base, int x, int y) {
		if (!(check(x, y))) {
			cout << "Некорректные координаты\n";
			return;
		}
		basesOnScene.insert(make_pair(tuple<int, int>(x, y), base));
	}

	void totalUnitsOnMap() {
		cout << "Героев на поле: " << unitsOnScene.size() << endl;
	}

	void totalBasesOnMap() {
		cout << "Баз на поле: " << basesOnScene.size() << endl;
	}

	void totalTempleOnMap() {
		cout << "Храмов на поле: " << TempleOnScene.size() << endl;
	}

	tuple<int, int> coordinate(int x, int y) {
		return tuple<int, int>(x, y);
	}

	void getValueUnitFrom(int x, int y) {
		if (unitsOnScene.count(tuple<int, int>(x, y)) != 0)
			cout << unitsOnScene[tuple<int, int>(x, y)]->info() << endl;
		else
			cout << "В этой координате ничего нет\n";
	}

	int getUnitAttack(Warrior* unit) {
		return unit->getAttack();
	};

	int getUnitArmour(Warrior* unit) {
		return unit->getArmour();
	};

	string getUnitInfo(Warrior* unit) {
		return unit->info();
	};

	string getTempleInfo(Temple* unit) {
		return unit->info();
	};

	int getUnitHealth(Warrior* unit) {
		return(unit->getHealth());
	};

	void removeUnitHealth(int ammount, Warrior* unit) {
		unit->removeHealth(ammount);
		if (getUnitHealth(unit) <= 0) {
			unit->makeMessage("Unit " + getUnitInfo(unit) + " has died\n");
			auto thisUnit = findTheCoordinatesOfTheUnit(unit);
			unitsOnScene.erase(thisUnit);
		}
	};

	int getBaseHealth(Base* base) {
		return(base->getHealth());
	};

	void removeBaseHealth(int ammount, Base* base) {
		base->removeHealth(ammount);
		if (getBaseHealth(base) <= 0) {
			auto thisBase = findTheCoordinatesOfTheBase(base);
			basesOnScene.erase(thisBase);
			base->eraseObserverInfo();
		}
	}

	void removeBase(Base* base) {
		auto thisBase = findTheCoordinatesOfTheBase(base);
		basesOnScene.erase(thisBase);
		base->eraseObserverInfo();
	}

	void removeBaseFromCoord(int i, int j) {
		if (!(check(i, j))) {
			cout << "Некорректные координаты\n";
			return;
		}
		basesOnScene.erase(tuple<int, int>(i, j));
		basesOnScene[tuple<int, int>(i, j)]->eraseObserverInfo();
	}

	Iter* createIterator(int cSize)const {
		return new Iter(0, cSize);
	}

	void removeUnit(Warrior* unit) {
		unit->makeMessage("Unit " + getUnitInfo(unit) + "has died\n");
		auto thisUnit = findTheCoordinatesOfTheUnit(unit);
		unitsOnScene.erase(thisUnit);
	};

	void removeUnitFromCoord(int i, int j) {
		if (!(check(i, j))) {
			cout << "Некорректные координаты\n";
			return;
		}
		unitsOnScene.erase(tuple<int, int>(i, j));
	}

	//string fight(Warrior* unitA, Warrior* unitB) {
	//	Warrior* winner = *unitA % unitB;
	//	if (winner == nullptr) {
	//		cout << "ничья\n";
	//		return "draw";
	//	}
	//	cout << winner->info() << ' ' << "выиграл\n";
	//	if (winner != unitA) {
	//		//unitB->addHealth(unitA->getHealth());
	//		removeUnit(unitA);
	//	}
	//	else {
	//		//unitA->addHealth(unitB->getHealth());
	//		removeUnit(unitB);
	//	}
	//	return winner->info() + ' ' + "выиграл";
	//}

	void getTherapy(Warrior* unit, Temple* Temple) {
		Temple->therapy(unit);
	}

	void step(Warrior* unit, char command) {
		tuple<int, int>coord = findTheCoordinatesOfTheUnit(unit);
		int x, y;
		tie(x, y) = coord;
		if (command == 'w') {
			moveUnit(unit, x - 1, y);
		}
		if (command == 's') {
			moveUnit(unit, x + 1, y);
		}
		if (command == 'd') {
			moveUnit(unit, x, y + 1);
		}
		if (command == 'a') {
			moveUnit(unit, x, y - 1);
		}
	}

	Base* getBaseFromCoord(int x, int y) {
		if (!check(x, y)) {
			cout << "Некорректные координаты\n";
			return nullptr;
		}
		if (basesOnScene.count(tuple<int, int>(x, y)) == 0) {
			cout << "Нет ни одной здесь\n";
			return nullptr;
		}
		return(basesOnScene[tuple<int, int>(x, y)]);
	}

	Warrior* getUnitFromCoord(int x, int y) {
		if (!check(x, y)) {
			cout << "Некорректные координаты\\n";
			return nullptr;
		}
		if (unitsOnScene.count(tuple<int, int>(x, y)) == 0) {
			cout << "Нет ни одного здесь\n";
			return nullptr;
		}
		return(unitsOnScene[tuple<int, int>(x, y)]);
	}

	Temple* getTempleFromCoord(int x, int y) {
		if (!check(x, y)) {
			cout << "Некорректные координаты\\n";
			return nullptr;
		}
		if (TempleOnScene.count(tuple<int, int>(x, y)) == 0) {
			cout << "Нет ни одной здесь\n";
			return nullptr;
		}
		return(TempleOnScene[tuple<int, int>(x, y)]);
	}

	int countOfUnitsOnBase(Base* base) {
		return base->getCntOfUnits();
	}
	int maximumCountOfUnitsOnBase(Base* base) {
		return base->getMaximumCntOfUnits();
	}

};