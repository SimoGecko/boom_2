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
		if (_currentScene &&  go != nullptr) {
			go->awake();
			go->start();
			_currentScene->_toAdd.push_back(go);
		}
	}
	void Scene::removeGameObject(GameObject* go) {
		if (_currentScene && go != nullptr) _currentScene->_toDelete.push_back(go);
	}

	void Scene::unload() { // make sure it's called at the end of the update
		for (GameObject* go : _allGameObjects) {
			delete go;
			//go = nullptr; // its a copy
		}
		_allGameObjects.clear();
	}

	const vector<GameObject*>& Scene::AllGameObjects() {
		if (_currentScene == nullptr) {
			Debug::logError("Trying to access allgameobjects while currentscene is null");
		}
		return _currentScene->_allGameObjects;
	}

	//static
	void Scene::start() {
		//load default
		Scene::actualLoad(_loadSceneName);
	}

	void Scene::update() {
		if (_currentScene != nullptr) {
			_currentScene->finalAdd();
			_currentScene->finalDelete();
		}

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
		_currentScene = _allScenes[sceneName];

		vector<GameObject*> startingGameObjects = _currentScene->build();


		//_currentScene->_allGameObjects = startingGameObjects;

		// since the scene might grow dynamically, call start only on those generated statically by the scene
		// scene takes care of calling start when newObject is inserted
		for (GameObject* go : startingGameObjects) {
			go->awake();
		}
		for (GameObject* go : startingGameObjects) {
			go->start();
		}

		_currentScene->_toAdd.insert(_currentScene->_toAdd.end(), startingGameObjects.begin(), startingGameObjects.end());

	}


	void Scene::finalDelete() {
		if (_toDelete.empty()) return;

		for (GameObject* go : _toDelete) {
			auto it = find(_allGameObjects.begin(), _allGameObjects.end(), go);
			if (it != _allGameObjects.end()) {
				Time::eraseCallbacksOfDeletedObject(go);
				_allGameObjects.erase(it);
				delete go;
			}
			else {
				Debug::logError("Scene trying to delete gameobject not found: " + go->name());
			}
		}

		_toDelete.clear();
	}
	void Scene::finalAdd() {
		if (_toAdd.empty()) return;

		vector<GameObject*> toaddcopy = _toAdd;
		_toAdd.clear();

		for (GameObject* go : toaddcopy) {
			_allGameObjects.push_back(go);
			//awake & start already called
		}

		//_toAdd.clear();
	}

	//static decl
	string Scene::_loadSceneName;
	bool Scene::_mustLoadScene;

	Scene* Scene::_currentScene = nullptr;
	unordered_map<string, Scene*> Scene::_allScenes;
}