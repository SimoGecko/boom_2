// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"

// Various static helper classes

namespace sxg::engine {

	class Debug {
	public:
		static void log(const string& message) {
			cout << "[LOG]\t" << message << endl;
		}
		static void logError(const string& message) {
			cout << "[ERROR]\t" << message << endl;
		}
		static void ensure(bool condition, const string& message) {
			if (!condition) cout << "[ASSERT]\t" << message << endl;
		}
		
	};

	
	class Utility {
	public:
	private:
	};
	
	const string emptyString = "";
	

	//FREE MATH FUNCTIONS
	namespace { 
		constexpr float eps			= 1e-5f;
		constexpr float pi			= 3.1415927f;
		constexpr float deg2rad		= 0.01745329251f;
		constexpr float rad2deg		= 57.2957795131f;

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
		sf::Vector2f& rotateby(sf::Vector2f& v, float degrees, const sf::Vector2f& center = {0,0}) {
			const float cs = cos(degrees);
			const float sn = sin(degrees);

			v.x -= center.x;
			v.y -= center.y;

			float nx = v.x*cs - v.y*sn;
			float ny = v.x*sn + v.y*cs;

			v.x = nx;
			v.y = ny;

			v.x += center.x;
			v.y += center.y;

			return v;
		}

		//angle
		float angle(const sf::Vector2f& v) {
			if      (v.y == 0) return v.x < 0 ? 180.f : 0.f;
			else if (v.x == 0) return v.y < 0 ? 270.f : 90.f;

			if (v.y > 0) {
				if (v.x > 0) return atan(v.y / v.x)  * rad2deg;
				else return 180.f - atan(v.y / -v.x) * rad2deg;
			}
			else {
				if (v.x > 0) return 360.f - atan(-v.y / v.x) * rad2deg;
				else return 180.f + atan(-v.y / -v.x) * rad2deg;
			}
		}
	}

	namespace { // UTILITY
		template <typename T>
		const string to_string(const sf::Vector2<T>& v) {
			return "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")";
		}

		const string to_string(void* pointer) {
			return std::to_string((int)pointer);
		}

		enum dir {right, up, left, down};
		dir dirFromVector(const sf::Vector2f& v) {
			float a = angle(v);
			assert(0 <= a && a <= 360);

			if (a <= 45)  return dir::right;
			if (a <= 135) return dir::up;
			if (a <= 225) return dir::left;
			if (a <= 315) return dir::down;
			return dir::right;
		}
	}
	
	
	
}