// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"

// every script derives from component and has these functions called automatically

namespace sxg::engine {

	class GameObject; // forward declaration

	class Component {
	public:
		//default ctor?
		//Component(GameObject& go);
		Component() = default; // ctor
		Component(const Component& src) = default; // copy ctor
		virtual ~Component() {};

		//main methods -> not abstract as they could be empty and fine
		virtual void start() {};
		virtual void update() {};
		//virtual void draw() {};

		virtual Component* clone() = 0; // each script must implement this

		GameObject& gameobject();
		sf::Transformable& transform();

	private:
		GameObject* _go; // must always have a reference
		friend class GameObject;

	};
	

}