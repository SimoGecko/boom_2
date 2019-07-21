// (c) Simone Guggiari 2019
#include "Utility.h"


namespace sxg::engine {

	//_________ DEBUG
	void Debug::log(const string& message) {
		cout << "[LOG]\t" << message << endl;
	}
	void Debug::logError(const string& message) {
		cout << "[ERROR]\t" << message << endl;
	}
	void Debug::ensure(bool condition, const string& message) {
		if (!condition) {
			cout << "[ASSERT]\t" << message << endl;
		}
	}


	//_________ RANDOM
	float Random::value() { return (float)rand() / RAND_MAX; }
	int   Random::range(int min, int max) { // exclusive
		return min + rand() % (max - min);
	}
	float Random::range(float min, float max) {
		return min + ((float)rand() / RAND_MAX)*(max - min);
	}
}