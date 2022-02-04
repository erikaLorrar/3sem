//#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include "logs.cpp"
#include "Field.cpp"

using namespace std;

class Game {
private:
	Scene scene;
public:
	MyLog* log;
	Game() {
		log = new MyLog;
		//scene = *new Scene;
		startMenu();
	}
	void startMenu() {
		cout << "1. Начать новую игру\n2. Выход\n";
		int com;
		cin >> com;
		if (com == 1) {
			log->makeNewLog("user: start game");
			game();
		}
		else {
			log->makeNewLog("user: exit");
			return;
		}
	}

	void gotoxy(short x, short y)
	{
		COORD position = { x,y }; //позиция x и y
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, position);
	}
	
	void infoMenu() {

		//gotoxy(scene.fieldSize*2+5, 1);

		//cout << "1. Всего юнитов на карте\n2. Всего баз на карте\n3. Всего больниц на карте\n";
		//int com;
		//cin >> com;
		//if (com == 1) {
		int i = 0;
		gotoxy(scene.fieldSize * 2 + 5, i); i++;
		log->makeNewLog("user: units sum");
		scene.totalUnitsOnMap();
		//}
		//if (com == 2) {
		gotoxy(scene.fieldSize * 2 + 5, i); i++;
		log->makeNewLog("user: base sum");
		scene.totalBasesOnMap();

		gotoxy(scene.fieldSize * 2 + 5, i); i++;i++;
		log->makeNewLog("user: temple sum");
		scene.totalTempleOnMap();
		//}
		//if (com == 3) {
			//gotoxy(scene.fieldSize * 2 + 5, i); i++;
			//log->makeNewLog("user: Temple sum");
			//scene.totalTemplesOnMap();
		//}
		
		for (int x = 0; x < scene.fieldSize; x++) {
			for (int y = 0; y < scene.fieldSize; y++) {
				if (scene.unitsOnScene.count(tuple<int, int>(x, y)) != 0) {
					gotoxy(scene.fieldSize * 2 + 5, i); i++;
					cout << scene.unitsOnScene[tuple<int, int>(x, y)]->info();
					cout << " (" << x << ";" << y << ")";
					gotoxy(scene.fieldSize * 2 + 5, i); i++;
			
					if (scene.unitsOnScene[tuple<int, int>(x, y)]->getHealth() < 50) {
						HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
					}
					
					cout << "Здоровье:  ";
					cout << scene.unitsOnScene[tuple<int, int>(x, y)]->getHealth();

					HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_RED);

					gotoxy(scene.fieldSize * 2 + 5, i); i++;
					cout << "Урон:  ";
					cout << scene.unitsOnScene[tuple<int, int>(x, y)]->getAttack();
					gotoxy(scene.fieldSize * 2 + 5, i); i++;i++;
					cout << "Броня:  ";
					cout << scene.unitsOnScene[tuple<int, int>(x, y)]->getArmour();
				}
			}
		}
		

		gotoxy(0, scene.fieldSize + 2);
	}

	void unitsMenu() {
		cout << "\n1. Добавить героя\n2. Взаимодействовать со существующим\n";
		int com;
		cin >> com;
		scene.printGameField();
		if (com == 1) {
			log->makeNewLog("user: create unit");
			cout << "\n Введите координаты базы, где вы хотите создать юнит\n";
			log->makeNewLog("user: base coordinates");
			int x, y;
			cin >> x >> y;
			Base* base = scene.getBaseFromCoord(x, y);
			Warrior* unit = nullptr;
			if (base == nullptr) {
				log->makeNewLog("user: incorrect coordinates");
				cout << "\n Некорректный ввод\n";
			}
			else {
				cout << "\n Выберите героя:\n1. Рипер\n2. Солдат\n3. Ориса\n4. Заря\n5. Мерси\n6. Бригитта\n";
				//scene.printGameField();
				int num;
				cin >> num;
				switch (num)
				{
				case 1:
					unit = base->createUnit(DamageSquad, Reaper_D);
					log->makeNewLog("user: new unit reaper");
					break;
				case 2:
					unit = base->createUnit(DamageSquad, Soldier_D);
					log->makeNewLog("user: new unit soldier");
					break;
				case 3:
					unit = base->createUnit(TankSquad, Orisa_T);
					log->makeNewLog("user: new unit orisa");
					break;
				case 4:
					unit = base->createUnit(TankSquad, Zarya_T);
					log->makeNewLog("user: new unit zarya");
					break;
				case 5:
					unit = base->createUnit(SupportSquad, Mercy_S);
					log->makeNewLog("user: new unit mercy");
					break;
				case 6:
					unit = base->createUnit(SupportSquad, Brigitte_S);
					log->makeNewLog("user: new unit brigitte");
					break;
				default:
					break;
				}
			}
			if (unit == nullptr) {
				cout << "\nНекорректный ввод\n";
				log->makeNewLog("user: Incorrect input");
			}
			else {
				scene.printGameField();
				cout << "\nВыбрать координаты для размещения юнита\n";
				int x, y;
				cin >> x >> y;
				log->makeNewLog("user: unit coordinates");
				if (scene.addUnit(unit, x, y) != -1)
					log->makeNewLog(unit->info() + ": user coordinates");
				else
					log->makeNewLog("user: Incorrect coordinates");
			}
		}
		else {
			cout << "\n1. Двигаться\n2. Лечиться\n3. Атаковать\n";
			int com;
			cin >> com;
			scene.printGameField();
			cout << "\nКоординаты юнита\n";
			int x, y;
			cin >> x >> y;
			log->makeNewLog("user: unit coordinates");
			Warrior* unit = scene.getUnitFromCoord(x, y);
			scene.printGameField();
			if (unit != nullptr) {
				if (com == 1) {
					log->makeNewLog("user: move unit");
					cout << "\n Введите a,w,d,s чтоб двигаться\n";
					char myStep;
					cin >> myStep;
					scene.step(unit, myStep);
				}
				if (com == 2) {
					log->makeNewLog("user: heal unit");
					cout << "\nВведите координаты храма, чтоб вылечить героя\n";
					int hx, hy;
					cin >> hx >> hy;
					Temple* Temple = scene.getTempleFromCoord(hx, hy);
					if (Temple != nullptr) {
						Temple->therapy(unit);
						log->makeNewLog(unit->info() + " : heal in Temple  " + Temple->info());
					}
				}
				if (com == 3) {
					log->makeNewLog("user: atack unit");
					cout << "\nВведите координаты для атаки\n";
					int ax, ay;
					cin >> ax >> ay;
					Warrior* enemyUnit = scene.getUnitFromCoord(ax, ay);

					scene.unitsOnScene[tuple<int, int>(ax, ay)]->removeHealth(scene.unitsOnScene[tuple<int, int>(x, y)]->getAttack());
					if (scene.unitsOnScene[tuple<int, int>(ax, ay)]->getHealth() <= 0) {
						scene.removeUnit(enemyUnit);
					}

					/*if (enemyUnit != nullptr) {
						log->makeNewLog(scene.fight(unit, enemyUnit));
					}*/
				}
				/*if (com == 4) {
					log->makeNewLog("user: inf unit heal");
					cout << scene.getUnitHealth(unit) << endl;
				}
				if (com == 5) {
					log->makeNewLog("user: inf unit armor");
					cout << scene.getUnitArmour(unit) << endl;
				}
				if (com == 6) {
					log->makeNewLog("user: inf unit atack");
					cout << scene.getUnitAttack(unit) << endl;
				}
				if (com == 7) {
					log->makeNewLog("user: inf unit");
					cout << scene.getUnitInfo(unit) << endl;
				}*/
			}
		}
	}

	void basesMenu() {
		cout << "\n1. Добавить базу\n2. Информация о существующей базе\n";
		int com;
		cin >> com;
		scene.printGameField();
		if (com == 1) {
			log->makeNewLog("user: create new base");
			cout << "\nВведите координаты:\n";
			int x, y;
			cin >> x >> y;
			log->makeNewLog("user: coordinates new base");
			//Base base = scene.createBase();
			scene.addBase(new Base, x, y);
		}
		if (com == 2) {
			log->makeNewLog("user: inf base");
			cout << "\nВведите координаты базы:\n";
			log->makeNewLog("user: input coordinates base");
			int x, y;
			cin >> x >> y;
			Base* base = nullptr;
			base = scene.getBaseFromCoord(x, y);
			if (base != nullptr) {
				cout << "\nМаксимальное количество героев:  ";
				log->makeNewLog("user: max units on base");
				cout << scene.maximumCountOfUnitsOnBase(base) << endl;
				cout << "\nКоличество героев на базе:  ";
				log->makeNewLog("user: sum unit on base");
				cout << scene.countOfUnitsOnBase(base) << endl;
			}
		}
	}

	void game() {
		string sizeOfField = scene.createGameField();
		log->makeNewLog("create scene " + sizeOfField + " X " + sizeOfField);
		int com;
		scene.printGameField();
		infoMenu();
		cout << "\n2. Управление базой \n3. Управление героями\n4. Управление храмом\n5. Выход\n ";
		cin >> com;
		while (com != 5) {
			//Sleep(1000);

			scene.printGameField();
			infoMenu();
			if (com == 2) {
				log->makeNewLog("user: menu bases");
				scene.printGameField();infoMenu();
				basesMenu();
			}
			if (com == 3) {
				log->makeNewLog("user: menu units");
				scene.printGameField();infoMenu();
				unitsMenu();
			}
			if (com == 4) {
				log->makeNewLog("user: menu Temple");
				scene.printGameField();
				TempleMenu();
			}
			if (com == 5) {
				log->makeNewLog("user: exit");
				break;
			}
			cout << "\n2. Управление базой \n3. Управление героями\n4. Управление храмом\n5. Выход\n ";
			cin >> com;
		}
		//system("cls");
		cout << "\n----------------Конец---------------- \n";
		//log->outputLogs();
		Log* adaptLog = new Adapter(log);
		cout << "\nВывод лог\n1. Консоль\n2. log.txt\n";
		int comm;
		cin >> comm;
		pair<string, string>  res = adaptLog->printLog(comm);
		ofstream fout;
		fout.open(res.second);
		fout << res.first;
		/*if (comm == 1) {
			system("pause");
		}*/
		//Sleep(5000);
		return;
	}

	void TempleMenu() {
		cout << "\n1. Создать храм\n2. Информация о храме\n";
		int com;
		cin >> com;
		scene.printGameField();
		if (com == 1) {
			log->makeNewLog("user: create new Temple");
			cout << "\nВведите координаты для создания храма\n";
			int x, y;
			cin >> x >> y;
			scene.printGameField();
			cout << "\nХрам:\n1. Ханамура\n2. Айхенвальд\n3. Нумбани\n";
			int func;
			cin >> func;
			if (func == 1) {
				scene.addTemple(scene.createTemple(DamageSquad), x, y);
			}
			if (func == 2) {
				scene.addTemple(scene.createTemple(TankSquad), x, y);
			}
			if (func == 3) {
				scene.addTemple(scene.createTemple(SupportSquad), x, y);
			}
		}
		if (com == 2) {
			cout << "\nВведите координаты храма для получения информации\n";
			int x, y;
			cin >> x >> y;
			Temple* Temple = scene.getTempleFromCoord(x, y);
			if (Temple != nullptr) {
				log->makeNewLog("user: inf Temple");
				cout << scene.getTempleInfo(Temple);
			}
		}
	}

};