// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "Component.h"

// Hub for components, with name, transform, and renderable. Also provides cloning and accessor functions

namespace sxg::engine {

	class GameObject {
	public:
		GameObject(string name) {
			//build new
			_name = name; // ensure unique
			// add to list
			_active = true;
		}

		GameObject(GameObject& clone) {
			//build a copy
		}

		template <typename C>
		void addComponent() {
			//clone the component and add it to _components
			auto c = make_shared<C>(this);
			_components.push_back(c);
		}

		template <typename C>
		C* getComponent() {
			for (auto& c : _components) {
				auto ans = dynamic_cast<shared_ptr<C>>(c);
				if (ans != nullptr) return ans;
			}
			return nullptr;
		}

		//_________________________

		void start();
		void update();
		//void draw();

	private:
		string _name;
		bool _active;

		vector<shared_ptr<Component>> _components;
		sf::Transformable _transform;
	};

}