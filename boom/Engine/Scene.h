// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"

// manages a collection of gameobjects and can be loaded/unloaded

namespace sxg::engine {

	class GameObject; // forward decl

	class Scene {
	public:
		Scene(const string name);
		virtual ~Scene();

		void addGameObject(GameObject* go);
		void removeGameObject(GameObject* go);

		const vector<GameObject*>& AllGameObjects() const;
		
		//static
		static void start();
		static void load(const string sceneName);
		static const Scene& current(); // should always have one

	protected:

		virtual vector<GameObject*> build() = 0; // this has to be implemented by each

	private:
		//normal
		void unload();

		string _name;
		vector<GameObject*> _allGameObjects; // sort them by name?

		//static
		static string _defaultSceneName;
		static Scene* _currentScene;
		static unordered_map<string, Scene*> _allScenes;
	};

}