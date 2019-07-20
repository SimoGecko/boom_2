// (c) Simone Guggiari 2019
#include "Gizmos.h"


namespace sxg::engine {
	void Gizmos::drawCircle(sf::Vector2f position, float radius, sf::Color color) {
		sf::CircleShape circle;
		circle.setRadius(radius);
		circle.setPosition(position);
		circle.setOutlineColor(color);
		circle.setOutlineThickness(outlineThickness);
		circle.setFillColor(sf::Color::Transparent);
		_circles.push_back(move(circle));
	}

	void Gizmos::drawRectangle(sf::Vector2f position, sf::Vector2f size, sf::Color color) {
		sf::RectangleShape rectangle;
		rectangle.setSize(size);
		rectangle.setPosition(position);
		rectangle.setOutlineColor(color);
		rectangle.setOutlineThickness(outlineThickness);
		rectangle.setFillColor(sf::Color::Transparent);
		_rectangles.push_back(move(rectangle));
	}

	void Gizmos::update() {
		_circles.clear();
		_rectangles.clear();
	}

	void Gizmos::draw() {
		for (const sf::CircleShape& c : _circles)       Screen::window().draw(c);
		for (const sf::RectangleShape& r : _rectangles) Screen::window().draw(r);
	}

	//static definitions
	vector<sf::CircleShape> Gizmos::_circles;
	vector<sf::RectangleShape> Gizmos::_rectangles;
	float Gizmos::outlineThickness = 0.07f;
}