// (c) Simone Guggiari 2019
#include "GameObject.h"


namespace sxg::engine {


	void GameObject::start() {
		for (auto& c : _components) c->start();
	}

	void GameObject::update() {
		for (auto& c : _components) c->update();
	}
}