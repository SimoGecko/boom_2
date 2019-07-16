// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"

// Various static helper classes

namespace sxg::engine {

	class Debug {
	public:
		static void Log(const string& message) {
			cout << "[LOG]\t" << message << endl;
		}
		static void LogError(const string& message) {
			cout << "[ERROR]\t" << message << endl;
		}
	};

	class Utility {
	public:

	private:
	};

}