// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"
#include "Component.h"
#include "Renderable.h"
#include "Scene.h"
#include "Prefabs.h"
#include "Specific.h"
#include "Time.h"

// Hub for components, with name, transform, and renderable. Also provides cloning and accessor functions

namespace sxg::engine {

	class Component; // forward decl

	class GameObject {
	public:
		//_________________________ construction, components and destruction
		GameObject(const string name, Tag tag = Tag::defaultTag);
		virtual ~GameObject();
		//ctor with renderable already
		//ctor with transform

		void destroy(const float lifetime = 0);

		GameObject* clone() const;

		//_________________________ templatized components
		//template implementation must be here already
		template <typename C>
		C* addComponent() {
			//clone the component and add it to _components
			C* newComponent = new C(); // most derived
			newComponent->_go = this;
			_components.push_back(newComponent);
			return newComponent;
		}

		template <typename C>
		C* getComponent() {
			for (Component* component : _components) {
				auto ans = dynamic_cast<C*>(component);
				if (ans != nullptr) return ans;
			}
			//Debug::logError("Gameobject " + _name + " doesn't have component of type " + typeid(C).name());
			return nullptr;
		}



		void addRenderable(const string& spriteName, sf::IntRect spriteRect, Layer layer = Layer::defaultLayer, int ppu = 100, bool add = true);

		//_________________________ normal methods

		void awake();
		void start();
		void update();
		//void draw();

		void onCollisionEnter(GameObject& other);
		void onCollisionExit (GameObject& other);

		//_________________________ queries
		const string& name() const;
		void setName(const string& newName);
		Tag tag() const;
		bool active() const;

		void setActive(bool active);

		Renderable& renderable();
		sf::Transformable& transform();
		const sf::Transformable& transform() const;


		//_________________________ static
		static const vector<GameObject*>& All();

		static GameObject* FindGameObjectWithName(const string& name);
		static vector<GameObject*> FindGameObjectsWithTag(Tag tag);

		static GameObject* Instantiate(const string& name, sf::Transformable* transf = nullptr, sf::Vector2f position = {0,0});
		static GameObject* Instantiate(const string& name, sf::Vector2f position);

	private:
		string _name; // make shared string and instance#
		Tag _tag;
		bool _active;

		vector<Component*> _components;
		Renderable* _renderable;
		sf::Transformable _transform; // not really needed, remove

		//methods
		static string getUniqueName(const string& name);
		void copyTransform(const sf::Transformable& transf);

		//static
		static unordered_map<string, size_t> numCopies;
	};


	//_____________________________________ COMPONENT
	//it's here since we want to access gameobject members

	
}