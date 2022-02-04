#include <tuple>
#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <list>
using namespace std;

//Итератор
class Iter {
private:
	//int stk;
	int sumOfInd;
	int cSize;
public:
	Iter(int beggin, int _cSize) {
		//stk = beggin;
		sumOfInd = beggin;
		cSize = _cSize;
	}
	void first() {
		sumOfInd = 0;
	}
	void next() {
		sumOfInd++;
	}
	void prev() {
		sumOfInd--;
	}
	/*bool isDone() {
		return ind == stk->sp + 1;
	}*/
	tuple<int, int> currentItem() {
		int posi = sumOfInd / cSize;
		//return stk->items[ind];
		int posj = sumOfInd % cSize;
		return (tuple<int, int>(posi, posj));
	}
};