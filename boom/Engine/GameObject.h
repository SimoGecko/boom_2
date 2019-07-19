// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
//#include "Component.h"
#include "Renderable.h"
#include "Scene.h"
#include "Prefabs.h"

// Hub for components, with name, transform, and renderable. Also provides cloning and accessor functions

namespace sxg::engine {

	class Component; // forward decl

	class GameObject {
	public:
		//_________________________ construction, components and destruction
		GameObject(const string name, const string tag = "default");

		//GameObject(const GameObject& clone);
		virtual ~GameObject();

		//ctor with renderable already
		//ctor with transform

		//Destroy(lifetime=0)

		GameObject* clone() const;

		//_________________________ templatized components
		//template implementation must be here already
		template <typename C>
		C* addComponent() {
			//clone the component and add it to _components
			C* newComponent = new C(*this); // most derived
			_components.push_back(newComponent);
			return newComponent;
		}

		template <typename C>
		C* getComponent() {
			for (Component* component : _components) {
				auto ans = dynamic_cast<C*>(component);
				if (ans != nullptr) return ans;
			}
			return nullptr;
		}

		void SetRenderable(Renderable* renderable);

		//_________________________ normal methods

		void start();
		void update();
		//void draw();

		//void onCollisionEnter(const GameObject& other);
		//void onCollisionExit (const GameObject& other);

		//_________________________ queries
		const string& name() const;
		const string& tag() const;
		bool active() const;
		void setActive(bool active);

		sf::Transformable& transform();
		Renderable& renderable();
		const sf::Transformable& transform_const() const;


		//_________________________ static
		static const vector<GameObject*>& All();

		static GameObject* FindGameObjectWithName(const string& name);
		static vector<GameObject*> FindGameObjectsWithTag(const string& tag);

		static GameObject* Instantiate(const string& name, sf::Transformable* transf = nullptr);
		static GameObject* Instantiate(const string& name, sf::Vector2f position);


	private:
		string _name;
		string _tag;
		bool _active;

		static string getUniqueName(const string& name);
		void copyTransform(const sf::Transformable& transf);

		vector<Component*> _components;
		Renderable* _renderable;
		sf::Transformable _transform;

		//static
		static unordered_map<string, size_t> numCopies;
	};


	//_____________________________________ COMPONENT
	//it's here since we want to access gameobject members

	class Component {
	public:
		Component(GameObject& go) : _go(go) { };
		virtual ~Component() {};

		//main methods -> not abstract as they could be empty and fine
		virtual void start() {};
		virtual void update() {};
		//virtual void draw() {};

		virtual Component* clone(GameObject& go) { return nullptr; };// = 0; // each script must implement this

		GameObject& gameobject() { return _go; }
		sf::Transformable& transform() { return _go.transform(); }

	private:
		GameObject& _go; // must always have a reference
		friend class GameObject;

	};
}