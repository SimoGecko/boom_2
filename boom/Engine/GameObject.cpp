// (c) Simone Guggiari 2019
#include "GameObject.h"


namespace sxg::engine {

	//_________________________ construction / destruction
	GameObject::GameObject(const string name,  Tag tag) :
		_name(getUniqueName(name)), _tag(tag), _active(true), _renderable(nullptr) {
		// add to list
	}

	//GameObject::GameObject(const GameObject& cloneObj) :
		//_name(getUniqueName(cloneObj.name())), _tag(cloneObj.tag()), _active(cloneObj.active()), _renderable(nullptr) {

	GameObject* GameObject::clone() const{
		GameObject* newGo = new GameObject(_name, _tag);

		newGo->copyTransform(transform());
		//copy other members
		if (_renderable != nullptr) {
			newGo->_renderable = new Renderable(*_renderable);
			newGo->_renderable->addToRenderables(); // in case it was prefab
		}

		//copy components (anim requires renderable already)
		for (Component* component : _components) {
			Component* newComponent = component->clone();
			newComponent->_go = newGo;
			newGo->_components.push_back(newComponent);
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

	void GameObject::destroy(const float lifetime) {
		if (lifetime > 0) {
			Time::invoke([this]() {Scene::current().removeGameObject(this); }, lifetime, this);
		}
		else {
			Scene::current().removeGameObject(this);
		}
	}

	//_________________________ components

	void GameObject::addRenderable(const string& spriteName, sf::IntRect spriteRect, Layer layer, int ppu, bool add) {
		//copy transformation so far
		_renderable = new Renderable(spriteName, spriteRect, layer, ppu, add);
	}


	//_________________________ normal
	void GameObject::awake() {
		for (Component* component : _components) component->awake();
	}

	void GameObject::start() {
		for (Component* component : _components) component->start();
	}

	void GameObject::update() {
		//destroy in the mids of others?
		for (Component* component : _components) component->update();
	}

	void GameObject::onCollisionEnter(GameObject& other) {
		for (Component* component : _components) component->onCollisionEnter(other);
	}
	void GameObject::onCollisionExit(GameObject& other) {
		for (Component* component : _components) component->onCollisionExit(other);
	}

	//_________________________ queries
	const string& GameObject::name() const { return _name; }
	Tag GameObject::tag() const { return _tag; }
	bool GameObject::active() const { return _active; }
	void GameObject::setActive(bool active) { _active = active; }

	sf::Transformable& GameObject::transform() {
		if (_renderable != nullptr) {
			return _renderable->transform();
		}
		//Debug::logError("Trying to access transform even though don't have one: " + _name);
		return _transform;
	}

	const sf::Transformable& GameObject::transform() const {
		if (_renderable != nullptr) {
			return _renderable->transform();
		}
		//Debug::logError("Trying to access transform even though don't have one: " + _name);
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

	vector<GameObject*> GameObject::FindGameObjectsWithTag(Tag tag) {
		// TODO implement better DS to speed up queries
		const vector<GameObject*>& all = All();
		vector<GameObject*> ans;
		for (GameObject* go : all) {
			if (go == nullptr) Debug::logError("Gameobject is null in GameObject::All()");
			else if (go->tag() == tag) ans.push_back(go);
		}
		return ans;
	}

	
	GameObject* GameObject::Instantiate(const string& name, sf::Transformable* transf, sf::Vector2f position) {
		//find gameobject in prefabs
		GameObject* goPrefab = Prefabs::getPrefab(name);
		if (goPrefab == nullptr) {
			Debug::logError("Couldn't instantiate gameobject " + name);
			return nullptr;
		}

		//clone it
		GameObject* newGo = goPrefab->clone();

		//if transform, set it
		if (transf != nullptr) {
			newGo->copyTransform(*transf);
		}
		else {
			newGo->transform().setPosition(position);
		}

		//add it to the scene
		Scene::current().addGameObject(newGo); // start is called here!
		return newGo;
	}

	GameObject* GameObject::Instantiate(const string& name, sf::Vector2f position) {
		return Instantiate(name, nullptr, position);
		//newGo->transform().setPosition(position);
		//return newGo;
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

		//not unique, add extension to name
		
		//find next number
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