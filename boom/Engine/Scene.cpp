// (c) Simone Guggiari 2019
#include "Scene.h"
#include "GameObject.h"

namespace sxg::engine {


	//normal
	Scene::Scene(const string& name) : _name(name) {
		if (_allScenes.count(_name) > 0) {
			Debug::logError("Scene already exists with name: " + _name);
			return;
		}
		//add it to the list of all scenes
		bool mustLoad = _allScenes.empty();
		if (mustLoad) _loadSceneName = name;
		_allScenes[_name] = this;

		//if (mustLoad) load(_name); // avoid loading from withing ctor since not done yet
	}

	Scene::~Scene() {
		unload();
	}

	void Scene::addGameObject(GameObject* go) {
		if (go == nullptr) return;
		_toAdd.push_back(go);

		//this causes error
		go->awake();
		go->start();
		/*
		_allGameObjects.push_back(go);
		go->awake();
		go->start();
		*/
	}
	void Scene::removeGameObject(GameObject* go) {
		if (go == nullptr) return;
		_toDelete.push_back(go);
	}

	void Scene::unload() { // make sure it's called at the end of the update
		for (GameObject* go : _allGameObjects) {
			delete go;
			//go = nullptr; // its a copy
		}
		Time::eraseCallbacks();
		_allGameObjects.clear();
	}

	const vector<GameObject*>& Scene::AllGameObjects() const {
		return _allGameObjects;
	}

	//static
	void Scene::start() {
		//load default
		Scene::actualLoad(_loadSceneName);
	}
	
	void Scene::update() {
		actualAdd();
		actualDelete();

		if (_mustLoadScene) {
			_mustLoadScene = false;
			actualLoad(_loadSceneName);
		}
	}

	void Scene::load(const string& sceneName) {
		_mustLoadScene = true;
		_loadSceneName = sceneName;
	}


	void Scene::actualLoad(const string& sceneName) {
		if (Scene::_allScenes.count(sceneName) == 0) {
			Debug::logError("No scene exists with name: " + sceneName);
			return;
		}

		if (_currentScene != nullptr) {
			_currentScene->unload();
		}
		//clear timers
		_currentScene = _allScenes[sceneName];

		auto startingGameObjects = _currentScene->build();
		_currentScene->_allGameObjects = startingGameObjects;

		// since the scene might grow dynamically, call start only on those generated statically by the scene
		// scene takes care of calling start when newObject is inserted 
		for (size_t i = 0; i < startingGameObjects.size(); ++i) {
			startingGameObjects[i]->awake(); 
		}
		for (size_t i = 0; i < startingGameObjects.size(); ++i) {
			startingGameObjects[i]->start(); // what if something is instantiated here
		}
	}

	Scene& Scene::current() { return *_currentScene; }

	void Scene::actualDelete() {
		if (_toDelete.empty() || _currentScene==nullptr) return;
		vector<GameObject*>& allGo = _currentScene->_allGameObjects;

		for (GameObject* go : _toDelete) {
			auto it = find(allGo.begin(), allGo.end(), go);
			if (it != allGo.end()) {
				Time::eraseCallbacksOfDeletedObject(go);
				allGo.erase(it);
				delete go;
			}
		}

		_toDelete.clear();
	}

	void Scene::actualAdd() {
		if (_toAdd.empty() || _currentScene == nullptr) return;
		vector<GameObject*>& allGo = _currentScene->_allGameObjects;

		for (GameObject* go : _toAdd) {
			allGo.push_back(go);
		}

		_toAdd.clear();
	}

	//static decl
	string Scene::_loadSceneName;
	unordered_map<string, Scene*> Scene::_allScenes;
	Scene* Scene::_currentScene = nullptr;
	vector<GameObject*> Scene::_toAdd;
	vector<GameObject*> Scene::_toDelete;
	bool Scene::_mustLoadScene;
	 
}