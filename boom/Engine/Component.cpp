// (c) Simone Guggiari 2019
#include "Component.h"
#include "GameObject.h"

namespace sxg::engine {
	//Component::Component(GameObject& go) : _go(&go) { }; //memberwise copy

	// each script must implement this
	//Component* Component::clone(Component* original) = 0;
	/*
	void Component::invoke(void(Component::*memfun)(), float time) { //function<void(void)> f
		//Time::callback([this]() {f(this); }, 1.f);
		//memfun(*this);
	}
	*/

	//test graveyard
	/*
	Time::callback(bind(&Bomb::startTicking, this), bombTimer - tickingOffset);
	Time::callback(&printTestBomb(), 1.f);
	Time::callback(explode(), bombTimer);
	
	Time::callback([]() {cout << "test" << endl; }, 1.f); // THIS WORKS
	Time::callback([]() {Bomb::printTestBomb(); }, 1.f); // THIS WORKS
	Time::callback(bind(&Bomb::startTicking, this), 1.f);
	invoke(&Bomb::startTicking, 1);
	*/

	void Component::invoke(function<void(void)> func, float delay) {
		Time::invoke(func, delay, &gameobject());
	}


	//queries
	GameObject& Component::gameobject() { return *_go; }
	sf::Transformable& Component::transform() { return _go->transform(); }
	const sf::Transformable& Component::transform() const { return _go->transform(); }

}