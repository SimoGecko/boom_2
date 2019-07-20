// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "Screen.h"

// provides easy debug facility for drawing circles and rectangles outlines

namespace sxg::engine {

	class Gizmos {
	public:
		
		static void drawCircle(sf::Vector2f position, float radius, sf::Color color = sf::Color::White);
		static void drawRectangle(sf::Vector2f position, sf::Vector2f size, sf::Color color = sf::Color::White);

		static void update();
		static void draw();
	private:
		//friend void Game::run();
		
		static vector<sf::CircleShape> _circles;
		static vector<sf::RectangleShape> _rectangles;
		static float outlineThickness;

	};

}