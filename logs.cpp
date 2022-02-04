#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

class MyLog {
private:
	vector<string> logs;
public:
	MyLog() {}
	void makeNewLog(string com) {
		logs.push_back(com);
	}
	vector<string> outputLogsToFile() {
		return logs;
	}
	vector<string> outputLogsToConsole() {
		return logs;
	}
};

class Log {
public:
	virtual ~Log() {}
	virtual pair<string, string> printLog(int com) = 0;
	virtual pair<string, string> LogToFile() = 0;
	virtual pair<string, string> LogToConsole() = 0;
};

//Адаптер
class Adapter : public Log {
public:
	Adapter(MyLog* p) : p_myLog(p) {}
	~Adapter() {
		delete p_myLog;
	}
	pair<string, string> printLog(int com) {
		if (com == 1) {
			return(pair<string, string>(LogToConsole()));
		}
		if (com == 2) {
			return (pair<string, string>(LogToFile()));
		}
	}
	pair<string, string> LogToFile()override {
		stringstream ss;
		vector<string>logs = p_myLog->outputLogsToFile();
		for (auto x : logs) {
			ss << x;
			ss << endl;
		}
		string res;
		//ss >> res;
		string str;
		while (getline(ss, str)) {
			res += str;
			res += "\n";
		}
		return pair<string, string>(res, "log.txt");
	}
	pair<string, string> LogToConsole()override {
		stringstream ss;
		vector<string>logs = p_myLog->outputLogsToConsole();
		for (auto x : logs) {
			ss << x;
			ss << endl;
		}
		string res;
		//ss >> res;
		string str;
		while (getline(ss, str)) {
			res += str;
			res += "\n";
		}
		return pair<string, string>(res, "CON");
	}
private:
	MyLog* p_myLog;
};