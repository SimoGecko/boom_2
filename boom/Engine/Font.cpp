// (c) Simone Guggiari 2019
#include "Font.h"


namespace sxg::engine {

	sf::Text* Font::getText(const string& fontName, unsigned int characterSize, unsigned int ppu, const sf::Color& color, sf::Text::Style style) {
		sf::Text newText("", Resources::Get<sf::Font>(fontName), characterSize);
		newText.setStyle(style);
		newText.setFillColor(color);
		newText.setScale(1.f / ppu, 1.f / ppu);

		_textToDraw.push_back(move(newText));
		return &_textToDraw.back();
	}

	void Font::removeText(sf::Text* text) {
		//TODO ensure it's destructed properly, no mem-leak
		auto it = find_if(_textToDraw.begin(), _textToDraw.end(), [text](const sf::Text& elem) {return &elem == text; });
		if (it != _textToDraw.end()) {
			_textToDraw.erase(it);
		}
		else {
			Debug::logError("There isn't a text to remove: " + text->getString());
		}
	}

	void Font::draw() {
		for (const sf::Text text : _textToDraw) {
			Screen::window().draw(text);
		}
	}

	//static def
	vector<sf::Text> Font::_textToDraw;

}