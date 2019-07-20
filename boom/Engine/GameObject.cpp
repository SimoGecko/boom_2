// (c) Simone Guggiari 2019
#include "GameObject.h"


namespace sxg::engine {

	//_________________________ construction / destruction
	GameObject::GameObject(const string name,  int tag) :
		_name(getUniqueName(name)), _tag(tag), _active(true), _renderable(nullptr) {
		// add to list
	}

	//GameObject::GameObject(const GameObject& cloneObj) :
		//_name(getUniqueName(cloneObj.name())), _tag(cloneObj.tag()), _active(cloneObj.active()), _renderable(nullptr) {

	GameObject* GameObject::clone() const{
		GameObject* newGo = new GameObject(_name, _tag);
		//copy components

		for (Component* component : _components) {
			//TODO should call copy ctor of most derived class
			//_components.push_back(new Component(*component));
			Component* newComponent = component->clone(*newGo);
			//newComponent->_go = *newGo; // THIS CAUSES THE SWITCH!!!!!!!!!!!!!!!
			newGo->_components.push_back(newComponent);
		}

		newGo->copyTransform(transform_const());
		//copy other members
		if (_renderable != nullptr) {
			newGo->_renderable = new Renderable(*_renderable);
			newGo->_renderable->addToRenderables(); // in case it was prefab
		}
		return newGo;
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
	int GameObject::tag() const { return _tag; }
	bool GameObject::active() const { return _active; }
	void GameObject::setActive(bool active) { _active = active; }

	sf::Transformable& GameObject::transform() {
		if (_renderable != nullptr) {
			return _renderable->transform();
		}
		return _transform;
	}

	const sf::Transformable& GameObject::transform_const() const {
		if (_renderable != nullptr) {
			return _renderable->transform();
		}
		return _transform;
	}

	Renderable& GameObject::renderable() {
		if (_renderable == nullptr) Debug::logError("There is no renderable attached to gameobject: " + _name);
		return *_renderable;
	} // it will throw error if there is no renderable

	//_________________________ static
	const vector<GameObject*>& GameObject::All() {
		//return reference to those stored in the scene
		return Scene::current().AllGameObjects();
	}

	GameObject* GameObject::FindGameObjectWithName(const string& name) {
		// TODO implement better DS to speed up queries
		const vector<GameObject*>& all = All();
		for (GameObject* go : all) {
			if (go == nullptr) Debug::logError("Gameobject is null in GameObject::All()");
			else if (go->name() == name) return go;
		}
		return nullptr;
	}

	vector<GameObject*> GameObject::FindGameObjectsWithTag(int tag) {
		// TODO implement better DS to speed up queries
		const vector<GameObject*>& all = All();
		vector<GameObject*> ans;
		for (GameObject* go : all) {
			if (go == nullptr) Debug::logError("Gameobject is null in GameObject::All()");
			else if (go->tag() == tag) ans.push_back(go);
		}
		return ans;
	}

	
	GameObject* GameObject::Instantiate(const string& name, sf::Transformable* transf) {
		//find gameobject in prefabs
		GameObject* goPrefab = Prefabs::getPrefab(name);
		if (goPrefab == nullptr) {
			Debug::logError("Couldn't instantiate gameobject " + name);
			return nullptr;
		}

		//clone it
		GameObject* newGo = goPrefab->clone();//new GameObject(*goPrefab);

		//if transform, set it
		if (transf != nullptr) {
			newGo->copyTransform(*transf);
		}

		//add it to the scene
		Scene::current().addGameObject(newGo);
		return newGo;
	}

	GameObject* GameObject::Instantiate(const string& name, sf::Vector2f position) {
		GameObject* newGo = Instantiate(name, nullptr);
		newGo->transform().setPosition(position);
		return newGo;
	}
	


	//_________________________ private
	string GameObject::getUniqueName(const string& name) {
		//name is either in the form
		//whatevername
		//whatevername_001

		string prefix = name;
		if (prefix.size() > 4 && prefix[prefix.size() - 4] == '_') {
			prefix = prefix.substr(0, prefix.size() - 4);
		}

		bool isUnique = numCopies.count(prefix)==0;
		if (isUnique) {
			numCopies[prefix] = 1;
			return prefix; // or name?(should be same)
		}

		//not unique, create new name
		
		//find new bigger number
		int copyN = numCopies[prefix]++;

		//return name formatted
		stringstream ss;
		ss << setw(3) << setfill('0') << copyN;
		return prefix + "_" + ss.str();
	}

	void GameObject::copyTransform(const sf::Transformable& transf) {
		transform().setPosition(transf.getPosition());
		transform().setRotation(transf.getRotation());
		transform().setScale   (transf.getScale());
	}


	unordered_map<string, size_t> GameObject::numCopies;

}