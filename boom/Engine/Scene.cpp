// (c) Simone Guggiari 2019
#include "Scene.h"


namespace sxg::engine {


	//normal
	Scene::Scene(string name) : _name(name) {
		if (_allScenes.count(_name) > 0) {
			cerr << "Scene already exists with name " << _name << endl;
			return;
		}
		//add it to the list of all scenes
		bool mustLoad = _allScenes.empty();
		_allScenes[_name] = this;

		if (mustLoad) load(_name);
	}

	Scene::~Scene() {
		unload();
	}

	void Scene::addGameobject(GameObject* go) {
		_allGameObjects.push_back(go);
	}

	void Scene::unload() {
		for (GameObject* go : _allGameObjects) {
			delete go;
		}
	}

	vector<GameObject*>& Scene::AllGameObjects() {
		return _allGameObjects;
	}

	//static
	void Scene::start() {
		//build here all the scenes
		//TODO move out of engine
		_defaultSceneName = "boom_scene";
		//_allScenes["boom_scene"] = new BoomScene("boom_scene");

		//load default
		Scene::load(_defaultSceneName);
	}



	void Scene::load(string sceneName) {
		if (Scene::_allScenes.count(sceneName) == 0) {
			cerr << "No scene with name " << sceneName << endl;
			return;
		}

		if (_currentScene != nullptr) {
			_currentScene->unload();
		}
		_currentScene = _allScenes[sceneName];

		_currentScene->_allGameObjects = _currentScene->build();

	}

	//static decl
	string Scene::_defaultSceneName;
	unordered_map<string, Scene*> Scene::_allScenes;
	Scene* Scene::_currentScene = nullptr;

}