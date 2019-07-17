// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "Component.h"
#include "Renderable.h"

// Hub for components, with name, transform, and renderable. Also provides cloning and accessor functions

namespace sxg::engine {

	class GameObject {
	public:
		//_________________________ construction, components and destruction
		GameObject(const string name, const string tag = "default");

		GameObject(const GameObject& clone);

		//ctor with renderable already
		//ctor with transform

		//Destroy(lifetime=0)

		template <typename C>
		void addComponent();

		template <typename C>
		C* getComponent();

		//_________________________ normal methods

		void start();
		void update();
		//void draw();


		//_________________________ queries
		const string& name() const;
		const string& tag() const;
		bool active() const;
		void setActive(bool active);


		//_________________________ static
		static const vector<GameObject*>& All();

		static GameObject* FindGameObjectWithName(const string& name);
		static vector<GameObject*> FindGameObjectsWithTag(const string& tag);

		static GameObject* Instantiate(const string& name);


	private:
		string _name;
		string _tag;
		bool _active;

		string getUniqueName(const string& name) const;

		vector<Component*> _components;
		Renderable _renderable;
		sf::Transformable _transform;
	};

}