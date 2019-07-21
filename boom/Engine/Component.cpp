// (c) Simone Guggiari 2019
#include "Component.h"
#include "GameObject.h"

namespace sxg::engine {
	//Component::Component(GameObject& go) : _go(&go) { }; //memberwise copy

	// each script must implement this
	//Component* Component::clone(Component* original) = 0;

	void Component::invoke(void(Component::*memfun)(), float time) { //function<void(void)> f
		//Time::callback([this]() {f(this); }, 1.f);
		//memfun(*this);
	}

	//queries
	GameObject& Component::gameobject() { return *_go; }
	sf::Transformable& Component::transform() { return _go->transform(); }

}