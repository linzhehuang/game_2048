#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <cstdlib>
#include <ctime>
using namespace std;

class Random {
public:
	Random() {
		srand(int(time(NULL)));
	}
	int GetRandomNum(int min,int max) {
		return rand()%(max-min+1)+min;
	}
};

#endif