// (c) Simone Guggiari 2019
#include "Input.h"


namespace sxg::engine {

	void Input::start() {
		_mouseStateOld = new vector<bool>(sf::Mouse::ButtonCount, false);
		_mouseStateNew = new vector<bool>(sf::Mouse::ButtonCount, false);

		_keyStateOld   = new vector<bool>(sf::Keyboard::KeyCount, false);
		_keyStateNew   = new vector<bool>(sf::Keyboard::KeyCount, false);
	}

	void Input::update() {
		swap(_mouseStateOld, _mouseStateNew);
		for (int i = 0; i < sf::Mouse::ButtonCount; i++) {
			_mouseStateNew->at(i) = sf::Mouse::isButtonPressed((sf::Mouse::Button)i);
		}

		swap(_keyStateOld, _keyStateNew);
		for (int i = 0; i < sf::Keyboard::KeyCount; i++) {
			_keyStateNew->at(i) = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i);
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
		return !_mouseStateOld->at(button) && _mouseStateNew->at(button);
	}
	bool Input::getMouseButton(int button) {
		return _mouseStateNew->at(button);
	}
	bool Input::getMouseButtonUp(int button) {
		return _mouseStateOld->at(button) && !_mouseStateNew->at(button);
	}

	// KEYBOARD __________________________________________________________

	bool Input::getKeyDown(sf::Keyboard::Key key) {
		return !_keyStateOld->at((int)key) && _keyStateNew->at((int)key);
	}
	bool Input::getKey(sf::Keyboard::Key key) {
		return _keyStateNew->at((int)key);
	}
	bool Input::getKeyUp(sf::Keyboard::Key key) {
		return _keyStateOld->at((int)key) && !_keyStateNew->at((int)key);
	}



	//static definitions
	vector<bool>* Input::_mouseStateOld;
	vector<bool>* Input::_mouseStateNew;
	vector<bool>* Input::_keyStateOld;
	vector<bool>* Input::_keyStateNew;
}