// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"

// class that manages the screen and window

namespace sxg::engine {
	class Screen {
	public:
		static sf::RenderWindow& window();
		//aspect ratio
	private:
		static int _width;
		static int _height;
		static string _title;
	};
}