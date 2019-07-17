// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"

// class that manages the screen and window

namespace sxg::engine {
	class Screen {
	public:
		static sf::RenderWindow& window();
		static sf::View& view();
		//aspect ratio

		static void start();


	private:
		static int _width;
		static int _height;
		static string _title;

		static sf::RenderWindow _window;
		static sf::View _view;
	};
}