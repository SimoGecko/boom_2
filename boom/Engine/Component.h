// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"

// every script derives from component and has these functions called automatically

#define CLONABLE(Script) Component* clone() { return new Script(*this); }

namespace sxg::engine {

	class GameObject; // forward declaration

	class Component {
	public:
		//using memfct = void(Component::*)();
		//default ctor?
		//Component(GameObject& go);
		Component() = default; // ctor
		Component(const Component& src) = default; // copy ctor
		virtual ~Component() {};


		const sf::Transformable& transform() const;

	protected:
		//main methods -> not abstract as they could be empty and fine
		virtual void awake() {};
		virtual void start() {};
		virtual void update() {};
		//virtual void draw() {};

		virtual void onCollisionEnter(GameObject& other) {};
		virtual void onCollisionExit (GameObject& other) {};

		virtual Component* clone() = 0; // each script must implement this

		GameObject& gameobject();
		sf::Transformable& transform();
		void invoke(function<void(void)> func, float delay);

	private:
		GameObject* _go; // must always have a reference
		friend class GameObject;
	};
	

}