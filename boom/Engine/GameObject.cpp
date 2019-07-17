// (c) Simone Guggiari 2019
#include "GameObject.h"


namespace sxg::engine {

	//_________________________ construction / destruction
	GameObject::GameObject(const string name, const string tag) :
		_name(getUniqueName(name)), _tag(tag), _active(true), _renderable(nullptr) {
		// add to list
	}

	GameObject::GameObject(const GameObject& clone) :
		_name(getUniqueName(clone.name())), _tag(clone.tag()), _active(clone.active()), _renderable(nullptr) {

		//copy components
		for (Component* component : clone._components) {
			//TODO should call copy ctor of most derived class
			_components.push_back(new Component(*component));
		}

		//copy other members
		//_transform(clone._transform);
		if (clone._renderable != nullptr) {
			_renderable = new Renderable(*clone._renderable);
		}
	}

	GameObject::~GameObject() {
		//clean up
		for (Component* component : _components) {
			delete component;
		}
		_components.clear();

		if (_renderable != nullptr) delete _renderable;
	}

	//_________________________ components

	template <typename C>
	void GameObject::addComponent() {
		//clone the component and add it to _components
		C* newComponent = new C(this);
		_components.push_back(newComponent);
	}

	template <typename C>
	C* GameObject::getComponent() {
		for (C* component : _components) {
			auto ans = dynamic_cast<C*>(component);
			if (ans != nullptr) return ans;
		}
		return nullptr;
	}


	void GameObject::SetRenderable(Renderable* renderable) {
		//copy transformation so far
		_renderable = renderable;
	}


	//_________________________ normal
	void GameObject::start() {
		for (Component* component : _components) component->start();
	}

	void GameObject::update() {
		for (Component* component : _components) component->update();
	}

	//_________________________ queries
	const string& GameObject::name() const { return _name; }
	const string& GameObject::tag() const { return _tag; }
	bool GameObject::active() const { return _active; }
	void GameObject::setActive(bool active) { _active = active; }

	sf::Transformable& GameObject::transform() {
		if (_renderable != nullptr) return _renderable->transform();
		return _transform;
	}

	//_________________________ static
	const vector<GameObject*>& GameObject::All() {
		//return reference to those stored in the scene
	}

	GameObject* GameObject::FindGameObjectWithName(const string& name) {
		// TODO implement better DS to speed up queries
		const vector<GameObject*>& all = All();
		for (GameObject* go : all) {
			if (go == nullptr) Debug::LogError("gameobject is null in GameObject::All()");
			else if (go->name() == name) return go;
		}
		return nullptr;
	}

	vector<GameObject*> GameObject::FindGameObjectsWithTag(const string& tag) {
		// TODO implement better DS to speed up queries
		const vector<GameObject*>& all = All();
		vector<GameObject*> ans;
		for (GameObject* go : all) {
			if (go == nullptr) Debug::LogError("gameobject is null in GameObject::All()");
			else if (go->tag() == tag) ans.push_back(go);
		}
		return ans;
	}


	GameObject* GameObject::Instantiate(const string& name) {
		//find gameobject in prefabs

		//clone it

		//add it to the scene
	}


	//_________________________ private
	string GameObject::getUniqueName(const string& name) const {
		bool isUnique = true; // TODO lookup
		if (isUnique) return name;

		//not unique, create new name


		string prefix = name;
		if (prefix.size() > 4 && prefix[prefix.size() - 4] == '_') {
			prefix = prefix.substr(0, prefix.size() - 4);
		}
		//find new bigger number
		int copyN = 1;

		//return name formatted
		stringstream ss;
		ss << setw(3) << setfill('0') << copyN;
		return prefix + "_" + ss.str();
	}


}