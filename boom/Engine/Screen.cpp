// (c) Simone Guggiari 2019
#include "Screen.h"


namespace sxg::engine {
	int Screen::_width = 640;
	int Screen::_height = 480;
	string Screen::_title = "Title";

	sf::RenderWindow& Screen::window() { return _window; }
	sf::View& Screen::view() { return _view; }

	void Screen::start() {

		_view.reset(sf::FloatRect(-4, -1, 20, 15));
		//_view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

		_window.create(sf::VideoMode(_width, _height), _title);
		_window.setView(_view);
		_window.setVerticalSyncEnabled(true);
	}


	//static definition
	sf::RenderWindow Screen::_window;
	sf::View Screen::_view;
}