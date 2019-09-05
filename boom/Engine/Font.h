// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "Resources.h"
#include "Screen.h"
// simple facility for drawing text with fonts on screen

namespace sxg::engine {

	class Font {
	public:
		static sf::Text* getText(const string& fontName, unsigned int characterSize = 30, unsigned int ppu = 100, const sf::Color& color=sf::Color::White, sf::Text::Style style = sf::Text::Regular);
		
		static void removeText(sf::Text* text);

	private:
		friend class Game;
		static void draw();
		static vector<sf::Text*> _textToDraw;
	};

}