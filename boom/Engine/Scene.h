// (c) Simone Guggiari 2019
#pragma once
#include "../Includes.h"

// manages a collection of gameobjects and can be loaded/unloaded

namespace sxg::engine {

	class GameObject; // forward decl

	class Scene {
	public:
		
		static void load(const string& sceneName);

	protected:
		Scene(const string& name);
		virtual ~Scene();

		virtual vector<GameObject*> build() = 0; // this has to be implemented by each

	private:
		friend class GameObject;
		friend class Game;

		static void addGameObject(GameObject* go);
		static void removeGameObject(GameObject* go);

		const static vector<GameObject*>& AllGameObjects();

		static void start();
		static void update();

		//normal
		void unload();
		void finalAdd();
		void finalDelete();

		static void actualLoad(const string& sceneName);

		string _name;
		vector<GameObject*> _allGameObjects; // sort them by name?
		
		vector<GameObject*> _toAdd;    // used to avoid adding while updating
		vector<GameObject*> _toDelete; // used to avoid deleting something while updating

		//static
		static string _loadSceneName;
		static bool _mustLoadScene;

		static Scene* _currentScene;
		static unordered_map<string, Scene*> _allScenes;

	};

}