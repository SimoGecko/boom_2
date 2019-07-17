// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
//#include "Component.h"
#include "Renderable.h"

// Hub for components, with name, transform, and renderable. Also provides cloning and accessor functions

namespace sxg::engine {

	class Component; // forward decl

	class GameObject {
	public:
		//_________________________ construction, components and destruction
		GameObject(const string name, const string tag = "default");

		GameObject(const GameObject& clone);
		virtual ~GameObject();

		//ctor with renderable already
		//ctor with transform

		//Destroy(lifetime=0)

		template <typename C>
		void addComponent();

		template <typename C>
		C* getComponent();

		void SetRenderable(Renderable* renderable);

		//_________________________ normal methods

		void start();
		void update();
		//void draw();


		//_________________________ queries
		const string& name() const;
		const string& tag() const;
		bool active() const;
		void setActive(bool active);

		sf::Transformable& transform();


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
		Renderable* _renderable;
		sf::Transformable _transform;
	};


	//_____________________________________ COMPONENT
	//it's here since we want to access gameobject members

	class Component {
	public:
		Component(GameObject& go) : _go(_go) {};
		virtual ~Component() {};

		//main methods -> not abstract as they could be empty and fine
		virtual void start() {};
		virtual void update() {};
		//virtual void draw() {};

		GameObject& gameobject() { return _go; }
		sf::Transformable& transform() { return _go.transform(); }

	private:
		GameObject& _go; // must always have a reference
	};
}