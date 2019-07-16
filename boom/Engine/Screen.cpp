// (c) Simone Guggiari 2019
#include "Screen.h"


namespace sxg::engine {
	int Screen::_width = 640;
	int Screen::_height = 480;
	string Screen::_title = "Title";

	sf::RenderWindow& Screen::window() {
		static sf::RenderWindow _window(sf::VideoMode(_width, _height), _title);
		return _window;
	}
}