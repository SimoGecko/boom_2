// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"

// manages a collection of gameobjects and can be loaded/unloaded

namespace sxg::engine {

	class GameObject; // forward decl

	class Scene {
	public:

		void addGameobject(GameObject* go);
		vector<GameObject*>& AllGameObjects();
		
		//static
		static void start();
		static void load(string sceneName);
		//static Scene& current();

	protected:
		Scene(string name);
		virtual ~Scene();

	private:
		//normal
		virtual vector<GameObject*> build() = 0; // this has to be implemented by each
		void unload();

		string _name;
		vector<GameObject*> _allGameObjects;

		//static
		static string _defaultSceneName;
		static Scene* _currentScene;
		static unordered_map<string, Scene*> _allScenes;
	};

}