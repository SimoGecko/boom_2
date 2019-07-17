// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "Screen.h"

// static class that provides access to input

namespace sxg::engine {

	class Input {
	public:
		Input() = delete;
		//~Input() {}

		static void start();
		static void update();

		static sf::Vector2i mousePosition();
		static bool isSpriteClicked(sf::Sprite& sprite, int button);

		static bool getMouseButtonDown	(int button);
		static bool getMouseButton		(int button);
		static bool getMouseButtonUp	(int button);

		static bool getKeyDown	(sf::Keyboard::Key key);
		static bool getKey		(sf::Keyboard::Key key);
		static bool getKeyUp	(sf::Keyboard::Key key);
	private:
		static vector<bool>* _mouseStateOld;
		static vector<bool>* _mouseStateNew;
		static vector<bool>* _keyStateOld;
		static vector<bool>* _keyStateNew;
	};

}