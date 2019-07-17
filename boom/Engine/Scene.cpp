// (c) Simone Guggiari 2019
#include "Scene.h"


namespace sxg::engine {


	//normal
	Scene::Scene(const string name) : _name(name) {
		if (_allScenes.count(_name) > 0) {
			Debug::LogError("Scene already exists with name " + _name);
			return;
		}
		//add it to the list of all scenes
		bool mustLoad = _allScenes.empty();
		if (mustLoad) _defaultSceneName = name;
		_allScenes[_name] = this;

		//if (mustLoad) load(_name); // avoid loading from withing ctor since not done yet
	}

	Scene::~Scene() {
		unload();
	}

	void Scene::addGameObject(GameObject* go) {
		_allGameObjects.push_back(go);
	}
	void Scene::removeGameObject(GameObject* go) {
		//remove and DELETE?
	}

	void Scene::unload() {
		for (GameObject* go : _allGameObjects) {
			delete go;
			go = nullptr;
		}
		_allGameObjects.clear();
	}

	const vector<GameObject*>& Scene::AllGameObjects() const {
		return _allGameObjects;
	}

	//static
	void Scene::start() {
		//build here all the scenes
		//TODO move out of engine
		//_defaultSceneName = "boom_scene";
		//_allScenes["boom_scene"] = new BoomScene("boom_scene");

		//load default
		Scene::load(_defaultSceneName);
	}



	void Scene::load(const string sceneName) {
		if (Scene::_allScenes.count(sceneName) == 0) {
			Debug::LogError("No scene exists with name " + sceneName);
			return;
		}

		if (_currentScene != nullptr) {
			_currentScene->unload();
		}
		_currentScene = _allScenes[sceneName];

		auto objs = _currentScene->build();
		_currentScene->_allGameObjects = objs;

	}

	//static decl
	string Scene::_defaultSceneName;
	unordered_map<string, Scene*> Scene::_allScenes;
	Scene* Scene::_currentScene = nullptr;

}