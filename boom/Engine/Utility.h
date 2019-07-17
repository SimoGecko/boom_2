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
	

	//FREE MATH FUNCTIONS
	namespace { 

		sf::Vector2f& normalize(sf::Vector2f& v) {
			float norm = v.x*v.x + v.y*v.y;
			v.x /= norm;
			v.y /= norm;
			return v;
		}

		float magnitude (const sf::Vector2f& v) { return sqrt(v.x*v.x + v.y*v.y); }
		float magnitude2(const sf::Vector2f& v) { return      v.x*v.x + v.y*v.y; }

		//rotate

		//angle
	}
	
	
	
}