// (c) Simone Guggiari 2019
#include "Component.h"
#include "GameObject.h"

namespace sxg::engine {
		Component::Component(GameObject& go) : _go(go) { };

		// each script must implement this
		Component* Component::clone(GameObject& go) {
			return nullptr;
		};

		//queries
		GameObject& Component::gameobject() { return _go; }
		sf::Transformable& Component::transform() { return _go.transform(); }

}