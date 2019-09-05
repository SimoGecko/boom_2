// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"

// Various static helper classes

namespace sxg::engine {

	//move into Utility.cpp
	//most of the methods are inline, so they'll stay here

	class Debug {
	public:
		static inline void log		(const string& message) {
			cout << "[LOG]\t" << message << endl;
		}
		static inline void logError (const string& message) {
			cout << "[ERROR]\t" << message << endl;
		}
		static inline void ensure	(bool condition, const string& message) {
			if (!condition) {
				cout << "[ASSERT]\t" << message << endl;
			}
		}
	};

	
	class Utility {
	public:
		static vector<sf::Vector2i> dir4;
	private:
	};

	class Ray {
	public:

	private:
		sf::Vector2f origin;
		sf::Vector2f direction;
	};

	class Random {
	public:

		static void start() {
			//set random seed
			unsigned int seed = (unsigned int)time(NULL);
			srand(seed);
		}

		static sf::Vector2f insideUnitCircle();
		static sf::Vector2f onUnitCircle();
		static sf::Vector2f insideUnitSquare();
		static sf::Vector2f onUnitSquare();
		static sf::Vector2f insideRectange(sf::FloatRect rect);

		static float value() {
			return (float)rand() / RAND_MAX;
		}
		static int   range(int min, int max){ // random in range [min, max[
			Debug::ensure(min < max, "Invalid parameters for Random::range");
			return min + (rand() % (max - min));
		}
		static float range(float min, float max) {
			return min + ((float)rand() / RAND_MAX)*(max - min);
		}

	private:
		//set a generator here
	};
	
	const string emptyString = "";
	

	//FREE MATH FUNCTIONS
	namespace { 
		constexpr float eps			= 1e-5f;
		constexpr float pi			= 3.14159265359f;
		constexpr float deg2rad		= 0.01745329251f;
		constexpr float rad2deg		= 57.2957795131f;



		static inline sf::Vector2f& normalize(sf::Vector2f& v) {
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

		static inline float magnitude (const sf::Vector2f& v) { return sqrt(v.x*v.x + v.y*v.y); }
		static inline float magnitude2(const sf::Vector2f& v) { return      v.x*v.x + v.y*v.y; }

		static inline int magnitude1(const sf::Vector2i& v) { return	abs(v.x) + abs(v.y); } // manhattan distance
		static inline int magnitude2(const sf::Vector2i& v) { return		v.x*v.x + v.y*v.y; }

		static inline float dot(const sf::Vector2f& a, const sf::Vector2f& b) { return a.x*b.x + a.y*b.y; }

		static inline sf::Vector2f lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t) {
			return (1 - t)*a + t * b;
		}
		static inline sf::Vector2f lerp(const sf::Vector2i& a, const sf::Vector2i& b, float t) {
			return sf::Vector2f((1 - t)*(float)a.x + t * (float)b.x, (1 - t)*(float)a.y + t * (float)b.y);
		}

		static inline sf::Vector2f to_v2f(const sf::Vector2i& v) { return sf::Vector2f((float)v.x, (float)v.y); }
		static inline sf::Vector2i to_v2i(const sf::Vector2f& v) { return sf::Vector2i((int)round(v.x), (int)round(v.y)); }

		//const sf::Vector2f v2fzero(0, 0);
		//const sf::Vector2i v2izero(0, 0);

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
		static inline float angle(const sf::Vector2f& v) {
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
		/*
		static inline float angle(const sf::Vector2i& v) {
			return angle(sf::Vector2f(v.x, v.y));
		}
		*/

	}

	namespace { // UTILITY
		template <typename T>
		const string to_string(const sf::Vector2<T>& v) {
			return "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")";
		}

		const string to_string(void* pointer) {
			return "0x" + std::to_string((int)pointer);
		}

		const string to_string_pad0(int x, int num0) {
			stringstream ss;
			ss << setfill('0') << setw(num0) << x;
			return ss.str();
		}

		const string to_min_sec(float timer) {
			int t = static_cast<int>(roundf(timer));

			int s = t % 60;
			int m = t / 60;
			char buffer[10];
			sprintf_s(buffer, "%02d:%02d", m, s);
			return buffer;
			//return to_string_pad0(m, 2) + ":" + to_string_pad0(s, 2);
		}


		// DIRECTIONS
		enum dir {none, right, up, left, down};
		enum orientation {center, horizontal, vertical};

		dir dirFromVector(const sf::Vector2f& v) {
			float a = angle(v);
			assert(0 <= a && a <= 360);

			if (a <= 45)  return dir::right;
			if (a <= 135) return dir::down;
			if (a <= 225) return dir::left;
			if (a <= 315) return dir::up;
			return dir::right;
		}

		sf::Vector2i vectorFromDir(dir d) {
			switch (d) {
				case dir::down:		return { 0, 1};
				case dir::up:		return { 0,-1};
				case dir::right:	return { 1, 0};
				case dir::left:		return {-1, 0};
			}
			return { 0,0 };
		}

		char charFromDir(dir d) {
			switch (d) {
				case dir::down : return 'D';
				case dir::up   : return 'U';
				case dir::right: return 'R';
				case dir::left : return 'L';
			}
			return '0';
		}

		const string stringFromOrientation(orientation o) {
			switch (o) {
			case orientation::center:		return "center";
			case orientation::horizontal:	return "horizontal";
			case orientation::vertical:		return "vertical";
			}
			return "";
		}
	}
	
	
	
}