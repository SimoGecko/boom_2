// (c) Simone Guggiari 2019
#include "Input.h"


namespace sxg::engine {

	void Input::start() {
		_mouseStateOld.resize(sf::Mouse::ButtonCount);
		_mouseStateNew.resize(sf::Mouse::ButtonCount);

		_keyStateOld.resize(sf::Keyboard::KeyCount);
		_keyStateNew.resize(sf::Keyboard::KeyCount);
	}

	void Input::update() {
		swap(_mouseStateOld, _mouseStateNew);
		for (int i = 0; i < sf::Mouse::ButtonCount; i++) {
			_mouseStateNew[i] = sf::Mouse::isButtonPressed((sf::Mouse::Button)i);
		}

		swap(_keyStateOld, _keyStateNew);
		for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
			_keyStateNew[i] = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i);
		}
	}




	// MOUSE __________________________________________________________
	sf::Vector2i Input::mousePosition() {
		return sf::Mouse::getPosition(Screen::window());
	}

	bool Input::isSpriteClicked(sf::Sprite& sprite, int button) {
		sf::FloatRect rect = sprite.getGlobalBounds();
		sf::Vector2i mousePos = sf::Mouse::getPosition(Screen::window());
		if (sf::Mouse::isButtonPressed((sf::Mouse::Button)button)) {
			if (rect.contains((float)round(mousePos.x), (float)round(mousePos.y))) return true;
		}
		return false;
	}


	bool Input::getMouseButtonDown(int button) {
		return !_mouseStateOld[button] && _mouseStateNew[button];
	}
	bool Input::getMouseButton(int button) {
		return _mouseStateNew[button];
	}
	bool Input::getMouseButtonUp(int button) {
		return _mouseStateOld[button] && !_mouseStateNew[button];
	}

	// KEYBOARD __________________________________________________________

	bool Input::getKeyDown(sf::Keyboard::Key key) {
		return !_keyStateOld[(int)key] && _keyStateNew[(int)key];
	}
	bool Input::getKey(sf::Keyboard::Key key) {
		return _keyStateNew[(int)key];
	}
	bool Input::getKeyUp(sf::Keyboard::Key key) {
		return _keyStateOld[(int)key] && !_keyStateNew[(int)key];
	}



	//static definitions
	vector<bool> Input::_mouseStateOld;
	vector<bool> Input::_mouseStateNew;
	vector<bool> Input::_keyStateOld;
	vector<bool> Input::_keyStateNew;
}