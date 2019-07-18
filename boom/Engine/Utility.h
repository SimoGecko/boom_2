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
		const float eps = 1e-5;

		sf::Vector2f& normalize(sf::Vector2f& v) {
			float norm = sqrt(v.x*v.x + v.y*v.y);
			if (norm > eps) {
				v.x /= norm;
				v.y /= norm;
			}
			else {
				v.x = v.y = 0;
			}


			return v;
		}

		float magnitude (const sf::Vector2f& v) { return sqrt(v.x*v.x + v.y*v.y); }
		float magnitude2(const sf::Vector2f& v) { return      v.x*v.x + v.y*v.y; }

		//rotate

		//angle
	}

	namespace { // UTILITY
		template <typename T>
		const string to_string(const sf::Vector2<T>& v) {
			return "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")";
		}
	}
	
	
	
}